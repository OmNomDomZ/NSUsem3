#include "parser.h"

#include "../include/converters.h"
#include "../include/folder_reader.h"
#include "../include/wav.h"

#include <memory>
#include <sstream>
#include <algorithm>
#include <string>
#include <vector>

const std::size_t SAMPLE_RATE = 44100;

bool isDigit(std::string& digit)
{
  for (char const &c : digit)
  {
    if (!isdigit(c))
    {
      return false;
    }
  }
  return true;
}

Parser::Parser(const std::string& WAVPath, const std::string& outputWAV, const std::string& fileName)
{
  instructionFileName_ = fileName;
  WAVPath_ = WAVPath;
  outputWAV_ = outputWAV;
}

void Parser::ParseCommand() {
  WAVWriter outWAVWriter;
  outWAVWriter.WAVOpen(outputWAV_);

  folder_reader FolderReader(WAVPath_);
  std::vector<std::string> fileNames = FolderReader.getFileNames();

  outWAVWriter.WriteHeader(0);

  WAVLoader loadWAVMain;
  loadWAVMain.WAVOpen(outputWAV_);
  WAVLoader loadWAVSub;

  std::vector<int16_t> mainData{};
  std::vector<int16_t> subData{};
  mainData.resize(SAMPLE_RATE);
  subData.resize(SAMPLE_RATE);


  std::string line;
  std::size_t outDuration = 0;
  std::unique_ptr<Converter> converter;

  std::ifstream instructionFile;
  instructionFile.open(instructionFileName_);

  while (std::getline(instructionFile, line))
  {
    if(!line.empty() && line[0] == '#')
    {
      continue;
    }

    std::istringstream iss(line);
    std::string command;
    if (!(iss >> command))
    {
      break;
    }

    std::string sample;
    std::string start, finish;
    if (!(iss >> sample >> start >> finish)) {
      continue;
    }

    if (!isDigit(start) || !isDigit(finish))
    {
      throw InvalidArgumentPassed();
    }

    std::string SampleFile = sample.substr(1);



    std::size_t Stream = std::stoul(SampleFile);
    std::size_t Start = std::stoul(start);
    std::size_t Finish = std::stoul(finish);

    std::vector<int16_t> params = {static_cast<int16_t>(Stream), static_cast<int16_t>(Start),
                                   static_cast<int16_t>(Finish)};

    loadWAVSub.WAVOpen(fileNames[Stream - 1]);

    converter = converter->makeConverter(command, params);


    const size_t inDuration = loadWAVSub.GetDuration();

    while (!converter->ConvFinished() && converter->ReadSecond() < inDuration) {
      if (outDuration == 0)
      {
        converter->ZeroingTime();
      }

      const std::size_t readSecond = converter->ReadSecond();
      const std::size_t writeSecond = converter->WriteSecond();

      if (writeSecond < outDuration)
      {
        loadWAVMain.GetData(mainData, writeSecond);
      }
      else
      {
        std::fill(mainData.begin(), mainData.end(), 0);
      }

      if (converter->GetStream())
      {
        loadWAVSub.GetData(subData, readSecond);
      }

      converter->convert(mainData, subData);
      outWAVWriter.WriteData(mainData, writeSecond);

      outDuration = std::max(converter->WriteSecond(), outDuration);
    }
  }
  outWAVWriter.WriteHeader(outDuration);
}