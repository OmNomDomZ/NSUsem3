#include <string>
#include <algorithm>

using std::string;

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
    FlatMap();

    // конструктор копирования
    FlatMap(const FlatMap &othermMap);

    // деструктор
    ~FlatMap();

    // перегрузка оператора присваивания
    FlatMap& operator=(const FlatMap &otherMap);

    // доступ / вставка элемента по ключу
    string& operator[](const string &key);


    // удаление элемента по ключу, возвращает количество удаленных элементов (0 или 1)
    std::size_t erase(const string &key);

    // очистка таблицы, после которой size() возвращает 0, а contains() - false на любой ключ
    void clear();

};
