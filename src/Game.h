
#ifndef BREAKOUT_GAME_H
#define BREAKOUT_GAME_H

#include <SFML/Graphics.hpp>
#include "Vector2.h"
#include "GameObject.h"

class Game
{
 public:
  Game(sf::RenderWindow& window);
  ~Game();
  bool init();
  void update(float dt);
  void render();
  void mouseClicked(sf::Event event);
  void keyPressed(sf::Event event);
  void keyReleased(sf::Event event);
  void ballmovement(float dt);
  void gemmovement(float dt);

 private:

  sf::RenderWindow& window;

  sf::Text play_text;
  sf::Text quit_text;
  sf::Text key_quit;
  sf::Text lose_text;
  sf::Text win_text;
  sf::Text menu_text;
  sf::Text life_score_text;
  sf::Text pl_score_text;

  sf::Font font;


  bool in_menu = true;
  bool in_lose = false;
  bool in_win = false;
  bool play_selected = true;
  bool menu_selected = false;
  bool quit_selected = true;


  int block_num = sizeof(blocks)/4;
  int life_score = 3;
  int pl_score = 0;

  GameObject* paddle;
  GameObject* ball;
  GameObject* blocks[18][4];
  GameObject* gems[4];




};

#endif // BREAKOUT_GAME_H
