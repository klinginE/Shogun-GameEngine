//Shogun includes
#include <Shogun/Management/ResourceManager.hpp>

//C++ includes
#include <limits.h>

namespace sg
{
    ResourceManager::ResourceManager() :
    maxSizeOfData(std::numeric_limits<uint64_t>::max()),
    totalSizeOfData(0)
    {
    }

    ResourceManager::ResourceManager(uint64_t inMaxSizeOfData) :
    maxSizeOfData(inMaxSizeOfData),
    totalSizeOfData(0)
    {
    }

    void* ResourceManager::getData(std::string key)
    {
        void* data = NULL;
        std::map<std::string, std::tuple<void*, uint64_t, uint64_t>>::iterator it = this->dataStore.find(key);
        if (it != this->dataStore.end())
        {
            std::tuple<void*, uint64_t, uint64_t> payload = it->second;
            data = std::get<0>(payload);
        }
        else
        {
            //TO DO
        }

        return data;
    }

    uint64_t ResourceManager::getDataSize(std::string key)
    {
        uint64_t size = 0;

        std::map<std::string, std::tuple<void*, uint64_t, uint64_t>>::iterator it = this->dataStore.find(key);
        if (it != this->dataStore.end())
        {
            std::tuple<void*, uint64_t, uint64_t> payload = it->second;
            size = std::get<1>(payload);
        }

        return size;
    }

    bool ResourceManager::removeData(std::string key)
    {
        std::map<std::string, std::tuple<void*, uint64_t, uint64_t>>::iterator it = this->dataStore.find(key);
        if (it != this->dataStore.end())
        {
            std::tuple<void*, uint64_t, uint64_t> payload = it->second;
            uint64_t size = std::get<1>(payload);
            uint64_t index = std::get<2>(payload);

            this->dataStore.erase(it);
            if (index < this->stringKeyAge.size())
            {
                this->stringKeyAge.erase(this->stringKeyAge.begin() + index);
            }
            this->totalSizeOfData -= size;
        }

        return true;
    }
}
