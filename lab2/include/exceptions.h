#pragma once

#include <iostream>
#include <exception>
#include <string>

class Exception : public std::invalid_argument
{
protected:
  explicit Exception(const std::string& error);
};

class FileOpenException : public Exception
{
public:
  FileOpenException();
};

class RIFFException : public Exception
{
public:
  RIFFException();
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

class FileFailure : public Exception
{
public:
  FileFailure();
};

class InvalidCommand : public Exception
{
public:
  InvalidCommand();
};

class InvalidNum : public Exception
{
public:
  InvalidNum();
};

class InvalidArgumentPassed : public Exception
{
public:
  InvalidArgumentPassed();
};
