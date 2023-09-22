#include "FlatMap.h"

FlatMap::FlatMap()
{
    capacity = 10;
    mapSize = 0;
    Map = new element[capacity];
}

FlatMap::FlatMap(const FlatMap& otherMap)
{
    capacity = 10;
    mapSize = 0;
    Map = new element[capacity];
    std::copy(otherMap.Map, otherMap.Map + mapSize, Map);
}

FlatMap::~FlatMap()
{
    delete[] Map;
}

FlatMap& FlatMap::operator=(const FlatMap &otherMap)
{
    if(this != &otherMap)
        {
            delete[] Map;
            capacity = otherMap.capacity;
            mapSize = otherMap.mapSize;
            Map = new element[capacity];

            std::copy(otherMap.Map, otherMap.Map + mapSize, Map);
        }
        return *this;
}

string& FlatMap::operator[](const string& key)
{
    indexStatus status = findIndex(key);

    if (status.contains == true)
    {
        return (Map[status.index].value);
    }

    else
    {
        if (capacity == mapSize)
        {
            capacity = 2 * capacity;
            element *newMap = new element[capacity];
            std::copy(Map, Map + mapSize, newMap);
            delete[] Map;
            Map = newMap;
        }

        Map[mapSize].key = key;
        mapSize++;
        return (Map[mapSize - 1].value);
    }
}

size_t FlatMap::erase(const string& key)
{
    indexStatus status = findIndex(key);

    if (Map[status.index].key == key)
    {
        std::copy(Map + status.index + 1, Map + mapSize, Map + status.index);
        mapSize--;
        return 1;
    }

    return 0;
}

void FlatMap::clear()
{
    delete[] Map;
    capacity = 10;
    mapSize = 0;
    Map = new element[capacity];
}
