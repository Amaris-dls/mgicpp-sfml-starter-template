
#ifndef SFML_GAME_H
#define SFML_GAME_H

#include <SFML/Graphics.hpp>

class Game
{
 public:
  Game(sf::RenderWindow& window);
  ~Game();
  bool init();
  void update(float dt);
  void render();
  void mouseButtonPressed(const sf::Event::MouseButtonPressed* event);
  void mouseButtonReleased(const sf::Event::MouseButtonReleased* event);
  void keyPressed(const sf::Event::KeyPressed* event);
  void keyReleased(const sf::Event::KeyReleased* event);

 private:
  sf::RenderWindow& window;
  
  sf::Texture background_texture;
  sf::Sprite background = sf::Sprite(background_texture);
  bool collisionCheck(sf::Vector2i click, sf::Sprite sprite);
  void spawn();

  sf::Sprite bird = sf::Sprite(bird_texture);
  sf::Texture bird_texture;
  sf::Font font;
  sf::Text title_text = sf::Text(font);
  sf::Text score_text = sf::Text(font);
  sf::Text timer_text = sf::Text(font);
  float time_remaining = 60.0f;

  bool in_menu;
  sf::Text menu_text = sf::Text(font);
  sf::Text play_option = sf::Text(font);
  sf::Text quit_option = sf::Text(font);
  bool play_selected = true;

  bool in_gameOver;
  sf::Text gameOver_text = sf::Text(font);
  sf::Text final_score_text = sf::Text(font);
  sf::Text restart_option = sf::Text(font);
  sf::Text exit_option = sf::Text(font);

  bool reverse = false;
  float speed = 500;

  int score = 0;

  bool bird_alive = true;
  bool time_go = false;

  float randx;
  float randy;

};

#endif // SFML_GAME_H
