
#include "Game.h"
#include <iostream>

Game::Game(sf::RenderWindow& game_window)
  : window(game_window)
{
  srand(time(NULL)); //seeds random number generator with the current time
}

Game::~Game()
{

}

// We call this once after the game class is instantiated
bool Game::init()
{
	score = 0;
	//menu
	in_menu = true;


	if (!font.openFromFile("../Data/Fonts/OpenSans-Bold.ttf")) {
		std::cout << "font did not load \n";
	}
	menu_text.setString("Welcome to Whackamole. Please select an option");
	menu_text.setFont(font);
	menu_text.setCharacterSize(40);
	menu_text.setFillColor(sf::Color::White);
	menu_text.setPosition({
		float(window.getSize().x / 2 - menu_text.getGlobalBounds().size.x / 2),
		float(window.getSize().y / 2 - menu_text.getGlobalBounds().size.y / 2) });
	play_option.setString("Play");
	play_option.setFont(font);
	play_option.setCharacterSize(30);
	play_option.setFillColor(sf::Color::White);
	play_option.setPosition({
		float(window.getSize().x / 2 - play_option.getGlobalBounds().size.x / 2),
		float(window.getSize().y / 2 + 50) });
	quit_option.setString("Quit");
	quit_option.setFont(font);
	quit_option.setCharacterSize(30);
	quit_option.setFillColor(sf::Color::White);
	quit_option.setPosition({
		float(window.getSize().x / 2 - quit_option.getGlobalBounds().size.x / 2),
		float(window.getSize().y / 2 + 100) });


	//background sprite
	if (!background_texture.loadFromFile("../Data/Images/WhackaMole Worksheet/background.png"))

	{
		std::cout << "Failed to load background texture!\n";
		return false;
	}
	background.setTexture(background_texture);
	//bird sprite
	if (!bird_texture.loadFromFile("../Data/Images/WhackaMole Worksheet/bird.png")) {
		std::cout << "Failed to load bird texture!\n";
		return false;
	}
	bird.setTexture(bird_texture);
	bird.setPosition({ 100, 100 });
	bird.setScale({ 0.5f, 0.5f });

	//text sprute
	if (!font.openFromFile("../Data/Fonts/OpenSans-Bold.ttf"))
	{
		std::cout << "font did not load \n";
	}
	title_text.setString("Whack-a-mole");
	title_text.setFont(font);
	title_text.setCharacterSize(50);
	title_text.setFillColor(sf::Color(255, 255, 255, 128));
	title_text.setPosition({
		window.getSize().x / 2 - title_text.getGlobalBounds().size.x / 2,
		window.getSize().y / 2 - title_text.getGlobalBounds().size.y / 2 });

	//score text
	score_text.setFont(font);
	score_text.setCharacterSize(50);
	score_text.setFillColor(sf::Color::Blue);
	score_text.setPosition({ 1000, 50 });
	score_text.setString(std::to_string(score));

	//timer text
	timer_text.setFont(font);
	timer_text.setCharacterSize(50);
	timer_text.setFillColor(sf::Color::Red);
	timer_text.setPosition({ 50, 50 });
	timer_text.setString("0");


	// game over
	in_gameOver = false;

	if (!font.openFromFile("../Data/Fonts/OpenSans-Bold.ttf"))
	{
		std::cout << "font did not load \n";
	}
	gameOver_text.setString("Game Over");
	gameOver_text.setFont(font);
	gameOver_text.setCharacterSize(40);
	gameOver_text.setFillColor(sf::Color::White);
	gameOver_text.setPosition(
		{ float(window.getSize().x / 2 - gameOver_text.getGlobalBounds().size.x / 2),
		 float(window.getSize().y / 2 - gameOver_text.getGlobalBounds().size.y / 2) });
	restart_option.setString("Play");
	restart_option.setFont(font);
	restart_option.setCharacterSize(30);
	restart_option.setFillColor(sf::Color::White);
	restart_option.setPosition({
		float(window.getSize().x / 2 - restart_option.getGlobalBounds().size.x / 2),
		float(window.getSize().y / 2 + 50) });
	exit_option.setString("Quit");
	exit_option.setFont(font);
	exit_option.setCharacterSize(30);
	exit_option.setFillColor(sf::Color::White);
	exit_option.setPosition({
		float(window.getSize().x / 2 - exit_option.getGlobalBounds().size.x / 2),
		float(window.getSize().y / 2 + 100) });




  return true;
}

// Update runs after event polling and before rendering
// use it for everything that needs to update between frames
void Game::update(float dt)
{
	// Decrease remaining time (dt should be seconds from your game loop)
	if (in_menu == false && !in_gameOver)
	{
		time_go = true;
		time_remaining -= dt;
		if (time_remaining < 0.0f)
			time_remaining = 0.0f;
		// Update displayed timer (integer seconds)
		timer_text.setString(std::to_string(static_cast<int>(time_remaining)));
		// If timer reached zero, go to game over
		if (time_remaining <= 0.0f)
		{
			in_gameOver = true;
			in_menu = false;
			time_go = false;
		}


	}


	if (reverse == true)
	{
		bird.move({1.0f * speed * dt, 0});
		bird.setScale({0.5f, 0.5f});
		bird.setTextureRect(sf::IntRect({ 0, 0 }, { int(bird.getLocalBounds().size.x), int(bird.getLocalBounds().size.y) }));


	}
	else if (reverse == false)
	{
		bird.move({-1.0f * speed * dt, 0});
		bird.setScale({0.5f, 0.5f});
		bird.setTextureRect(sf::IntRect({int( bird.getLocalBounds().size.x), 0 }, {int( - bird.getLocalBounds().size.x), int( bird.getLocalBounds().size.y)}));
	}
	

	if (
		(bird.getPosition().x >
			(window.getSize().x - bird.getGlobalBounds().size.x)) ||
		(bird.getPosition().x < 0))
	{
		reverse = !reverse;
	}

}

// Runs after update, use it to tell the window what to draw this frame
void Game::render()
{
	if (in_menu == true)
	{
		window.draw(menu_text);
		window.draw(play_option);
		window.draw(quit_option);
	}

	else if (in_gameOver == true)
	{

		window.draw(gameOver_text);
		window.draw(restart_option);
		window.draw(exit_option);
	}
	else
	{
		window.draw(background);
		window.draw(title_text);
		window.draw(score_text);
		window.draw(timer_text);
		if (bird_alive == true)
		{
			window.draw(bird);
		}
	}

}

//Called by event polling when a MouseButtonPressed event is found
void Game::mouseButtonPressed(const sf::Event::MouseButtonPressed* event)
{
	// Event contains mouse position and which button was clicked

	// Don't need to extract position to a variable like this, this is just to show you it's a Vector2i
	sf::Vector2i position = event->position;

	// You can tell which button was pressed by comparing it to SFML's definitions of mouse buttons
	if (event->button == sf::Mouse::Button::Left)
	{
		//Left mouse button was pressed
		if (collisionCheck(position, bird))
		{
			bird_alive = false;
			spawn();
		}
	}
}

//Called by event polling when a MouseButtonReleased event is found
void Game::mouseButtonReleased(const sf::Event::MouseButtonReleased* event)
{
	//Works the same as MouseButtonPressed
	if (event->button == sf::Mouse::Button::Left)
	{
		//Left mouse button was released
	}
}

// Called by event polling when a KeyPressed event is found
void Game::keyPressed(const sf::Event::KeyPressed* event)
{
	// You can tell which button was pressed by the scancode to SFML's definitions of keyboard keys
	if (event->scancode == sf::Keyboard::Scancode::Left || event->scancode == sf::Keyboard::Scancode::Right)
	{
		play_selected = !play_selected;
		if (play_selected)
		{
			play_option.setFillColor(sf::Color::Blue);
			quit_option.setFillColor(sf::Color::White);
			restart_option.setFillColor(sf::Color::Blue);
			exit_option.setFillColor(sf::Color::White);
		}
		else
		{

			play_option.setFillColor(sf::Color::White);
			quit_option.setFillColor(sf::Color::Blue);
			restart_option.setFillColor(sf::Color::White);
			exit_option.setFillColor(sf::Color::Blue);
		}

	}
	else if (event->scancode == sf::Keyboard::Scancode::Enter) {
		if (play_selected && in_menu == true)
		{
			in_menu = false;
		}
		else if (play_selected && in_gameOver == true)
		{
			in_gameOver = false;
			score = 0;
			score_text.setString(std::to_string(score));
			time_remaining = 60.0f;
			timer_text.setString(std::to_string(static_cast<int>(time_remaining)));

			spawn();
		}
		else
		{
			window.close();
		}
	}

}

// Called by event polling when a KeyReleased event is found
void Game::keyReleased(const sf::Event::KeyReleased* event)
{
	// Works the same way as KeyPressed
	if (event->scancode == sf::Keyboard::Scancode::W)
	{
		// W was released
	}

}

bool Game::collisionCheck(sf::Vector2i click, sf::Sprite sprite)
{
	if (click.x >= sprite.getPosition().x &&
		click.x <= (sprite.getPosition().x + sprite.getGlobalBounds().size.x) &&
		click.y >= sprite.getPosition().y &&
		click.y <= (sprite.getPosition().y + sprite.getGlobalBounds().size.y))
	{
		score += 1;
		score_text.setString(std::to_string(score));
		return true;
	}
	else
	{
		return false;
	}

}

void Game::spawn()
{
	randx = rand() % (window.getSize().x - (int(bird.getGlobalBounds().size.x)));
	randy = rand() % (window.getSize().y - (int(bird.getGlobalBounds().size.y)));
	bird.setPosition({randx, randy});
	bird_alive = true;


}


