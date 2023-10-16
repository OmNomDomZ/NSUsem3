#include "wav.h"

WAVLoader::WAVLoader(std::string& FileName)
{
  if (FileName.find(".wav") == std::string::npos)
  {
    //
  }
  InputFileName = FileName;
  InputFile.open(InputFileName, std::ios::binary);
  if (!InputFile.is_open())
  {
    //
  }

  GetHeader();

}

void WAVLoader::GetHeader()
{

  InputFile.read(reinterpret_cast<char *> (&InputHeader), sizeof(WAVHeader));
  if (InputHeader.chunkID != RIFF)
  {
    //
  }

  if (InputHeader.format != WAVE)
  {
    //
  }

  if (InputHeader.subchunk1ID != FMT)
  {
    //
  }

  if (InputHeader.subchunk2ID != DATA)
  {
    //
  }

  if (InputHeader.audioFormat != AUDIO_FORMAT)
  {
    //
  }

  if (InputHeader.numChannels != NUM_CHANNELS)
  {
   //
  }

  if (InputHeader.sampleRate != SAMPLE_RATE)
  {
    //
  }

  if (InputHeader.byteRate != BYTE_RATE)
  {
    //
  }

  if (InputHeader.blockAlign != BLOCK_ALIGN)
  {
    //
  }

  if (InputHeader.bitsPerSample != BITS_PER_SAMPLE)
  {
    //
  }
}

void WAVLoader::GetData()
{
  dataStart = sizeof(InputHeader);

  Data = new int8_t[InputHeader.subchunk2Size];

  InputFile.seekg(dataStart, std::ios::beg);

  for (std::size_t i = 0; i < InputHeader.subchunk2Size; ++i)
  {
    Data[i] = ReadByte();
  }

}

int8_t WAVLoader::ReadByte()
{
  char c;
  InputFile.get(c);
  return (static_cast<int8_t>(c));
}