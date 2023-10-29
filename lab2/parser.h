#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <fstream>

class Parser
{
private:
  std::ifstream inputFile;
  std::string inputWAV;
  std::string outputWAV;


public:
  Parser(const std::string& fileName);


  void ParseCommand();


};



#endif
