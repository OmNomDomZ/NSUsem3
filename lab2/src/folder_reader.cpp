#include "../include/folder_reader.h"

#include <filesystem>

folder_reader::folder_reader(const std::string &folderPath)
    : folderPath_(folderPath){}

std::vector<std::string> folder_reader::getFileNames()
{
  std::vector<std::string> fileNames;
  for (const auto& entry : std::filesystem::directory_iterator(folderPath_)) {
    if (std::filesystem::is_regular_file(entry.path())) {
      fileNames.push_back(entry.path().string());
    }
  }
  return fileNames;
}