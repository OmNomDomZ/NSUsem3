#ifndef CONVERTERS
#define CONVERTERS

#include <iostream>

class Converter
{
public:
  Converter();
  virtual ~Converter() = default;

  virtual void convert();

private:
  std::size_t start;
  std::size_t finish;
  bool convertFinished;
};

class MuteConverter : public Converter
{
public:
  ~MuteConverter() override = default;
  void convert() override;

};

class MixConverter : public Converter
{
public:
  ~MixConverter() override = default;
  void convert() override;

};



#endif
