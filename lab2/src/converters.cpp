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


MuteConverter::MuteConverter(const std::vector<int16_t>& Params)
    : Converter(Params){}

void MuteConverter::convert(std::vector<int16_t>& Data1, const std::vector<int16_t>& Data2) {
  if (start < finish && finish <= Data1.size())
  {
    std::fill(Data1.begin() + start * SAMPLE_RATE * sizeof(*Data1.data()), Data1.begin() + finish * SAMPLE_RATE * sizeof(*Data1.data()), 0);
  }
}


MixConverter::MixConverter(const std::vector<int16_t>& Params)
    : Converter(Params){}

void MixConverter::convert(std::vector<int16_t>& Data1, const std::vector<int16_t>& Data2) {
  if (start < finish && curTime < finish)
  {
    for (std::size_t i = start * SAMPLE_RATE * sizeof(*Data1.data()); i < finish * SAMPLE_RATE * sizeof(*Data1.data()); ++i)
    {
      Data1[i] = Data1[i] / 2 + Data2[i] / 2;
    }
    curTime++;
    convFinished = (curTime >= finish);
  }
}

