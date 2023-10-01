#include "flat_map.h"
#include "iostream"

using std::string;

// стандартный конструктор
FlatMap::FlatMap() : capacity(startCapacity), mapSize(0), map(new element[capacity])
{
}

// конструктор копирования
FlatMap::FlatMap(const FlatMap& otherMap) : capacity(otherMap.capacity), mapSize(otherMap.capacity), map(new element[capacity])
{
    std::copy(otherMap.map, otherMap.map + mapSize, map);
}

// деструктор
FlatMap::~FlatMap()
{
    delete[] map;
}

// перегрузка оператора присваивания
FlatMap& FlatMap::operator=(const FlatMap& otherMap)
{
    if (this != &otherMap)
    {
        delete[] map;
        capacity = otherMap.capacity;
        mapSize = otherMap.mapSize;
        map = new element[capacity];

        std::copy(otherMap.map, otherMap.map + mapSize, map);
    }
    return *this;
}

// доступ / вставка элемента по ключу
string& FlatMap::operator[](const string& key)
{
    indexStatus status = findIndex(key);

    if (status.contains)
    {
        return (map[status.index].value);
    }
    else
    {
        if (capacity == mapSize)
        {
            capacity = 2 * capacity;
            element *newMap = new element[capacity];
            std::copy(map, map + mapSize, newMap);
            delete[] map;
            map = newMap;
        }

        for (std::size_t i = mapSize; status.index < i; --i)
        {
            map[i] = std::move(map[i - 1]);
        }

        map[status.index].key = key;
        mapSize++;
        return (map[status.index].value);
    }
}

// получить количество элементов в таблиц
std::size_t FlatMap::size() const
{
    return (mapSize);
}

// возвращает true, если запись с таким ключом присутствует в таблице
bool FlatMap::contains(const std::string& key)
{
    indexStatus status = findIndex(key);
    return (status.contains);
}

// удаление элемента по ключу, возвращает количество удаленных элементов (0 или 1)
std::size_t FlatMap::erase(const string& key)
{
    indexStatus status = findIndex(key);

    if (status.contains)
    {
        std::copy(map + status.index + 1, map + mapSize, map + status.index);
        mapSize--;
        return 1;
    }

    return 0;
}

// очистка таблицы, после которой size() возвращает 0, а contains() - false на любой ключ
void FlatMap::clear()
{
    delete[] map;
    capacity = startCapacity;
    mapSize = 0;
    map = new element[capacity];
}

// конструктор перемещения
FlatMap::FlatMap(FlatMap&& otherMap) noexcept : capacity(otherMap.capacity), mapSize(otherMap.mapSize), map(otherMap.map)
{
    otherMap.map = nullptr;
    otherMap.capacity = startCapacity;
    otherMap.mapSize = 0;
}

// перемещающий оператор =
FlatMap& FlatMap::operator=(FlatMap&& otherMap) noexcept
{
    if (this == &otherMap)
    {
        return *this;
    }

    delete[] map;
    capacity = otherMap.capacity;
    mapSize = otherMap.mapSize;
    map = otherMap.map;

    otherMap.map = nullptr;
    otherMap.capacity = startCapacity;
    otherMap.mapSize = 0;

    return *this;
}

FlatMap::indexStatus FlatMap::findIndex(const string& key)
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

        if (map[mid].key == key)
        {
            return {mid, true};
        }
        else if (map[mid].key < key)
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
