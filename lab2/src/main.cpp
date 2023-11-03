#include "commander.h"
#include <iostream>
#include <string>
#include <converters.h>
#include "wav.h"
int main(int argc, char *argv[])
{
  if (argc < 4)
  {
    return 0;
  }
  std::string inputWAV{argv[1]};
  std::string outputWAV{argv[2]};
  std::string inputParser{argv[3]};

  Commander commander(inputWAV, outputWAV, inputParser);
  commander.executeCommands();

  return 0;
}
