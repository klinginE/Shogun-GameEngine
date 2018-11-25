#pragma once

//C++ includes
#include <map>
#include <tuple>
#include <vector>
#include <string>

namespace sg
{
    class ResourceManager
    {
        private:
            uint64_t maxSizeOfData;
            uint64_t totalSizeOfData;
            std::map<const std::string, std::tuple<const char*, uint64_t, uint64_t>> dataStore;
            std::vector<const std::string*> stringKeyAge;

            const char* insertData(const std::string&, uint64_t&);
            const char* readDataFromFile(const std::string&, uint64_t&) const;

        public:
            virtual ~ResourceManager();
            ResourceManager();
            ResourceManager(uint64_t);
            const char* getData(const std::string&);
            uint64_t getDataSize(const std::string&);
            bool removeData(const std::string&);
    };
}
