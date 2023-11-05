#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <fstream>

class Parser
{
//private:
//  std::ifstream inputFile;
//  std::string inputWAV;
//  std::string outputWAV;


public:
  std::ifstream inputFile;
  std::string WAVPath_;
  std::string outputWAV;

  Parser(const std::string& fileName);


  void ParseCommand();


};



#endif
