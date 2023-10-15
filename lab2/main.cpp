#include <fstream>
#include <iostream>

int main()
{
 std::ifstream inputFile;
 std::ofstream outputFile;

 inputFile.open("input.wav");
 outputFile.open("output.wav");



  return 0;
}
