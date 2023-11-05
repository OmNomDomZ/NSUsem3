#ifndef COMMANDER_H
#define COMMANDER_H

#include "converters.h"
#include "parser.h"
#include "wav.h"

class Commander {
private:
  WAVLoader wavLoader;
  WAVWriter wavWriter;
  MuteConverter muteConverter;
  MixConverter mixConverter;
  Parser parser;

public:
  Commander(const std::string& WAVPath, const std::string& outputWAV, const std::string& inputParser);

  void executeCommands();
};

#endif