#ifndef LAB3_GAMEENGINE_H
#define LAB3_GAMEENGINE_H

#include "player.h"
#include "enemy.h"
#include "bullets.h"

class gameEngine{
private:
  player player_;
  enemy enemies_;
  bullets playerBullets;
  bullets enemyBullets;

  bool isGameOver = true;

public:
  gameEngine(player& playerObjRef, enemy& enemyObjRef);

  void update(int c);

  void damageEnemy();

  void damagePlayer();

  void gameOver();

  bool gameStatus();
};


#endif