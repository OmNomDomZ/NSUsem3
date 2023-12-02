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

    std::size_t capacity;
    std::size_t mapSize;
    element* map;

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
    FlatMap(const FlatMap& othermMap);

    // деструктор
    ~FlatMap();

    // перегрузка оператора присваивания
    FlatMap& operator=(const FlatMap& otherMap);

    // доступ / вставка элемента по ключу
    std::string& operator[](const std::string& key);

    // получить количество элементов в таблице
    [[nodiscard]] std::size_t size() const;

    // возвращает true, если запись с таким ключом присутствует в таблице
    bool contains(const std::string& key);

    // удаление элемента по ключу, возвращает количество удаленных элементов (0 или 1)
    std::size_t erase(const std::string& key);

    // очистка таблицы, после которой size() возвращает 0, а contains() - false на любой ключ
    void clear();

    // конструктор перемещения
    FlatMap(FlatMap&& otherMap) noexcept;

    // перемещающий оператор =
    FlatMap& operator=(FlatMap&& otherMap) noexcept;


    class iterator
    {
        private:
          element* current;

        public:
          explicit iterator(element* cur) : current(cur) {};

          iterator& operator++()
          {
            ++current;
            return *this;
          }

          bool operator!=(const iterator& other) const
          {
            return current != other.current;
          }

          element& operator*() const
          {
            return *current;
          }

          [[nodiscard]] std::string getKey() const
          {
            return current->key;
          }

          [[nodiscard]] std::string  getValue() const
          {
            return current->value;
          }


    };

    // получить итератор на первый элемент
    iterator begin()
    {
          return iterator(map);
    }

    // получить итератор на элемент, следующий за последним
    iterator end()
    {
          return iterator(map + mapSize);
    }

    // получить итератор на элемент по данному ключу, или на end(), если такого ключа нет
    iterator find(const std::string& key)
    {
          indexStatus status = findIndex(key);
          if (status.contains)
          {
            return iterator(map + status.index);
          }
          return end();
    }
};

#endif
