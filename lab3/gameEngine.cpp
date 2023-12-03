#include "gameEngine.h"
#include "gameObject.h"
#include <random>

gameEngine::gameEngine(class gameScreen& gameScreenObj)
    : gameScreen(gameScreenObj)
{
  player_ = new player();
  enemies_ = new enemy();
  playerBullets = new bullets();
  enemiesBullets = new bullets();
}

void gameEngine::update(int c) {
  gameScreen.displayTheBorder();
  gameScreen.printTitle(player_->getInf(), enemies_->getInf());

  player_->move(c, {}, 0);
  std::vector<std::pair<int, int>> playerPosition = player_->getObjects();
  playerBullets->move(c, playerPosition, player_->getBulletDirection());

  enemies_->action();

  for(auto& enemy : enemies_->getObjects())
  {
    std::vector<std::pair<int, int>> enemyPosition;
    enemyPosition.emplace_back(enemy.first, enemy.second);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(1, 15);
    int randomNum = distr(gen);
    if (randomNum == 1)
    {
      enemiesBullets->move(enemiesBulletFire, enemyPosition, enemies_->getBulletDirection());
    }
  }

  player_->action();
  playerBullets->action();
  enemiesBullets->action();

  damageEnemy();
  damagePlayer();

  if (enemies_->getInf() == 0)
  {
    gameScreen.printWinTitle(player_->getInf());
  }

}

void gameEngine::damageEnemy() {
  for (auto& enemy : enemies_->getObjects())
  {
    for (auto& bullet : playerBullets->getObjects())
    {
      if (enemy.first == bullet.first && enemy.second == bullet.second)
      {
        enemies_->removeObject(enemy);
        enemies_->changeInf();
        player_->changeInf();
        break;
      }
    }
  }
}

void gameEngine::damagePlayer() {
  for (auto& bullet : enemiesBullets->getObjects())
  {
    for (auto& player : player_->getObjects())
    if (player.first == bullet.first && player.second == bullet.second )
    {
      gameOver();
    }
  }
}

void gameEngine::gameOver() {
  gameScreen.gameOver();
  isGameOver = false;
}

bool gameEngine::gameStatus() {
  return isGameOver;
}

void gameEngine::printGameOver() {
  gameScreen.gameOver();
}