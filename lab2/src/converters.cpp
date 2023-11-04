#include "converters.h"

const int32_t SAMPLE_RATE = 44100;

void Converter::setParams(const std::vector<int16_t>& Params)
{
  stream = Params[0];
  start = Params[1];
  finish = Params[2];
  curTime = start;
  convFinished = false;
}

Converter::Converter(const std::vector<int16_t>& Params){
  Converter::setParams(Params);
}

bool Converter::ConvFinished() const{
  return convFinished;
}

std::size_t Converter::GetStream() {
  return stream;
}

std::size_t Converter::ReadSecond() {
  return curTime;
}

std::size_t Converter::WriteSecond() {
  return curTime;
}

MuteConverter::MuteConverter(const std::vector<int16_t>& Params)
    : Converter(Params){}

void MuteConverter::convert(std::vector<int16_t>& mainData, const std::vector<int16_t>& subData) {
  if (start <= curTime && curTime < finish)
  {
    std::fill(mainData.begin(), mainData.end(), 0);
  }
  else
  {
    std::copy(subData.begin(), subData.end(), mainData.begin());
  }
  curTime++;
}


MixConverter::MixConverter(const std::vector<int16_t>& Params)
    : Converter(Params){}

void MixConverter::convert(std::vector<int16_t>& mainData, const std::vector<int16_t>& subData) {
  if (curTime < finish)
  {
    for (std::size_t i = 0; i < mainData.size(); ++i)
    {
      mainData[i] = mainData[i] / 2 + subData[i] / 2;
    }
    curTime++;
  }
}
