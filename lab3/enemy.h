
#ifndef LAB3_ENEMY_H
#define LAB3_ENEMY_H

#include "gameObject.h"
#include "bullets.h"

class enemy : public gameObject{
private:
  struct Enemy
  {
    int h;
    int w;
    steady_clock_t last_time;
  };

  int screenHeight;
  int screenWidth;

  const int enemy_color_pair = 3;

  int const enemy_bullet_color = 4;

  bullets enemyBullets;

  int const enemyBulletsSpeed = 700;

  int const enemySpeed = 400;

  int const numEnemies = 5;

  std::vector<Enemy> enemies;


public:
  enemy();

  void getPosition();

  void move(Enemy& enemy);

  void action() override;

  void DownMove(Enemy& enemy);

  void removeEnemy();

};

#endif
