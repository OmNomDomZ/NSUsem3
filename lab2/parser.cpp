#include "parser.h"

#include "converters/converters.h"
#include "wav.h"

#include <string>
#include <vector>
#include <sstream>

Parser::Parser(const std::string &fileName)
{
  inputFile.open(fileName);
}

void Parser::ParseCommand()
{
  WAVLoader loadWAV;
  loadWAV.WAVOpen(inputWAV);

  std::vector <int16_t> inData;
  std::vector <int16_t> subData;
  loadWAV.GetData(inData);
  size_t WAVDuration = loadWAV.GetDuration();

  WAVWriter outWAV;
  outWAV.WAVOpen(outputWAV);
  outWAV.WriteHeader(WAVDuration);


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
      std::vector<int16_t> params = {static_cast<int16_t>(start), static_cast<int16_t>(finish)};
      MuteConverter muteConverter(params);
      muteConverter.convert(inData, subData);
    }
    else if (command == "mix")
    {
      std::string sample;
      std::size_t start, finish;
      if (!(iss >> sample >> start >> finish))
      {
        continue;
      }
      std::string subSampleFile = sample.substr(1);
      WAVLoader subWAV;
      subWAV.WAVOpen(subSampleFile);
      subWAV.GetData(subData);

      std::size_t subSample = std::stoul(subSampleFile);
      std::vector<int16_t> params = {static_cast<int16_t>(subSample), static_cast<int16_t>(start), static_cast<int16_t>(finish)};
      MixConverter mixConverter(params);
      mixConverter.convert(inData, subData);
    }


    else
    {}

    for (std::size_t i = 0; i < WAVDuration; ++i)
    {
      outWAV.WriteData(inData, i);
    }
  }

}