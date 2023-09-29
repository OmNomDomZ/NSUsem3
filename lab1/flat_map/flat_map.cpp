#include "flat_map.h"

using std::string;

// стандартный конструктор
FlatMap::FlatMap() :
capacity(startCapacity), mapSize(0), Map(new element[capacity])
{
}

// конструктор копирования
FlatMap::FlatMap(const FlatMap &otherMap) :
capacity(otherMap.capacity), mapSize(otherMap.capacity), Map(new element[capacity])
{
    std::copy(otherMap.Map, otherMap.Map + mapSize, Map);
}

// деструктор
FlatMap::~FlatMap()
{
    delete[] Map;
}

// перегрузка оператора присваивания
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

// доступ / вставка элемента по ключу
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
            Map = std::move(newMap);
        }

        std::copy(Map + status.index, Map + mapSize, Map + status.index + 1);
        Map[status.index].key = key;
        mapSize++;
        return (Map[status.index].value);
    }
}

// получить количество элементов в таблиц
std::size_t FlatMap::size() const
{
    return (mapSize);
}

// возвращает true, если запись с таким ключом присутствует в таблице
bool FlatMap::contains(const std::string &key)
{
    indexStatus status = findIndex(key);
    return (status.contains);
}

// удаление элемента по ключу, возвращает количество удаленных элементов (0 или 1)
std::size_t FlatMap::erase(const string &key)
{
    indexStatus status = findIndex(key);

    if (status.contains)
    {
        std::copy(Map + status.index + 1, Map + mapSize, Map + status.index);
        mapSize--;
        return 1;
    }

    return 0;
}

// очистка таблицы, после которой size() возвращает 0, а contains() - false на любой ключ
void FlatMap::clear()
{
    delete[] Map;
    capacity = startCapacity;
    mapSize = 0;
    Map = new element[capacity];
}

// конструктор перемещения
FlatMap::FlatMap(FlatMap &&otherMap) noexcept :
capacity(otherMap.capacity), mapSize(otherMap.mapSize), Map(std::move(otherMap.Map))
{
    otherMap.Map = nullptr;
    otherMap.capacity = startCapacity;
    otherMap.mapSize = 0;
}

// перемещающий оператор =
FlatMap &FlatMap::operator=(FlatMap &&otherMap) noexcept
{
    if (this == &otherMap)
    {
        return *this;
    }

    delete[] Map;
    capacity = otherMap.capacity;
    mapSize = otherMap.mapSize;
    Map = std::move(otherMap.Map);

    otherMap.Map = nullptr;
    otherMap.capacity = startCapacity;
    otherMap.mapSize = 0;

    return *this;
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
