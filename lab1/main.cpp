#include <iostream>

class FlatMap
{
public:
    // стандартный конструктор
    FlatMap()
    {
        Element = new element;
        Element->key = new std::string();
        Element->value = new std::string();
    }

    // конструктор копирования
    FlatMap(const FlatMap& other_map)
    {   Element = new element;
        this->Element->key = new std::string(*other_map.Element->key);
        this->Element->value = new std::string(*other_map.Element->value);
    }

    // деструктор
    ~FlatMap()
    {
        // В случае std::string, деструктор автоматически управляет памятью
        // и не требует явного удаления
    }

    // перегрузка оператора присваивания
    FlatMap& operator=(const FlatMap& other_map)
    {
        delete this->Element->key;
        delete this->Element->value;

        this->Element->key = new std::string(*other_map.Element->key);
        this->Element->value = new std::string(*other_map.Element->value);

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
    struct element
    {
        std::string* key;
        std::string* value;
    };

    element* Element;
};


int main()
{
    return 0;
}
