
#include "GameObject.h"
#include "iostream"

GameObject::GameObject()
{

}


GameObject::~GameObject()
{

}


bool GameObject::initialiseSprite(sf::Texture& texture, std::string filename)
{
  if(!texture.loadFromFile(filename))
  {
    std::cout << filename << "dont work";
  }

  sprite = new sf::Sprite();
  sprite->setTexture(texture);
  return true;
}



sf::Sprite* GameObject::getSprite()
{
  return sprite;
}