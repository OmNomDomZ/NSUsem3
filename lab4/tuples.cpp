#include <iostream>
#include <tuple>

template <size_t Index, typename... Args>
typename std::enable_if<Index == sizeof...(Args)>::type
print_tuple(std::ostream&, const std::tuple<Args...>&) {}

template <size_t Index = 0, typename... Args>
    typename std::enable_if<Index < sizeof...(Args)>::type
                              print_tuple(std::ostream& os, const std::tuple<Args...>& t) {
  if (Index != 0)
    os << ", ";
  os << std::get<Index>(t);
  print_tuple<Index + 1>(os, t);
}

template <typename... Args>
std::ostream& operator<<(std::ostream& os, const std::tuple<Args...>& t) {
  print_tuple(os, t);
  return os;
}

int main() {
  std::tuple<int, std::string, double> t = {5, "abcd", 3.14};
  std::cout << t << std::endl;

  return 0;
}
