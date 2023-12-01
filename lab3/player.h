#ifndef LAB3_PLAYER_H
#define LAB3_PLAYER_H

#include "gameObject.h"
#include "bullets.h"

class player : public gameObject {
private:
  int h;
  int w;

  bool ok;

  int screenHeight;
  int screenWidth;

  const int player_color_pair = 1;
  const int player_bullet_color_pair = 2;

  bullets playerBullets;

  const int playerBulletSpeed = 400;

public:
  player();

  void move(int c);

  void action() override;

  bullets& getBullets();

  int getHeight();

  int getWidth();

  bool isAlive();

  void dead();

};


#endif
