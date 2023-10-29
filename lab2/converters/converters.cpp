#include "converters.h"

void Converter::setParams(const std::vector<int16_t> &Params)
{
  stream = (Params[0] == SIZE_MAX) ? 0 : Params[0];
  start = (Params[1] == SIZE_MAX) ? 0 : Params[1];
  finish = (Params[2] == SIZE_MAX) ? SIZE_MAX : Params[2];
  curTime = start;
  convFinished = false;
}

Converter::Converter(const std::vector<int16_t> &Params){
  Converter::setParams(Params);
}


MuteConverter::MuteConverter(const std::vector<int16_t> &Params)
    : Converter(Params){}

void MuteConverter::convert(std::vector<int16_t>& Data1, const std::vector<int16_t>& Data2) {
  if (start < finish)
  {
    std::fill(Data1.begin(), Data1.end(), 0);
  }
  curTime++;
}


MixConverter::MixConverter(const std::vector<int16_t> &Params)
    : Converter(Params){}

void MixConverter::convert(std::vector<int16_t>& Data1, const std::vector<int16_t>& Data2) {
  if (curTime < finish)
  {
    for (size_t i = 0; Data1.size(); ++i)
    {
      Data1[i] = Data1[i] / 2 + Data2[i] / 2;
    }
    curTime++;
    convFinished = (curTime >= finish);
  }
}

