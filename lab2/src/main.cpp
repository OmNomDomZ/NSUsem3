#include "../include/commander.h"
#include <string>

int main(int argc, char *argv[])
{
  if (argc < 4)
  {
    throw InvalidNum();
  }
  std::string FilePath{argv[1]};
  std::string outputWAV{argv[2]};
  std::string inputParser{argv[3]};

  Commander commander{FilePath, outputWAV, inputParser};
  commander.executeCommands();

  return 0;
}
