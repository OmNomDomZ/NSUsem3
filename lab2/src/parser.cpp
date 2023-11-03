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
  WAVLoader loadWAV;

  std::vector<int16_t> inData;
  std::vector<int16_t> subData;
  //  inData.resize(WAVDuration * SAMPLE_RATE);

  WAVWriter outWAVwriter;
  outWAVwriter.WAVOpen(outputWAV);
  outWAVwriter.WriteHeader(0);
  WAVLoader outWAVloader;
  outWAVloader.WAVOpen(outputWAV);
  //  loadWAV.GetData(inData, 0);

  std::string line;
  size_t outDuration;
  while (std::getline(inputFile, line)) {
    std::istringstream iss(line);
    std::string command;
    if (!(iss >> command)) {
      break;
    }
    std::string sample;
    std::size_t start, finish;
    if (!(iss >> sample >> start >> finish)) {
      continue;
    }

    std::string subSampleFile = sample.substr(1);
    WAVLoader subWAV;
    subWAV.WAVOpen(subSampleFile);
    //      subWAV.GetData(subData);

    std::size_t subStream = std::stoul(subSampleFile);
    std::vector<int16_t> params = {static_cast<int16_t>(subStream), static_cast<int16_t>(start),
                                   static_cast<int16_t>(finish)};
    std::unique_ptr<Converter> converter;

    if (subStream) {
      loadWAV.WAVOpen(inputWAV);
    }

    if (command == "mute") {
      converter = std::make_unique<MuteConverter>(params);
    } else if (command == "mix") {
      converter = std::make_unique<MixConverter>(params);
    } else {
      throw std::exception();
    }

    const size_t inDuration = loadWAV.GetDuration();

    while (!converter->ConvFinished() && converter->readSecond() < inDuration) {
      const size_t readSecond = converter->readSecond();

      if (converter->readSecond() < outDuration){
        outWAVloader.GetData(inData, readSecond);
      }
      else{
        std::fill(inData.begin(), inData.end(), 0);
      }

      if (converter->GetStream()){
        subWAV.GetData(subData, readSecond);
      }

      converter->convert(inData, subData);
      outWAVwriter.WriteData(inData, readSecond);
      outDuration = std::max(converter->readSecond(), outDuration);
    }
  }
  outWAVwriter.WriteHeader(outDuration);
}