#ifndef FOLDERREADER_H
#define FOLDERREADER_H

#include "string"
#include "vector"

class folder_reader {
public:

  explicit folder_reader(const std::string& folderPath);

  std::vector<std::string> getFileNames();

private:
  std::string folderPath_;
};

#endif