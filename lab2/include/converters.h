#pragma once

#include <iostream>
#include <vector>
#include <cstdint>
#include <algorithm>

class Converter
{
public:
  Converter() = default;

  Converter(const std::vector<int16_t>& Params);

  virtual ~Converter() = default;

  void setParams(const std::vector<int16_t>& Params);

  virtual void convert(std::vector<int16_t>& Data1, const std::vector<int16_t>& Data2) = 0;

  bool ConvFinished() const;

  std::size_t GetStream();

  std::size_t ReadSecond();

  std::size_t WriteSecond();

protected:
  std::size_t stream;
  std::size_t start;
  std::size_t curTime;
  std::size_t finish;
  bool convFinished;
//  std::size_t InStream;
};

class MuteConverter : public Converter
{
public:
  MuteConverter() = default;

  MuteConverter(const std::vector<int16_t>& Params);

  ~MuteConverter() override = default;

  void convert(std::vector<int16_t>& Data1, const std::vector<int16_t>& Data2) override;
};

class MixConverter : public Converter
{
public:
  MixConverter() = default;

  MixConverter(const std::vector<int16_t>& Params);

  ~MixConverter() override = default;

  void convert(std::vector<int16_t>& Data1, const std::vector<int16_t>& Data2) override;
};
