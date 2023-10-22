#include "wav.h"
#include "exceptions.h"

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


struct RIFFandFMT
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
};

struct DATAChunk
{
    int32_t subchunk2ID;
    int32_t subchunk2Size;
};


const RIFFandFMT FINAL_RIFFandFMT{
    RIFF, 0, WAVE,
    FMT, SUBCHUNK1_SIZE, AUDIO_FORMAT, NUM_CHANNELS, SAMPLE_RATE, BYTE_RATE, BLOCK_ALIGN, BITS_PER_SAMPLE
};

const DATAChunk FINAL_DATA{
    DATA, 0
};

void WAVLoader::WAVOpen(std::string& FileName)
{

  InputFileName = FileName;
  if (InputFile.is_open())
  {
    InputFile.close();
  }

  InputFile.open(InputFileName, std::ios::binary);
  if (!InputFile.is_open())
  {
    throw FileOpenException();
  }

  GetHeader();
}


void WAVLoader::GetHeader()
{
  RIFFandFMT InputHeader{};
  InputFile.read(reinterpret_cast<char *> (&InputHeader), sizeof(InputHeader));
  DataStart = sizeof(InputHeader);

  if (InputHeader.chunkID != RIFF)
  {
    throw RIFFException();
  }

  if (InputHeader.format != WAVE)
  {
    throw FormatException();
  }

  if (InputHeader.subchunk1ID != FMT)
  {
    throw FMTException();
  }

  if (InputHeader.audioFormat != AUDIO_FORMAT)
  {
    throw AudioFormatException();
  }

  if (InputHeader.numChannels != NUM_CHANNELS)
  {
    throw NumChannelsException();
  }

  if (InputHeader.sampleRate != SAMPLE_RATE)
  {
    throw SampleRateException();
  }
}

void WAVLoader::GetData(std::vector<int16_t>& Data)
{
  DATAChunk DataChunk{};
  InputFile.read(reinterpret_cast<char *>(&DataChunk), sizeof(DataChunk));

  if (DataChunk.subchunk2ID != DATA)
  {
    throw DATAException();
  }

  DataStart += sizeof(DataChunk);

  InputFile.seekg(DataStart, std::ios::beg);
  InputFile.read(reinterpret_cast<char*>(Data.data()), DataChunk.subchunk2Size);
  if(InputFile.fail())
  {
    throw FileFailure();
  }

  DataSize = DataChunk.subchunk2Size;

}

std::size_t WAVLoader::GetDuration() const
{
  return DataSize / BYTE_RATE;
}

void WAVWriter::WAVOpen(std::string& FileName) {

  OutputFileName = FileName;
  if (OutputFile.is_open())
  {
    OutputFile.close();
  }

  OutputFile.open(OutputFileName, std::ios::binary);
  if (!OutputFile.is_open())
  {
    throw FileOpenException();
  }

}

void WAVWriter::WriteHeader(const std::size_t Duration)
{
  RIFFandFMT finalRIFFandFMT{FINAL_RIFFandFMT};
  DATAChunk finalDataChunk{FINAL_DATA};

  finalDataChunk.subchunk2Size = Duration * sizeof(int16_t) * SAMPLE_RATE;
  finalRIFFandFMT.chunkSize = CHUNK_SIZE_WITHOUT_DATA + finalDataChunk.subchunk2Size;

  OutputFile.seekp(std::ios::beg);
  OutputFile.write(reinterpret_cast<char *> (&finalRIFFandFMT), sizeof(finalRIFFandFMT));
  OutputFile.write(reinterpret_cast<char *> (&finalDataChunk), sizeof(finalDataChunk));

  dataStart = sizeof(finalRIFFandFMT) + sizeof(finalDataChunk);

  OutputFile.flush();
  if (OutputFile.fail())
  {
    throw FileFailure();
  }
}

void WAVWriter::WriteData(std::vector<int16_t>& Data, const std::size_t second)
{
  OutputFile.seekp(dataStart + second * Data.size() * sizeof(*Data.data()), std::ios::beg);
  OutputFile.write(reinterpret_cast<char*> (Data.data()), Data.size() * sizeof(*Data.data()));

  if (OutputFile.fail())
  {
    throw FileFailure();
  }
}

