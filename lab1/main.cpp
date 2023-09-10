#include <iostream>

class FlatMap
{
public:
    // стандартный конструктор
    FlatMap()
    {
        key = new std::string();
        value = new std::string();
    }

    // конструктор копирования
    FlatMap(const FlatMap &other_map)
    {
        this->key = new std::string(*other_map.key);
        this->value = new std::string(*other_map.value);
    }

    // деструктор
    ~FlatMap()
    {
        // В случае std::string, деструктор автоматически управляет памятью
        // и не требует явного удаления
    }

    // перегрузка оператора присваивания
    FlatMap& operator=(const FlatMap &other_map)
    {
        delete this->key;
        delete this->value;

        this->key = new std::string(*other_map.key);
        this->value = new std::string(*other_map.value);

        return *this;
    }

    // // получить количество элементов в таблице
    // std::size_t size() const;

    // // доступ / вставка элемента по ключу
    // std::string& operator[](const std::string &key);

    // // возвращает true, если запись с таким ключом присутствует в таблице
    // bool contains(const std::string &key);

    // // удаление элемента по ключу, возвращает количество удаленных элементов (0 или 1)
    // std::size_t erase(const std::string &key);

    // // очистка таблицы, после которой size() возвращает 0, а contains() - false на любой ключ
    // void clear();

private:
    std::string *key;
    std::string *value;
};


int main()
{
    
    return 0;
}
