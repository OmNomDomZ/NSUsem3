#ifndef CONVERTERS
#define CONVERTERS

#include <iostream>
#include <vector>
#include <algorithm>

class Converter
{
public:
  Converter() = default;

  Converter(const std::vector<size_t>& Params);

  virtual ~Converter() = default;

  void setParams(const std::vector<size_t>& Params);

  virtual void convert(std::vector<size_t>& Data1, const std::vector<size_t>& Data2);

protected:
  std::size_t stream;
  std::size_t start;
  std::size_t curTime;
  std::size_t finish;
  bool convFinished;
};

class MuteConverter : public Converter
{
public:
  MuteConverter() = default;

  MuteConverter(const std::vector<size_t>& Params);

  ~MuteConverter() override = default;

  void convert(std::vector<size_t>& Data1, const std::vector<size_t> &Data2) override;
};

class MixConverter : public Converter
{
public:
  MixConverter() = default;

  MixConverter(const std::vector<size_t>& Params);

  ~MixConverter() override = default;

  void convert(std::vector<size_t>& Data1, const std::vector<size_t>& Data2) override;
};



#endif
