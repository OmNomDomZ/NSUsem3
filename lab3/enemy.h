
#ifndef LAB3_ENEMY_H
#define LAB3_ENEMY_H

#include "gameObject.h"
#include "bullets.h"

class enemy : public gameObject{
private:
  int h;
  int w;
  steady_clock_t last_time;

  const int enemy_color_pair = 4;

  bullets enemyBullets;

public:
  void getPosition();

  void move();

  void action() override;

};

#endif
