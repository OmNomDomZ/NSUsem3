#ifndef WAV
#define WAV

#include <string>
#include <fstream>
#include <cstdint>
#include <vector>

class WAVLoader
{
private:
  std::string InputFileName;
  std::ifstream InputFile;
  std::streamoff DataStart;
  std::size_t DataSize;

public:
  WAVLoader() = default;

  ~WAVLoader() = default;

  void WAVOpen(std::string& FileName);

  void GetHeader();

  void GetData(std::vector<int16_t>& Data);

  std::size_t GetDuration() const;

};

class WAVWriter {
private:
  std::string OutputFileName;
  std::ofstream OutputFile;
  std::streamoff dataStart;

public:
  WAVWriter() = default;

  ~WAVWriter() = default;

  void WAVOpen(std::string &FileName);

  void WriteHeader(const std::size_t Duration);

  void WriteData(std::vector<int16_t>& Data, const std::size_t Duration);
};

#endif
