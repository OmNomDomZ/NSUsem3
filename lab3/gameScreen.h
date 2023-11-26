#ifndef LAB3_GAMESCREEN_H
#define LAB3_GAMESCREEN_H

#include <curses.h>
#include <iostream>
#include <chrono>


class gameScreen{
private:
  int h1;
  int w1;

  const char* title_format_str = "The terminal game template. Bullets: %lu";

  const int main_color_pair = 1;

public:
  void makeScreen();

  void getConsoleDimensions();

  void printTitle();

  void displayTheBorder();
};



#endif