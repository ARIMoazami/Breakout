
#include "GameObject.h"
#include "Game.h"
#include <iostream>

Game::Game(sf::RenderWindow& game_window)
  : window(game_window)
{
  srand(time(NULL));
}

Game::~Game()
{

}

bool Game::init()
{
  font.loadFromFile("Data/Fonts/OpenSans-Bold.ttf");

  play_text.setString("ENTER BREAKOUT");
  play_text.setFont(font);
  play_text.setCharacterSize(50);
  play_text.setFillColor(sf::Color(255,255,255));
  play_text.setPosition(
    window.getSize().x/2.1 - play_text.getGlobalBounds().width/2,
    window.getSize().y/7 - play_text.getGlobalBounds().height/2);

  quit_text.setString("QUIT GAME");
  quit_text.setFont(font);
  quit_text.setCharacterSize(50);
  quit_text.setFillColor(sf::Color(255,255,255));
  quit_text.setPosition(
    window.getSize().x/2.1 - quit_text.getGlobalBounds().width/2,
    window.getSize().y/3 - quit_text.getGlobalBounds().height/2);

  key_quit.setString("Esc key to quit\nat anytime");
  key_quit.setFont(font);
  key_quit.setCharacterSize(35);
  key_quit.setFillColor(sf::Color(255,255,255));
  key_quit.setPosition(
    window.getSize().x/2 - key_quit.getGlobalBounds().width/2,
    window.getSize().y/1.2 - key_quit.getGlobalBounds().height/2);

  //display player life score
  life_score_text.setString("lives: " + std::to_string(life_score));
  life_score_text.setFont(font);
  life_score_text.setCharacterSize(50);
  life_score_text.setFillColor(sf::Color(255,255,255));
  life_score_text.setPosition(
  window.getSize().x/1.4 - life_score_text.getGlobalBounds().width/2,
  window.getSize().y/3 - life_score_text.getGlobalBounds().height/2);

  //display player brick score
  pl_score_text.setString("score: " + std::to_string(pl_score));
  pl_score_text.setFont(font);
  pl_score_text.setCharacterSize(50);
  pl_score_text.setFillColor(sf::Color(255,255,255));
  pl_score_text.setPosition(
    window.getSize().x/3 - pl_score_text.getGlobalBounds().width/2,
    window.getSize().y/3 - pl_score_text.getGlobalBounds().height/2);

  //display lose message
  lose_text.setString("GAME OVER");
  lose_text.setFont(font);
  lose_text.setCharacterSize(50);
  lose_text.setFillColor(sf::Color(255,255,255));
  lose_text.setPosition(
    window.getSize().x/2.1 - lose_text.getGlobalBounds().width/2,
    window.getSize().y/2 - lose_text.getGlobalBounds().height/2);


  //display game over menu text
  menu_text.setString("*TAB* KEY TO RETURN TO MENU");
  menu_text.setFont(font);
  menu_text.setCharacterSize(40);
  menu_text.setFillColor(sf::Color(255,255,255));
  menu_text.setPosition(
    window.getSize().x/2.1 - menu_text.getGlobalBounds().width/2,
    window.getSize().y/7 - menu_text.getGlobalBounds().height/2);

  //win message
  win_text.setString("YOU WIN!");
  win_text.setFont(font);
  win_text.setCharacterSize(50);
  win_text.setFillColor(sf::Color(255,255,255));
  win_text.setPosition(
    window.getSize().x/2.1 - win_text.getGlobalBounds().width/2,
    window.getSize().y/2 - win_text.getGlobalBounds().height/2);


  //paddle gameobject creation
  paddle = new GameObject();
  paddle->initialiseSprite(paddle->paddle_texture,"Data/Images/paddleRed.png");
  paddle->getSprite()->setPosition(450,650);


  //ball object creation
  ball = new GameObject();
  ball->initialiseSprite(ball->ball_texture,"Data/Images/ballBlue.png");
  ball->direction.x = 200;
  ball->direction.y = 200;
  ball->getSprite()->setPosition(500,600);

  //gem object creation
  for (int g = 0; g < 4; g++)
  {
    gems[g] = new GameObject();
    gems[g]->initialiseSprite(
    gems[g]->gem_texture, "Data/Images/element_red_diamond.png");
    gems[g]->getSprite()->setPosition(90, 85*g - 270);
    gems[g]->direction.y = 150;
    gems[g]->visibility = false;
  }


  //blocks
  for (int x = 0; x < 18; x++)
  {
    for (int y = 0; y < 4; y++)
    {
      blocks[x][y] = new GameObject();

      switch (y)
      {
        case 0:
          blocks[x][y]->initialiseSprite(blocks[x][y]->blocks_texture,"Data/Images/element_green_rectangle.png");
          break;
        case 1:
          blocks[x][y]->initialiseSprite(blocks[x][y]->blocks_texture,"Data/Images/element_yellow_rectangle.png");
          break;
        case 2:
          blocks[x][y]->initialiseSprite(blocks[x][y]->blocks_texture,"Data/Images/element_purple_rectangle.png");
          break;
        case 3:
          blocks[x][y]->initialiseSprite(blocks[x][y]->blocks_texture,"Data/Images/element_blue_rectangle.png");
          break;
        default:
          break;
      }
      blocks[x][y]->getSprite()->setPosition(x*60,50*y);
    }
  }

  return true;
}

void Game::update(float dt)
{
  paddle->getSprite()->move(paddle->direction.x * dt, paddle->direction.y * dt);

//ball collision with paddle
  if (ball->getSprite()->getGlobalBounds().intersects(
    paddle->getSprite()->getGlobalBounds()))
  {

    //checking total over lap amount of blocks and ball on x axis
    //all this code is used again to stop the ball glitching into the paddle
    float x_overlap_total = std::max((float)0.0, std::min(ball->getSprite()->getPosition().x + paddle->getSprite()->getGlobalBounds().width,
    ball->getSprite()->getPosition().x + paddle->getSprite()->getGlobalBounds().width) -
    std::max(ball->getSprite()->getPosition().x, paddle->getSprite()->getPosition().x));

    //checking total over lap amount of blocks and ball on y axis
    float y_overlap_total = std::max((float)0.0, std::min(ball->getSprite()->getPosition().y + ball->getSprite()->getGlobalBounds().height,
    ball->getSprite()->getPosition().y + paddle ->getSprite()->getGlobalBounds().height) -
    std::max(ball->getSprite()->getPosition().y, paddle->getSprite()->getPosition().y));

    float x_direction = 1;

    float y_direction = 1;

    if (ball->getSprite()->getPosition().x < paddle->getSprite()->getPosition().x)
    {
      x_direction = -1;
    }

    if (ball->getSprite()->getPosition().y < paddle->getSprite()->getPosition().y)
    {
      y_direction = -1;
    }
    //making sure that the ball doesnt get stuck inside the block and reverses ball movement on y axis
    if (y_overlap_total < x_overlap_total)
    {
      ball->getSprite()->move(0, y_overlap_total * y_direction);
      ball->direction.y *= -1;
    }
    else
    {
      // making sure that the ball doesnt get stuck inside the block and reverses ball movement on x axis
      if (x_overlap_total < y_overlap_total)
      {
        ball->getSprite()->move(x_overlap_total * x_direction, 0);
        ball->direction.x *= -1;
      }
      // making sure that the ball doesnt get stuck inside the block and reverses ball movement on both axis
      else
      {
        ball->getSprite()->move(0, y_overlap_total * y_direction);
        ball->getSprite()->move(x_overlap_total * x_direction, 0);
        ball->direction.y *= -1;
        ball->direction.x *= -1;
      }
    }
  }


//gem collision
  for (int g = 0; g < 4; g++)
  {
    if (paddle->getSprite()->getGlobalBounds().intersects(
      gems[g]->getSprite()->getGlobalBounds()) && gems[g]->visibility)
    {
      gems[g]->visibility = false;
      pl_score += 5;
      pl_score_text.setString("score: " + std::to_string(pl_score));
    }
  }


  //ball collision with the bricks
  for (int x = 0; x < 18; x++)
  {
    for (int y = 0; y < 4; y++)
    {
      if (ball->getSprite()->getGlobalBounds().intersects(blocks[x][y]->getSprite()->getGlobalBounds())
          && blocks[x][y]->visibility)
      {
        //checking total over lap amount of blocks and ball on collision on x axis
        float x_overlap_total = std::max((float)0.0, std::min(blocks[x][y]->getSprite()->getPosition().x + blocks[x][y]->getSprite()->getGlobalBounds().width,
        ball->getSprite()->getPosition().x + ball->getSprite()->getGlobalBounds().width) -
        std::max(blocks[x][y]->getSprite()->getPosition().x, ball->getSprite()->getPosition().x));

        //checking total over lap amount of blocks and ball on collision on y axis
        float y_overlap_total = std::max((float)0.0, std::min(blocks[x][y]->getSprite()->getPosition().y + blocks[x][y]->getSprite()->getGlobalBounds().height,
        ball->getSprite()->getPosition().y + ball->getSprite()->getGlobalBounds().height) -
        std::max(blocks[x][y]->getSprite()->getPosition().y, ball->getSprite()->getPosition().y));

        float x_direction = 1;

        float y_direction = 1;

        if (ball->getSprite()->getPosition().x < blocks[x][y]->getSprite()->getPosition().x)
        {
          x_direction = -1;
        }

        if (ball->getSprite()->getPosition().y < blocks[x][y]->getSprite()->getPosition().y)
        {
          y_direction = -1;
        }

        //making sure that the ball doesnt get stuck inside the block and reverses ball movement on y axis
        if (y_overlap_total < x_overlap_total)
        {
          ball->getSprite()->move(0, y_overlap_total * y_direction);
          ball->direction.y *= -1;
        }
        else
        {
          //making sure that the ball doesnt get stuck inside the block and reverses ball movement on x axis
          if (x_overlap_total < y_overlap_total)
          {
            ball->getSprite()->move(x_overlap_total * x_direction, 0);
            ball->direction.x *= -1;
          }
          //making sure that the ball doesnt get stuck inside the block and reverses ball movement on both axis
          else
          {
            ball->getSprite()->move(0, y_overlap_total * y_direction);
            ball->getSprite()->move(x_overlap_total * x_direction, 0);
            ball->direction.y *= -1;
            ball->direction.x *= -1;
          }
        }
        
        blocks[x][y]->visibility = false;
        pl_score += 1;
        pl_score_text.setString("score: " + std::to_string(pl_score));
        block_num -= 1;
      }
    }
  }


  //ball collision with the walls
  if ((ball->getSprite()->getPosition().x >=
     (window.getSize().x - ball->getSprite()->getGlobalBounds().width)) ||
    (ball->getSprite()->getPosition().x <= 0))
  {
    ball->direction.x *= -1;
  }
  else
  {
    if (ball->getSprite()->getPosition().y < 0)
    {
      ball->direction.y *= -1;
      ball->getSprite()->move(0,1);
    }
  }


  //ball collide with bottom of window
  if ((ball->getSprite()->getPosition().y > window.getSize().y))
  {
    life_score -= 1;
    life_score_text.setString("lives: " + std::to_string(life_score));
    ball->getSprite()->setPosition(500,600);
    ball->direction.y = -150;
  }


  //paddle collisions with the window sizes
  if (paddle->getSprite()->getPosition().x >=
      window.getSize().x - paddle->getSprite()->getGlobalBounds().width)
  {
    paddle->getSprite()->setPosition(window.getSize().x -
    paddle->getSprite()->getGlobalBounds().width,
    paddle->getSprite()->getPosition().y);
  }

  if (paddle->getSprite()->getPosition().x <= 0)
  {
    paddle->getSprite()->setPosition(0, paddle->getSprite()->getPosition().y);
  }

  //losing the game
  if (life_score == 0)
  {
    in_lose = true;
  }

  //win the game
  if (block_num == 0)
  {
    in_win = true;
  }


}

void Game::render()
{
  if(in_menu)
  {
    window.draw(play_text);
    window.draw(quit_text);
    window.draw(key_quit);
    in_lose = false;
    in_win = false;
  }
  else if(in_lose)
  {
    window.draw(lose_text);
    window.draw(menu_text);
  }
  else if (in_win)
  {
    window.draw(win_text);
    window.draw(menu_text);
  }
  else
  {
    quit_selected = false;
    window.draw(life_score_text);
    window.draw(pl_score_text);
    window.draw(*paddle->getSprite());
    window.draw(*ball->getSprite());
    for (int g = 0; g < 4; g++)
    {
      if (gems[g]->visibility)
      {
        window.draw(*gems[g]->getSprite());
      }
    }
    for (int x = 0; x < 18; x++)
    {
      for (int y = 0; y < 4; y++)
      {
        if (blocks[x][y]->visibility)
        {
          window.draw(*blocks[x][y]->getSprite());
        }
      }
    }
  }

}

void Game::mouseClicked(sf::Event event)
{
  //get the click position
  sf::Vector2i click = sf::Mouse::getPosition(window);


}

void Game::keyPressed(sf::Event event)
{
  //mapping the keys for the controls on the menu
  if ((event.key.code == sf::Keyboard::W) ||
  (event.key.code == sf::Keyboard::S))

    //menu text will change depending on if certain options are selected
  {
    if (in_menu)
    {
      play_selected = !play_selected;
      quit_selected = !quit_selected;
      if (play_selected)
      {
        play_text.setString("> ENTER BREAKOUT");
        quit_text.setString("QUIT GAME");
      }
      else
      {
        play_text.setString("ENTER BREAKOUT");
        quit_text.setString("> QUIT GAME");
      }
    }
  }
  //enter is selected on either option it will take the player to those menus
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
  {
    if (in_menu)
    {
      if (play_selected)
      {
        in_menu = false;
        for (int x = 0; x < 18; x++)
        {
          for (int y = 0; y < 4; y++)
          {
            blocks[x][y]->visibility = true;
          }
        }
        paddle->getSprite()->setPosition(450,650);
        ball->getSprite()->setPosition(500,600);
        pl_score = 0;
        pl_score_text.setString("score: " + std::to_string(pl_score));
        life_score = 3;
        life_score_text.setString("lives: " + std::to_string(life_score));
        block_num = 72;
      }
      else
      {
        window.close();
      }
    }

    if (in_lose)
    {
      if (menu_selected)
      {
        in_menu = true;
      }
    }
  }

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
  {
    window.close();
  }


  //Tab key to return to main menu
  if (in_lose)
  {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab))
    {
      in_menu = true;
      in_lose = false;
      ball->getSprite()->setPosition(500,600);
    }
  }

  if (in_win)
  {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab))
    {
      in_menu = true;
      in_win = false;
      ball->getSprite()->setPosition(500,600);
    }
  }



  //paddle movement
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
  {
    paddle->direction.x = -300.f;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
  {
    paddle->direction.x = 300.f;
  }

}

void Game::keyReleased(sf::Event event)
{
  //keyreleased for paddle
  if (event.key.code == sf::Keyboard::A)
  {
     paddle->direction.x = -0.f;
  }
  else if (event.key.code == sf::Keyboard::D)
  {
    paddle->direction.x = 0.f;
  }
}

//ball movement function
void Game::ballmovement(float dt)
{
  if (!in_menu)
  {
    ball->getSprite()->move(ball->direction.x * dt, ball->direction.y * dt);
  }
}

void Game::gemmovement(float dt)
{
  for (int g = 0; g < 4; g++)
  {
    if (gems[g]->visibility == true)
    {
      gems[g]->getSprite()->move(0 , gems[g]->direction.y * dt);
    }
  }


  if (pl_score == 15)
  {
    gems[3]->visibility = true;
    gems[3]->getSprite()->setPosition(90, 85 - 270);
  }

  if (pl_score == 30)
  {
    gems[2]->visibility = true;
    gems[2]->getSprite()->setPosition(90, 85 - 270);
  }

  if (pl_score == 45)
  {
    gems[1]->visibility = true;
    gems[1]->getSprite()->setPosition(90, 85 - 270);
  }

  if (pl_score == 60)
  {
    gems[0]->visibility = true;
    gems[0]->getSprite()->setPosition(90, 85 - 270);
  }
}




