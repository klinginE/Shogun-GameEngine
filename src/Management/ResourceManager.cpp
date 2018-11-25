//Shogun includes
#include <Shogun/Management/ResourceManager.hpp>

//C++ includes
#include <unistd.h>
#include <iostream>
#include <fstream>

namespace sg
{
    ResourceManager::ResourceManager() :
    totalSizeOfData(0)
    {
        uint64_t pages = sysconf(_SC_PHYS_PAGES);
        uint64_t page_size = sysconf(_SC_PAGESIZE);
        uint64_t numberOfBytes = (pages * page_size);

        //By deault only allow up to 1/2th the total memory
        this->maxSizeOfData = (numberOfBytes >> 1);
    }

    ResourceManager::ResourceManager(uint64_t inMaxSizeOfData) :
    maxSizeOfData(inMaxSizeOfData),
    totalSizeOfData(0)
    {
        if (maxSizeOfData == 0)
        {
            uint64_t pages = sysconf(_SC_PHYS_PAGES);
            uint64_t page_size = sysconf(_SC_PAGESIZE);
            uint64_t numberOfBytes = (pages * page_size);
    
            //By deault only allow up to 1/2th the total memory
            this->maxSizeOfData = (numberOfBytes >> 1);
        }
    }

    ResourceManager::~ResourceManager()
    {
        for (const std::string* key : this->stringKeyAge)
        {
            this->removeData(*key);
        }
    }

    const char* ResourceManager::getData(const std::string& key)
    {
        const char* data = NULL;
        std::map<const std::string, std::tuple<const char*, uint64_t, uint64_t>>::iterator it = this->dataStore.find(key);
        if (it != this->dataStore.end())
        {
            std::tuple<const char*, uint64_t, uint64_t> payload = it->second;
            data = std::get<0>(payload);
            uint64_t size = std::get<1>(payload);
            uint64_t index = std::get<2>(payload);

            if (data && index < this->stringKeyAge.size())
            {
                this->removeData(key);

                std::tuple<const char*, uint64_t, uint64_t> new_payload = std::make_tuple(data, size, this->stringKeyAge.size());
                this->dataStore[key] = new_payload;
                this->stringKeyAge.push_back(&key);
                this->totalSizeOfData += size;
            }
        }
        else
        {
            uint64_t size = 0;
            data = this->insertData(key, size);
            if (size == 0)
            {
                data = NULL;
            }
        }

        return data;
    }

    uint64_t ResourceManager::getDataSize(const std::string& key)
    {
        uint64_t size = 0;

        std::map<const std::string, std::tuple<const char*, uint64_t, uint64_t>>::const_iterator it = this->dataStore.find(key);
        if (it != this->dataStore.end())
        {
            std::tuple<const char*, uint64_t, uint64_t> payload = it->second;
            size = std::get<1>(payload);
        }
        else
        {
            const char* data = this->insertData(key, size);
            if (data == NULL)
            {
                size = 0;
            }
        }

        return size;
    }

    const char* ResourceManager::insertData(const std::string& key, uint64_t& size)
    {
        const char* data = this->readDataFromFile(key, size);
        if (data != NULL && size > 0)
        {
            std::tuple<const char*, uint64_t, uint64_t> payload = std::make_tuple(data, size, this->stringKeyAge.size());
            this->dataStore[key] = payload;
            this->stringKeyAge.push_back(&key);
            this->totalSizeOfData += size;
        }
        else
        {
            data = NULL;
            size = 0;
        }

        if (data != NULL && size > 0 && this->totalSizeOfData > this->maxSizeOfData)
        {
            uint64_t halfMax = (this->maxSizeOfData >> 1);

            std::vector<const std::string*>::iterator it = this->stringKeyAge.begin();
            while (this->totalSizeOfData > halfMax &&
                   it != this->stringKeyAge.end())
            {
                const std::string* key = (*it);
                if (this->removeData(*key))
                {
                    it = this->stringKeyAge.begin();
                }
                else
                {
                    break;
                }
            }
        }

        return data;
    }

    bool ResourceManager::removeData(const std::string& key)
    {
        bool didRemove = false;

        std::map<const std::string, std::tuple<const char*, uint64_t, uint64_t>>::iterator it = this->dataStore.find(key);
        if (it != this->dataStore.end())
        {
            std::tuple<const char*, uint64_t, uint64_t> payload = it->second;
            const char* data = std::get<0>(payload);
            uint64_t size = std::get<1>(payload);
            uint64_t index = std::get<2>(payload);

            this->dataStore.erase(it);
            if (index < this->stringKeyAge.size())
            {
                this->stringKeyAge.erase(this->stringKeyAge.begin() + index);
            }
            delete[] data;
            this->totalSizeOfData -= size;
            didRemove = true;
        }

        return didRemove;
    }

    const char* ResourceManager::readDataFromFile(const std::string& key, uint64_t& size) const
    {
        char* memblock = NULL;

        std::ifstream file(key, std::ios::in|std::ios::binary|std::ios::ate);
        if (file.is_open())
        {
            std::streampos pos = file.tellg();
            if (pos > 0)
            {
                size = static_cast<uint64_t>(pos);
                memblock = new char[size];
                file.seekg(0, std::ios::beg);
                file.read(memblock, size);
            }
            file.close();
        }

        return memblock;
    }
}
