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
        Map = new element[capacity];
    }

    // конструктор копирования
    FlatMap(const FlatMap &other_map)
    {
        capacity = other_map.capacity;
        Map = new element[capacity];
        for (std::size_t i = 0; i < capacity; ++i)
        {
            if (other_map.Map[i].key == nullptr)
            {
                break;
            }
            Map[i].key = new string(*(other_map.Map[i].key));
            Map[i].value = new string(*(other_map.Map[i].value));
        }

    }

    // деструктор
    ~FlatMap()
    {
        for (std::size_t i = 0; i < capacity; ++i)
        {
            if (Map[i].key == nullptr)
            {
                break;
            }
            delete Map[i].key;
            delete Map[i].value;
        }
        delete[] Map;
    }

    // перегрузка оператора присваивания
    FlatMap& operator=(const FlatMap &other_map)
    {
        for (std::size_t i = 0; i < capacity; ++i)
        {
            if (Map[i].key != nullptr)
            {
                delete this->Map[i].key;
                delete Map[i].value;
            }
            else
            {
                break;
            }
        }
        delete[] Map;

        capacity = other_map.capacity;
        Map = new element[capacity];
        for (std::size_t i = 0; i < capacity; ++i)
        {
            if (other_map.Map[i].key != nullptr)
            {
                Map[i].key = new string(*(other_map.Map[i].key));
                Map[i].value = new string(*(other_map.Map[i].value));
            }
            else
            {
                break;
            }
        }

        return *this;
    }

    // получить количество элементов в таблице
    std::size_t size() const
    {
        std::size_t count = 0;
        for (std::size_t i = 0; i < capacity; ++i)
        {
            if (Map[i].key != nullptr)
            {
                count++;
            }
            return count;
        }
        return count;
    }

    // доступ / вставка элемента по ключу
    string& operator[](const string &key)
    {
        std::size_t mapSize = size();
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

    // // возвращает true, если запись с таким ключом присутствует в таблице
    // bool contains(const string &key);

    // // удаление элемента по ключу, возвращает количество удаленных элементов (0 или 1)
    // std::size_t erase(const string &key);

    // // очистка таблицы, после которой size() возвращает 0, а contains() - false на любой ключ
    // void clear();

// private:
    struct element
    {
        string* key;
        string* value;
    };

    element* Map;
    std::size_t capacity;
};

// int main()
// {
//     FlatMap a = FlatMap();
//     string* d = new string("klND");
//     string* v = new string("boo");
//     a.Map[0].key = d;
//     a.Map[0].value = v;
//     FlatMap b = FlatMap();
//     string* g = new string("klkdfnD");
//     string* h = new string("ooo");
//     b.Map[0].key = g;
//     b.Map[0].value = h;
//     b = a;
//     // string value = a["klND"];
//     // cout << value << endl;
//     return 0;
// }
