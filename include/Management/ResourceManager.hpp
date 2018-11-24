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
            std::map<std::string, std::tuple<void*, uint64_t, uint64_t>> dataStore;
            std::vector<std::string> stringKeyAge;

        public:
            virtual ~ResourceManager();
            ResourceManager();
            ResourceManager(uint64_t);
            void* getData(std::string);
            uint64_t getDataSize(std::string);
            bool removeData(std::string);
    };
}
