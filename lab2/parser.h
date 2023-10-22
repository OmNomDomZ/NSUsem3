#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class Parser
{
private:
  struct Command{
    std::string converter;
    std::vector<std::size_t> params;
  };

  std::string FileName;
  std::ifstream File;

public:


};



#endif
