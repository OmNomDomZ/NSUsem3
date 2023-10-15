#ifndef WAV_LOADER
#define WAV_LOADER

#include <string>
#include <fstream>
#include <cstdint>

  const int32_t RIFF = 0x52494646;
  const int32_t WAVE = 0x57415645;
  const int32_t FMT = 0x666d7420;
  const int32_t DATA = 0x64617461;

  const int16_t AUDIO_FORMAT = 0x0001;
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


class WAVLoader
{
private:
  WAVHeader InputHeader;
  std::string InputFileName;
  std::ifstream InputFile;

public:
  WAVLoader() = default;

  WAVLoader(std::string& FileName);

  void GetHeader();

  ~WAVLoader() = default;
};


#endif
