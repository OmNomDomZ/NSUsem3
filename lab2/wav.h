#ifndef WAV
#define WAV

#include <string>
#include <fstream>
#include <cstdint>
#include <vector>

  const int32_t RIFF = 0x52494646;
  const int32_t WAVE = 0x57415645;
  const int32_t FMT = 0x666d7420;
  const int32_t DATA = 0x64617461;

  const int32_t CHUNK_SIZE_WITHOUT_DATA = 36;
  const int16_t AUDIO_FORMAT = 0x0001;
  const int32_t SUBCHUNK1_SIZE = 16;
  const int16_t NUM_CHANNELS = 1;
  const int32_t SAMPLE_RATE = 44100;
  const int16_t BITS_PER_BYTE = 8;
  const int16_t BITS_PER_SAMPLE = BITS_PER_BYTE * sizeof(int16_t);
  const int32_t BYTE_RATE = SAMPLE_RATE * NUM_CHANNELS * BITS_PER_SAMPLE / BITS_PER_BYTE;
  const int32_t BLOCK_ALIGN = NUM_CHANNELS * BITS_PER_SAMPLE / BITS_PER_BYTE;


  struct WAVHeader
  {
    int32_t chunkID;
    int32_t chunkSize;
    int32_t format;

    int32_t subchunk1ID;
    int32_t subchunk1Size;
    int16_t audioFormat;
    int16_t numChannels;
    int32_t sampleRate;
    int32_t byteRate;
    int16_t blockAlign;
    int16_t bitsPerSample;

    int32_t subchunk2ID;
    int32_t subchunk2Size;
  };

  const WAVHeader FINAL_HEADER{
      RIFF, 0, WAVE,
      FMT, SUBCHUNK1_SIZE, AUDIO_FORMAT, NUM_CHANNELS, SAMPLE_RATE, BYTE_RATE, BLOCK_ALIGN, BITS_PER_SAMPLE,
      DATA, 0
  };



class WAVLoader
{
private:
  WAVHeader InputHeader;
  std::string InputFileName;
  std::ifstream InputFile;
  std::streamoff dataStart;

public:
  WAVLoader() = default;

  ~WAVLoader() = default;

  void WAVOpen(std::string& FileName);

  void GetHeader();

  void GetData(std::vector<int8_t>& Data);
};

class WAVWriter {
private:
  WAVHeader OutputHeader;
  std::string OutputFileName;
  std::ofstream OutputFile;
  std::streamoff dataStart;

public:
  WAVWriter() = default;

  ~WAVWriter() = default;

  void WAVOpen(std::string &FileName);

  void WriteHeader();

  void WriteData(std::vector<int8_t>& Data);
};

#endif
