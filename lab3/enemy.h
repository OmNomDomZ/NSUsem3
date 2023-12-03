
#ifndef LAB3_ENEMY_H
#define LAB3_ENEMY_H

#include "gameObject.h"
#include "bullets.h"

class enemy : public gameObject{
private:
  struct Enemy
  {
    int h{};
    int w{};
    steady_clock_t last_time;
  };

  int screenHeight;
  int screenWidth;

  const int enemy_color_pair = 3;

  const int enemySpeed = 1500;

  int numEnemies = 4;

  const int bulletDirection = 1;

  std::vector<Enemy> enemies;

public:

  enemy();

  void move(int& c, std::vector<std::pair<int, int>> position, int bulletPosition) override;

  void action() override;

  std::vector<std::pair<int, int>> getObjects() override;

  int getBulletDirection() override;

  void removeObject(std::pair<int, int> object) override;

  int getInf() override;

  void changeInf() override;

  void removeEnemy(const enemy::Enemy& enemyToRemove) ;

      void DownMove(Enemy &enemy);
};

#endif
