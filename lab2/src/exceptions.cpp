#include "../include/exceptions.h"

Exception::Exception(const std::string& error)
  : std::invalid_argument("Error: " + error){}

FileOpenException::FileOpenException()
    : Exception("Couldn't open the file") {}

RIFFException::RIFFException()
    : Exception("Invalid RIFF") {}

FormatException::FormatException()
    : Exception("Invalid format") {}

FMTException::FMTException()
    : Exception("Invalid data format") {}

DATAException::DATAException()
    : Exception("Invalid data subchunk ID"){}

AudioFormatException::AudioFormatException()
    : Exception("Invalid audio format"){}

NumChannelsException::NumChannelsException()
    : Exception("Invalid number of channels"){}

SampleRateException::SampleRateException()
    : Exception("Invalid sample rate"){}

FileFailure::FileFailure()
    : Exception("File failure"){}