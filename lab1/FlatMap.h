#ifndef FLATMAP
#define FLATMAP

#include <string>
#include <algorithm>

class FlatMap
{

private:
    const std::size_t startCapacity = 2;

    struct element
    {
        std::string key;
        std::string value;
    };

    element* Map;
    std::size_t capacity;
    std::size_t mapSize;

    struct indexStatus
    {
        std::size_t index;
        bool contains;
    };

    indexStatus findIndex(const std::string& key);

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
    std::string& operator[](const std::string &key);


    // удаление элемента по ключу, возвращает количество удаленных элементов (0 или 1)
    std::size_t erase(const std::string &key);

    // очистка таблицы, после которой size() возвращает 0, а contains() - false на любой ключ
    void clear();

};

#endif
