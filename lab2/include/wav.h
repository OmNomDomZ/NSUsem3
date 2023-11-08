#ifndef WAV
#define WAV

#include <string>
#include <fstream>
#include <cstdint>
#include <vector>

class WAVLoader {
private:
  std::string InputFileName;
  std::ifstream InputFile;
  std::streamoff DataStart;
  std::size_t DataSize_;

public:
  WAVLoader() = default;

  ~WAVLoader() = default;

  void WAVOpen(const std::string &FileName);

  void GetHeader();

  void GetData(std::vector<int16_t> &Data, const std::size_t Duration);

  std::size_t GetDuration() const;

  void FindData();

  void FindRIFF();
};

class WAVWriter {
private:
  std::string OutputFileName;
  std::ofstream OutputFile;
  std::streamoff dataStart;

public:
  WAVWriter() = default;

  ~WAVWriter() = default;

  void WAVOpen(const std::string &FileName);

  void WriteHeader(const std::size_t Duration);

  void WriteData(std::vector<int16_t> &Data, const std::size_t second);
};

#endif
