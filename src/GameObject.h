
#ifndef BREAKOUT_GAMEOBJECT_H
#define BREAKOUT_GAMEOBJECT_H

#include <string>
#include <SFML/Graphics.hpp>
#include "Vector2.h"

class GameObject
{
 public:
  GameObject();
  ~GameObject();

  bool initialiseSprite(sf::Texture &texture, std::string filename);
  sf::Sprite* getSprite();

  sf::Sprite paddle;
  sf::Sprite ball;

  sf::Texture ball_texture;
  sf::Texture paddle_texture;
  sf::Texture blocks_texture;
  sf::Texture gem_texture;

  bool visibility = true;

  float speed = 200.f;

  Vector2 direction = {0,0};

 private:
  sf::Sprite* sprite = nullptr;
};

#endif // BREAKOUT_GAMEOBJECT_H
