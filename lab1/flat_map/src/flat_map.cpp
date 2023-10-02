#include "flat_map.h"

#include <memory>

using std::string;

// стандартный конструктор
FlatMap::FlatMap() : capacity(startCapacity), mapSize(0), map(new element[capacity])
{
}

// конструктор копирования
FlatMap::FlatMap(const FlatMap& otherMap) : capacity(otherMap.capacity), mapSize(otherMap.mapSize), map(new element[capacity])
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
      std::unique_ptr<element[]> tmp = std::make_unique<element[]>(otherMap.capacity);
      std::copy_n(otherMap.map, otherMap.mapSize, tmp.get());
      delete[] map;
      mapSize = otherMap.mapSize;
      capacity = otherMap.capacity;
      map = tmp.release();
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
            auto newMap = new element[capacity];
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
[[nodiscard]] std::size_t FlatMap::size() const
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
    if (this != &otherMap)
    {
      std::unique_ptr<element[]> tmp = std::make_unique<element[]>(otherMap.capacity);
      std::copy_n(otherMap.map, otherMap.mapSize, tmp.get());

      delete[] map;

      capacity = otherMap.capacity;
      mapSize = otherMap.mapSize;
      map = tmp.release();

      otherMap.capacity = startCapacity;
      otherMap.mapSize = 0;
      otherMap.map = nullptr;
    }

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
