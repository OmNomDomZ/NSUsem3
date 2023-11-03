#include "commander.h"

Commander::Commander(const std::string &inputWAV, const std::string &outputWAV, const std::string &inputParser)
  : parser(inputParser)
{
  parser.inputWAV = inputWAV;
  parser.outputWAV = outputWAV;
}

void Commander::executeCommands()
{
  parser.ParseCommand();
}