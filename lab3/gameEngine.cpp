#include "gameEngine.h"

gameEngine::gameEngine(player& playerObj, enemy& enemyObj)
    : player_(playerObj), enemies_(enemyObj){
}

void gameEngine::update(int c) {

  player_.move(c);

  player_.action();
  enemies_.action();

  playerBullets = player_.getBullets();
  enemyBullets = enemies_.getBullets();

  damageEnemy();
  damagePlayer();

}

void gameEngine::damageEnemy() {
  for (auto& enemy : enemies_.getEnemies())
  {
    for (auto& bullet : playerBullets.getBullets())
    {
      if (enemy.h == bullet.h && enemy.w == bullet.w)
      {
        enemies_.removeEnemy(enemy);
        break;
      }
    }
  }
}

void gameEngine::damagePlayer() {
  for (auto& bullet : enemyBullets.getBullets())
  {
    if (player_.getHeight() == bullet.h && player_.getWidth() == bullet.w )
    {
      gameOver();
    }
  }

}

void gameEngine::gameOver() {
  isGameOver = false;
}

bool gameEngine::gameStatus() {
  return isGameOver;
}