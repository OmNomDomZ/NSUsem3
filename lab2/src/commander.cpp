#include "commander.h"

Commander::Commander(const std::string &WAVPath, const std::string &outputWAV, const std::string &inputParser)
  : parser(inputParser)
{
  parser.WAVPath_ = WAVPath;
  parser.outputWAV = outputWAV;
}

void Commander::executeCommands()
{
  parser.ParseCommand();
}