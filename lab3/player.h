#ifndef LAB3_PLAYER_H
#define LAB3_PLAYER_H

#include "gameObject.h"
#include "bullets.h"

class player : public gameObject {
private:
  int h;
  int w;

  bool isAlive_ = true;

  int screenHeight;
  int screenWidth;

  const int bulletDirection = -1;

  const int player_color_pair = 1;

  int score = 0;

public:
  player();

  void move(int& c, std::vector<std::pair<int, int>> position, int bulletPosition) override;

  void action() override;

  std::vector<std::pair<int, int>> getObjects() override;

  int getBulletDirection() override;

  void removeObject(std::pair<int, int> object) override;

  int getInf() override;

  void changeInf() override;

};


#endif
