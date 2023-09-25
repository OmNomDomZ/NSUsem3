#include "FlatMap.h"

using std::string;

FlatMap::FlatMap() : capacity(startCapacity), mapSize(0), Map(new element[capacity]) {}

FlatMap::FlatMap(const FlatMap &otherMap) : capacity(otherMap.capacity), mapSize(otherMap.capacity), Map(new element[capacity])
{
    std::copy(otherMap.Map, otherMap.Map + mapSize, Map);
}

FlatMap::~FlatMap()
{
    delete[] Map;
}

FlatMap &FlatMap::operator=(const FlatMap &otherMap)
{
    if (this != &otherMap)
    {
        delete[] Map;
        capacity = otherMap.capacity;
        mapSize = otherMap.mapSize;
        Map = new element[capacity];

        std::copy(otherMap.Map, otherMap.Map + mapSize, Map);
    }
    return *this;
}

string &FlatMap::operator[](const string &key)
{
    indexStatus status = findIndex(key);

    if (status.contains)
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

        std::copy(Map + status.index, Map + mapSize, Map + status.index + 1);
        Map[status.index].key = key;
        mapSize++;
        return (Map[status.index].value);
    }
}

std::size_t FlatMap::size() const
{
    return(mapSize);
}

bool FlatMap::contains(const std::string& key)
{
    indexStatus status = findIndex(key);
    return (status.contains);
}

size_t FlatMap::erase(const string &key)
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

FlatMap::indexStatus FlatMap::findIndex(const string &key)
{
    if (mapSize == 0)
    {
        return {0, false};
    }

    std::size_t left = 0;
    std::size_t right = mapSize - 1;
    std::size_t mid;

    while (right >= left)
    {
        mid = (left + right) / 2;

        if (Map[mid].key == key)
        {
            return {mid, true};
        }
        else if (Map[mid].key < key)
        {
            left = mid + 1;
        }
        else
        {
            if (mid == 0)
            {
                break;
            }
            right = mid - 1;
        }
    }

    return {left, false};
}
