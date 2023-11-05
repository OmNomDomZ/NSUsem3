#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <fstream>

class Parser
{
private:
  std::string instructionFileName_;
  std::string WAVPath_;
  std::string outputWAV_;

public:

  Parser(const std::string& fileName, const std::string& WAVPath, const std::string& outputWAV);

  void ParseCommand();
};



#endif
