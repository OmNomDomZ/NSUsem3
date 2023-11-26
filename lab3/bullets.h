#ifndef LAB3_BULLETS_H
#define LAB3_BULLETS_H

#include "gameScreen.h"
#include <iostream>
#include <vector>
#include <chrono>
#include <curses.h>
#include <algorithm>

#include "gameObject.h"

using namespace std::chrono_literals;

using steady_clock_t = std::chrono::time_point<std::chrono::steady_clock>;

class bullets : public gameObject{
private:
  struct Bullet {
    int w;
    int h;
    steady_clock_t last_time;
  };

  int bulletDirection;
  std::vector<Bullet> bullets;

  const int bullet_color_pair = 3;

public:
  void get();

  void action() override;

  void removeBullets();

  void addBullet(int w, int h, steady_clock_t time);

  void defineBulletDirection(int h);

};

#endif