#include "parser.h"

#include "converters.h"
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
  outWAVWriter.WriteHeader(0);


  WAVLoader loadWAVMain;
  loadWAVMain.WAVOpen(inputWAV);
  WAVLoader loadWAVSub;

  std::vector<int16_t> mainData{};
  std::vector<int16_t> subData;
  mainData.resize(SAMPLE_RATE);
  subData.resize(SAMPLE_RATE);

//  WAVWriter outWAVwriter;
//  outWAVwriter.WAVOpen(outputWAV);
//  outWAVwriter.WriteHeader(0);
//
//  WAVLoader outWAVloader;
//  outWAVloader.WAVOpen(outputWAV);
//  //  loadWAV.GetData(inData, 0);

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

    if (command == "mute")
    {
      std::size_t start, finish;
      if (!(iss >> start >> finish)) {
        continue;
      }
      std::vector<int16_t> params = {0, static_cast<int16_t>(start), static_cast<int16_t>(finish)};

      converter = std::make_unique<MuteConverter>(params);
    }

    else if(command == "mix")
    {
      std::string sample;
      std::size_t start, finish;
      if (!(iss >> sample >> start >> finish)) {
        continue;
      }

      std::string subSampleFile = sample.substr(1);

      loadWAVSub.WAVOpen(subSampleFile);
//      subWAV.GetData(subData);

      std::size_t subStream = std::stoul(subSampleFile);
      std::vector<int16_t> params = {static_cast<int16_t>(subStream), static_cast<int16_t>(start),
                                     static_cast<int16_t>(finish)};

      converter = std::make_unique<MixConverter>(params);
    }

    else
    {
      throw std::exception();
    }


//    if (subStream) {
//      loadWAV.WAVOpen(inputWAV);
//    }
//

    const size_t inDuration = loadWAVMain.GetDuration();

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