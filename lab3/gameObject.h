#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H


#include <iostream>
#include <curses.h>
#include <chrono>

using namespace std::chrono_literals;

using steady_clock_t = std::chrono::time_point<std::chrono::steady_clock>;

class gameObject {
public:
  virtual void action() = 0;
//  virtual void draw() = 0;
//  virtual bool isAlive() = 0;

  void out(int y, int x, const std::string& s);

  steady_clock_t now();

};

#endif
