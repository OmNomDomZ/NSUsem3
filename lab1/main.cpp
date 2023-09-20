#include <iostream>
#include <string>
#include <algorithm>

using std::string;
using std::cout;
using std::endl;

class FlatMap
{

private:
    struct element
    {
        string key;
        string value;
    };

    element* Map;
    std::size_t capacity;
    std::size_t mapSize;

    struct indexStatus
    {
        std::size_t index;
        bool contains;
    };

    bool compareKey(const element& left, const element& right)
    {
        return left.key < right.key;
    }

    indexStatus findIndex(const string& key)
    {
        std::sort(Map, Map + mapSize, compareKey);
        std::size_t left = 0;
        std::size_t right = mapSize - 1;
        std::size_t mid;

        while (right >= left)
        {
            mid = left + (right - left) / 2;

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
                right = mid - 1;
            }
        }

        return {mapSize, false};
    }

public:
    // стандартный конструктор
    FlatMap()
    {
        capacity = 10;
        mapSize = 0;
        Map = new element[capacity];
    }

    // конструктор копирования
    FlatMap(const FlatMap &other_map)
    {
        capacity = other_map.capacity;
        mapSize = other_map.mapSize;
        Map = new element[capacity];
        std::copy(other_map.Map, other_map.Map + mapSize, Map);
    }

    // деструктор
    ~FlatMap()
    {
        delete[] Map;
    }

    // перегрузка оператора присваивания
    FlatMap& operator=(const FlatMap &other_map)
    {
        if(this != &other_map)
        {
            delete[] Map;
            capacity = other_map.capacity;
            mapSize = other_map.mapSize;
            Map = new element[capacity];

            std::copy(other_map.Map, other_map.Map + mapSize, Map);
        }
        return *this;
    }

    // доступ / вставка элемента по ключу
    string& operator[](const string &key)
    {

        indexStatus status = findIndex(key);

        if (status.contains == false)
        {
            Map[status.index].key = key;
        }

        else
        {
            return (Map[status.index].value);
        }
    }


    // удаление элемента по ключу, возвращает количество удаленных элементов (0 или 1)
    std::size_t erase(const string &key)
    {
        for (std::size_t i = 0; i < mapSize; ++i)
        {
            if (Map[i].key == key)
            {
                std::copy(Map + i + 1, Map + mapSize, Map + i);
                mapSize--;
                return 1;
            }
        }
        return 0;
    }

    // очистка таблицы, после которой size() возвращает 0, а contains() - false на любой ключ
    void clear()
    {
        mapSize = 0;
    }

};

// int main()
// {
//     FlatMap a;
//     string* key = new string("klasdnf");
//     string* ke1 = new string("asdnf");
//     string val;
//     FlatMap b;
//     FlatMap c = a;
//     // val = a[*key];
//     // val = b[*ke1];
//     // a[*key] = "alskgn";
//     // b = a;
//     // bool v = a.contains(*key);
//     // std::size_t y = a.erase(*key);
//     // a.clear();
//     // bool asd = a.contains(*key);
//     return 0;
// }
