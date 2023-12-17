#include <iostream>
#include <fstream>
#include <sstream>
#include <tuple>
#include <vector>
#include <stdexcept>

template<typename... Args>
class CsvParser {
private:
  std::ifstream& file;
  int skipLines;

  class Iterator {
  private:
    std::ifstream& file;
    int currentLine;
    int skipLines;
    std::string currentRow;

    bool readNextLine() {
      if (file.eof()) return false;
      std::getline(file, currentRow);
      currentLine++;
      return true;
    }

    std::vector<std::string> splitRow(const std::string& row) {
      std::vector<std::string> values;
      std::stringstream ss(row);
      std::string value;
      while (std::getline(ss, value, ',')) {
        values.push_back(value);
      }
      return values;
    }

  public:
    using iterator_category = std::input_iterator_tag;
    using value_type = std::tuple<Args...>;
    using difference_type = std::ptrdiff_t;
    using pointer = value_type*;
    using reference = value_type&;

    Iterator(std::ifstream& file, int skip) : file(file), skipLines(skip), currentLine(0) {
      while (skipLines > 0) {
        readNextLine();
        skipLines--;
      }
    }

    Iterator& operator++() {
      if (!readNextLine()) {
        currentLine = -1; // end iterator
      }
      return *this;
    }

    bool operator!=(const Iterator& other) const {
      return currentLine != other.currentLine;
    }

    value_type operator*() {
      std::vector<std::string> values = splitRow(currentRow);
      if (values.size() != sizeof...(Args)) {
        throw std::runtime_error("Number of columns does not match tuple size.");
      }
      return std::make_tuple(parseValue<Args>(values)...);
    }

    template<typename T>
    T parseValue(const std::vector<std::string>& values) {
      std::stringstream ss(values[sizeof...(Args) - sizeof...(T)]);
      T result;
      ss >> result;
      return result;
    }
  };

public:
  CsvParser(std::ifstream& file, int skipLines = 0) : file(file), skipLines(skipLines) {}

  Iterator begin() {
    return Iterator(file, skipLines);
  }

  Iterator end() {
    return Iterator(file, -1); // end iterator
  }
};

int main() {
  std::ifstream csv_stream("test.csv");
  if (!csv_stream.is_open()) {
    std::cerr << "Failed to open file!" << std::endl;
    return 1;
  }

  try {
    CsvParser<int, std::string, double> parser(csv_stream, 1 /* skip first line */);
    for (const std::tuple<int, std::string, double>& row : parser) {
      std::cout << std::get<0>(row) << ", " << std::get<1>(row) << ", " << std::get<2>(row) << "\n";
    }
  } catch (const std::exception& e) {
    std::cerr << "Error: " << e.what() << std::endl;
  }

  csv_stream.close();

  return 0;
}
