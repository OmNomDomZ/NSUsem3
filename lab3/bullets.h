#ifndef LAB3_BULLETS_H
#define LAB3_BULLETS_H

#include <vector>
#include <algorithm>
#include "gameObject.h"

using namespace std::chrono_literals;

using steady_clock_t = std::chrono::time_point<std::chrono::steady_clock>;

class bullets : public gameObject{
private:
  struct Bullet {
    int h;
    int w;
    steady_clock_t last_time;
  };

  std::vector<Bullet> bullets;

  const int bulletSpeed = 500;
  const int bullet_color_pair = 2;

  int bulletDirection = 0;

  int screenHeight = 0;
  int screenWidth = 0;


public:

  void move(int& c, std::vector<std::pair<int, int>> position, int bulletPosition) override;

  void action() override;

  std::vector<std::pair<int, int>> getObjects() override;

  int getBulletDirection() override;

  void removeObject(std::pair<int, int> object) override;

  int getInf() override;

  void changeInf() override;

  void removeBullets();

  void addBullet(int w, int h, steady_clock_t time);

  void defineBulletDirection(int bulletDirection);

};

#endif