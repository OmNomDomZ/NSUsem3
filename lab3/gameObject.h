#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <chrono>
#include <curses.h>
#include <iostream>
#include <vector>

using namespace std::chrono_literals;

using steady_clock_t = std::chrono::time_point<std::chrono::steady_clock>;

class gameObject {
public:
  gameObject() = default;

  virtual void move(int& c, std::vector<std::pair<int, int>> position, int bulletPosition) = 0;

  virtual void action() = 0;

  virtual std::vector<std::pair<int, int>> getObjects() = 0;

  virtual int getBulletDirection() = 0;

  virtual void removeObject(std::pair<int, int> object) = 0;

  virtual int getInf() = 0;

  virtual void changeInf() = 0;

  void out(int y, int x, const std::string& s);

  steady_clock_t now();

  virtual ~gameObject() = default;

};

#endif
