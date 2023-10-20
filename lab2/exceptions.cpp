#include "exceptions.h"

Exception::Exception(const std::string& error)
  : std::invalid_argument("Error: " + error){}

InvalidFileFormatException::InvalidFileFormatException()
  : Exception("Invalid file format") {}

FileOpenException::FileOpenException()
    : Exception("Couldn't open the file") {}

RIFFException::RIFFException()
    : Exception("Invalid RIFF") {}

FormatException::FormatException()
    : Exception("Invalid format") {}