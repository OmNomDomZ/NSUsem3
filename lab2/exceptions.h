#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <iostream>
#include <exception>
#include <string>

class Exception : public std::invalid_argument
{
protected:
  Exception(const std::string& error);
};

class InvalidFileFormatException : public Exception
{
public:
  InvalidFileFormatException();
};

class FileOpenException : public Exception
{
public:
  FileOpenException();
};

class RIFFException : public Exception
{
public:
  RIFFException()
};

class FormatException : public Exception
{
public:
  FormatException();
};

class FMTException : public Exception
{
public:
  FMTException();
};

class DATAException : public Exception
{
public:
  DATAException();
};

class AudioFormatException : public Exception
{
public:
  AudioFormatException();
};

class NumChannelsException : public Exception
{
public:
  NumChannelsException();
};

class SampleRateException : public Exception
{
public:
  SampleRateException();
};

class ByteRateException : public Exception
{
public:
  ByteRateException();
};

class BlockAlignException : public Exception
{
public:
  BlockAlignException();
};

class BitsPerSampleException : public Exception
{
public:
  BitsPerSampleException();
};


#endif