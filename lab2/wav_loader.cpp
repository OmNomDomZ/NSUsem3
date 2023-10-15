#include "wav_loader.h"

WAVLoader::WAVLoader(std::string& FileName)
{
  if (FileName.find(".wav") == std::string::npos)
  {
    //
  }
  InputFileName = FileName;
  InputFile.open(InputFileName);
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