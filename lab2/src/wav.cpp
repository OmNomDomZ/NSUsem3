#include "../include/wav.h"
#include "../include/exceptions.h"

const int32_t RIFF = 0x46464952;
const int32_t WAVE = 0x45564157;
const int32_t FMT = 0x20746d66;
const int32_t DATA = 0x61746164;

const int32_t CHUNK_SIZE_WITHOUT_DATA = 36;
const int16_t AUDIO_FORMAT = 0x0001;
const int32_t SUBCHUNK1_SIZE = 16;
const int16_t NUM_CHANNELS = 1;
const int32_t SAMPLE_RATE = 44100;
const int16_t BITS_PER_BYTE = 8;
const int16_t BITS_PER_SAMPLE = BITS_PER_BYTE * sizeof(int16_t);
const int32_t BYTE_RATE = SAMPLE_RATE * NUM_CHANNELS * BITS_PER_SAMPLE / BITS_PER_BYTE;
const int32_t BLOCK_ALIGN = NUM_CHANNELS * BITS_PER_SAMPLE / BITS_PER_BYTE;


struct __attribute__((packed)) RIFF_t
{
  int32_t chunkID;
  int32_t chunkSize;
  int32_t format;
};

struct __attribute__((packed)) FMT_t
{
  int32_t subchunk1ID;
  int32_t subchunk1Size;
  int16_t audioFormat;
  int16_t numChannels;
  int32_t sampleRate;
  int32_t byteRate;
  int16_t blockAlign;
  int16_t bitsPerSample;
};

struct __attribute__((packed)) DATAChunk_t
{
    int32_t subchunk2ID;
    int32_t subchunk2Size;
};


const RIFF_t FINAL_RIFF
    {
    RIFF, 0, WAVE
    };

const FMT_t FINAL_FMT
    {
        FMT, SUBCHUNK1_SIZE, AUDIO_FORMAT, NUM_CHANNELS, SAMPLE_RATE, BYTE_RATE, BLOCK_ALIGN, BITS_PER_SAMPLE
    };


const DATAChunk_t FINAL_DATA{
    DATA, 0
};

void WAVLoader::WAVOpen(const std::string& FileName)
{

  InputFileName = FileName;
  DataStart = 0;
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
  FindData();

}


void WAVLoader::GetHeader()
{
  RIFF_t InputRIFF{};
  FMT_t InputFMT{};
  InputFile.read(reinterpret_cast<char *> (&InputRIFF), sizeof(InputRIFF));
  InputFile.read(reinterpret_cast<char *> (&InputFMT), sizeof(InputFMT));

  DataStart += sizeof(InputRIFF);
  DataStart += sizeof(InputFMT);

  if (InputRIFF.chunkID != RIFF)
  {
    throw RIFFException();
  }

  if (InputRIFF.format != WAVE)
  {
    throw FormatException();
  }

  if (InputFMT.subchunk1ID != FMT)
  {
    throw FMTException();
  }

  if (InputFMT.audioFormat != AUDIO_FORMAT)
  {
    throw AudioFormatException();
  }

  if (InputFMT.numChannels != NUM_CHANNELS)
  {
    throw NumChannelsException();
  }

  if (InputFMT.sampleRate != SAMPLE_RATE)
  {
    throw SampleRateException();
  }
}

void WAVLoader::FindData(){
  DATAChunk_t DataChunk{};
  while (!InputFile.eof())
  {
    InputFile.read(reinterpret_cast<char *>(&DataChunk), sizeof(DataChunk));
    if (InputFile.fail())
    {
      throw FileFailure();
    }
    DataStart += sizeof(DataChunk);
    if (DataChunk.subchunk2ID == DATA)
    {
      DataSize_ = DataChunk.subchunk2Size;
      return;
    }

    InputFile.seekg(DataChunk.subchunk2Size, std::fstream::cur);
    if (InputFile.fail())
    {
      throw FileFailure();
    }
    DataStart += DataChunk.subchunk2Size;
  }
}

void WAVLoader::GetData(std::vector<int16_t>& Data, const std::size_t second)
{
  InputFile.seekg(DataStart + second * Data.size() * sizeof(*Data.data()), std::ios::beg);
  InputFile.read(reinterpret_cast<char*>(Data.data()), SAMPLE_RATE * sizeof(*Data.data()));
  if(InputFile.fail())
  {
    throw FileFailure();
  }
}

std::size_t WAVLoader::GetDuration() const
{
  return DataSize_ / BYTE_RATE;
}

void WAVWriter::WAVOpen(const std::string& FileName) {

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
  RIFF_t finalRIFF{FINAL_RIFF};
  FMT_t finalFMT{FINAL_FMT};
  DATAChunk_t finalDataChunk{FINAL_DATA};

  finalDataChunk.subchunk2Size = Duration * sizeof(int16_t) * SAMPLE_RATE;
  finalRIFF.chunkSize = CHUNK_SIZE_WITHOUT_DATA + finalDataChunk.subchunk2Size;

  OutputFile.seekp(std::ios::beg);
  OutputFile.write(reinterpret_cast<char *> (&finalRIFF), sizeof(finalRIFF));
  OutputFile.write(reinterpret_cast<char *> (&finalFMT), sizeof (finalFMT));
  OutputFile.write(reinterpret_cast<char *> (&finalDataChunk), sizeof(finalDataChunk));

  dataStart = sizeof(finalRIFF) + sizeof(finalFMT) + sizeof(finalDataChunk);

  OutputFile.flush();
  if (OutputFile.fail())
  {
    throw FileFailure();
  }
}

void WAVWriter::WriteData(std::vector<int16_t>& Data, const std::size_t second)
{
  OutputFile.seekp(dataStart + second * Data.size() * sizeof(*Data.data()), std::ios::beg);
  OutputFile.write(reinterpret_cast<char*> (Data.data()), SAMPLE_RATE * sizeof(*Data.data()));

  if (OutputFile.fail())
  {
    throw FileFailure();
  }
}

