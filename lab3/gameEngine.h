#ifndef LAB3_GAMEENGINE_H
#define LAB3_GAMEENGINE_H

#include "player.h"
#include "enemy.h"
#include "bullets.h"
#include "gameScreen.h"

class gameEngine{
private:
  gameObject* player_;
  gameObject* enemies_;
  gameObject* playerBullets;
  gameObject* enemiesBullets;

  int enemiesBulletFire = ' ';

  gameScreen gameScreen;

  bool isGameOver = true;

public:
  gameEngine(class gameScreen& gameScreenObj);

  void update(int c);

  void damageEnemy();

  void damagePlayer();

  void gameOver();

  bool gameStatus();

  void printGameOver();
};


#endif