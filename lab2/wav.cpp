#include "wav.h"

void WAVLoader::WAVOpen(std::string& FileName)
{
  if (FileName.find(".wav") == std::string::npos)
  {

  }
  InputFileName = FileName;
  if (InputFile.is_open())
  {
    InputFile.close();
  }

  InputFile.open(InputFileName, std::ios::binary);
  if (!InputFile.is_open())
  {

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

void WAVLoader::GetData(std::vector<int8_t>& Data)
{
  dataStart = sizeof(InputHeader);
  InputFile.seekg(dataStart, std::ios::beg);
  InputFile.read(reinterpret_cast<char*>(Data.data()), InputHeader.subchunk2Size);
  if(InputFile.fail())
  {

  }

}

void WAVWriter::WAVOpen(std::string& FileName) {
  if (FileName.find(".wav") == std::string::npos)
  {

  }
  OutputFileName = FileName;
  if (OutputFile.is_open())
  {
    OutputFile.close();
  }

  OutputFile.open(OutputFileName, std::ios::binary);
  if (!OutputFile.is_open())
  {

  }

}

void WAVWriter::WriteHeader() {
  WAVHeader finalHeader{FINAL_HEADER};
  finalHeader.subchunk2Size = ;
  finalHeader.chunkSize = CHUNK_SIZE_WITHOUT_DATA + finalHeader.subchunk2Size;

  OutputFile.seekp(std::ios::beg);
  OutputFile.write(reinterpret_cast<char *> (&finalHeader), sizeof(finalHeader));
  dataStart = sizeof(finalHeader);
  OutputFile.flush();
}

void WAVWriter::WriteData(std::vector<int8_t>& Data)
{
  OutputFile.seekp(dataStart);
  OutputFile.write(reinterpret_cast<char*> (Data.data()), );
  OutputFile.flush();
  if (OutputFile.fail())
  {

  }

}

