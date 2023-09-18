#include <iostream>
#include <string>

using std::string;
using std::cout;
using std::endl;

class FlatMap
{
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
        for (std::size_t i = 0; i < mapSize; ++i)
        {
            Map[i].key = new string(*(other_map.Map[i].key));
            Map[i].value = new string(*(other_map.Map[i].value));
        }

    }

    // деструктор
    ~FlatMap()
    {
        for (std::size_t i = 0; i < mapSize; ++i)
        {
            delete Map[i].key;
            delete Map[i].value;
        }
        delete[] Map;
    }

    // перегрузка оператора присваивания
    FlatMap& operator=(const FlatMap &other_map)
    {
        for (std::size_t i = 0; i < mapSize; ++i)
        {
            delete Map[i].key;
            delete Map[i].value;
        }
        delete[] Map;

        capacity = other_map.capacity;
        mapSize = other_map.mapSize;
        Map = new element[capacity];
        for (std::size_t i = 0; i < mapSize; ++i)
        {
            Map[i].key = new string(*(other_map.Map[i].key));
            Map[i].value = new string(*(other_map.Map[i].value));
        }

        return *this;
    }

    // получить количество элементов в таблице
    std::size_t size() const
    {
        return mapSize;
    }

    // доступ / вставка элемента по ключу
    string& operator[](const string &key)
    {
        if (mapSize != capacity)
        {
            for (std::size_t i = 0; i < mapSize; ++i)
            {
                if (*Map[i].key == key)
                {
                    return (*Map[i].value);
                }
            }
        }

        if (mapSize == capacity)
        {
            capacity *= 2;
            element* newMap = new element[capacity];
            for (std::size_t i = 0; i < mapSize; ++i)
            {
                newMap[i].key = new string(*(Map[i].key));
                newMap[i].value = new string(*(Map[i].value));
            }
            Map = newMap;
            delete[] newMap;
        }
        Map[mapSize].key = new string(key);
        Map[mapSize].value = new string("");
        return *(Map[mapSize].value);
    }

    // возвращает true, если запись с таким ключом присутствует в таблице
    bool contains(const string &key)
    {
        std::size_t left = 0;
        std::size_t right = mapSize - 1;

        while (left <= right)
        {
            std::size_t mid = left + (right - left) / 2;

            if (*(Map[mid].key) == key)
            {
                return true;
            }
            else if (*(Map[mid].key) < key)
            {
                left = mid + 1;
            }
            else
            {
                right = mid - 1;
            }
        }

        return false;   
    }

    // удаление элемента по ключу, возвращает количество удаленных элементов (0 или 1)
    std::size_t erase(const string &key)
    {
        for (std::size_t i = 0; i < mapSize; ++i)
        {
            if (*(Map[i].key) == key)
            {
                delete Map[i].key;
                delete Map[i].value;
                Map[i].key = nullptr;
                Map[i].value = nullptr;
                mapSize--;
                return 1;
            }
        }
        return 0;
    }

    // очистка таблицы, после которой size() возвращает 0, а contains() - false на любой ключ
    void clear()
    {
        for(std::size_t i = 0; i < mapSize; ++i)
        {
            delete Map[i].key;
            delete Map[i].value;
            Map[i].key = nullptr;
            Map[i].value = nullptr;
            mapSize = 0;
        }
    }

private:
    struct element
    {
        string* key;
        string* value;
    };

    element* Map;
    std::size_t capacity;
    std::size_t mapSize;
};

// int main()
// {
//     FlatMap a;
//     string* key = new string("klasdnf");
//     string* ke1 = new string("asdnf");
//     string val;
//     FlatMap b;
//     FlatMap c = a;
//     val = a[*key];
//     val = b[*ke1];
//     a[*key] = "alskgn";
//     b = a;
//     bool v = a.contains(*key);
//     std::size_t y = a.erase(*key);
//     a.clear();
//     int j = a.size();
//     bool asd = a.contains(*key);
//     return 0;
// }
