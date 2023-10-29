#include "parser.h"

#include "converters/converters.h"
#include "wav.h"

#include <string>
#include <vector>
#include <sstream>
#include <iterator>

Parser::Parser(const std::string &fileName)
{
  inputFile.open(fileName);
}

void Parser::ParseCommand()
{
  WAVLoader loadWAV;
  loadWAV.WAVOpen(inputWAV);

  std::vector <int16_t> inData;
  std::vector <int16_t> subSample;
  loadWAV.GetData(inData);
  size_t WAVDuration = loadWAV.GetDuration();

  WAVWriter outWAV;
  outWAV.WAVOpen(outputWAV);
  outWAV.WriteHeader(WAVDuration);

  std::vector<int16_t> outData;


  std::string line;
  while (std::getline(inputFile, line))
  {
    std::istringstream iss(line);
    std::string command;
    if(!(iss >> command))
    {
      break;
    }

    if (command == "mute")
    {
      std::size_t start, finish;
      if (!(iss >> start >> finish))
      {
        continue;
      }
      MuteConverter muteConverter({start, finish});
      muteConverter.convert(outData, subSample);
    }
    else if (command == "mix")
    {
      std::string param;
      std::size_t start, finish;
      if (!(iss >> param >> start >> finish))
      {
        continue;
      }
      std::string sample = param.substr(1);
      std::size_t secondSample = std::stoul(sample);
      MixConverter mixConverter({secondSample, start, finish});

    }

    else
    {}

  }

}