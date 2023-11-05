#include "parser.h"

#include "converters.h"
#include "folder_reader.h"
#include "wav.h"

#include <memory>
#include <sstream>
#include <string>
#include <vector>

const std::size_t SAMPLE_RATE = 44100;

Parser::Parser(const std::string &fileName) { inputFile.open(fileName); }

void Parser::ParseCommand() {
  WAVWriter outWAVWriter;
  outWAVWriter.WAVOpen(outputWAV);

  folder_reader FolderReader(WAVPath_);
  std::vector<std::string> fileNames = FolderReader.getFileNames();

//  std::string OutputPath = WAVPath_ + "output.wav";
//  outWAVWriter.WAVOpen(OutputPath);
  outWAVWriter.WriteHeader(0);

  WAVLoader loadWAVMain;
  loadWAVMain.WAVOpen(outputWAV);
  WAVLoader loadWAVSub;

  std::vector<int16_t> mainData{};
  std::vector<int16_t> subData;
  mainData.resize(SAMPLE_RATE);
  subData.resize(SAMPLE_RATE);


  std::string line;
  std::size_t outDuration = 0;
  std::unique_ptr<Converter> converter;

  while (std::getline(inputFile, line)) {
    std::istringstream iss(line);
    std::string command;
    if (!(iss >> command))
    {
      break;
    }

    std::string sample;
    std::size_t start, finish;
    if (!(iss >> sample >> start >> finish)) {
      continue;
    }

    std::string SampleFile = sample.substr(1);


    std::size_t Stream = std::stoul(SampleFile);
    std::vector<int16_t> params = {static_cast<int16_t>(Stream), static_cast<int16_t>(start),
                                   static_cast<int16_t>(finish)};

    loadWAVSub.WAVOpen(fileNames[Stream - 1]);

    converter = converter->makeConverter(command, params);


    const size_t inDuration = loadWAVSub.GetDuration();

    while (!converter->ConvFinished() && converter->ReadSecond() < inDuration) {
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