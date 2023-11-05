#include "commander.h"

Commander::Commander(const std::string& WAVPath, const std::string& outputWAV, const std::string& inputParser)
  : parser(WAVPath, outputWAV, inputParser) {}

void Commander::executeCommands()
{
  parser.ParseCommand();
}