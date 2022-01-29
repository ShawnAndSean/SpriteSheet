#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <chrono>
#include "characters.h"

using namespace std;


int main() 
{
	srand(time(NULL));
	string backgroundpic[4] = { "DRYLAND.png","RUSSIA.png","ARENA.png","HELL.png" };
	string sprite_enemies[5] = { "SKELETON.png","FBI.png","ROMANS.png","ROMANS2.png","NUDE GUY.png"};
	string background_string = backgroundpic[rand() % sizeof(backgroundpic) / sizeof(backgroundpic[0])];
	sf::Texture background;
	if (!background.loadFromFile(background_string)){
		return EXIT_FAILURE;
	}
		
	sf::Sprite background_sprite(background);
	sf::Sprite explorer;
	int screen_width = background.getSize().x;
	int screen_height = background.getSize().y;

	Explorer_Movement explorer1({ 100.0f,100.0f },explorer);
	Explorer_Movement explorer2({ 200.0f,100.0f }, explorer);
	auto timepoint = std::chrono::steady_clock::now();
	sf::RenderWindow window(sf::VideoMode(screen_width, screen_height), "Indiana Jones: Temple Rush");
	while (window.isOpen()) 
	{
		sf::Event game;
		while(window.pollEvent(game))
		{
			if (game.type == sf::Event::Closed) {
				window.close();
			}	
		}
		float deltatime;
		{
			//makes or stops the newtimepoint to a particular timepoint using the const variable to hold it for the mean time
			const auto newTimepoint = std::chrono::steady_clock::now();
			//deltatime is equal to the time interval of the float to represent dractions of  newTimepoint minus timepoint where
			//it will be counted by .count()
			deltatime = std::chrono::duration<float>(newTimepoint - timepoint).count();
			//returns to normal back again where timepoint is equal to newTimepoint
			timepoint = newTimepoint;
		}
		sf::Vector2f currentdirection(0.0f, 0.0f); // initialization of the current direction or the starting position.


		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) //up
		{
			currentdirection.y = currentdirection.y - 1.0f;
			explorer1.setDirections(currentdirection);
			explorer1.updatePositionAllOver(deltatime);
			explorer2.setDirections(currentdirection);
			explorer2.updatePositionAllOver(deltatime);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))//down
		{
			currentdirection.y = currentdirection.y + 1.0f;
			explorer1.setDirections(currentdirection);
			explorer1.updatePositionAllOver(deltatime);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) //left
		{
			currentdirection.x = currentdirection.x - 1.0f;
			explorer1.setDirections(currentdirection);
			explorer1.updatePositionAllOver(deltatime);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))//right
		{
			currentdirection.x = currentdirection.x + 1.0f;
			explorer1.setDirections(currentdirection);
			explorer1.updatePositionAllOver(deltatime);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))//right
		{
			static constexpr float speed = 100;
			currentdirection.x;
			currentdirection.y;
			explorer1.setDirections(currentdirection);
			explorer1.updatePositionAllOver(deltatime);
		}
		else
		{
			explorer1.setDirections(currentdirection);
			explorer1.stopWalk(deltatime);
		}

		window.clear();
		window.draw(background_sprite);
		explorer1.ShiftingandDraw(window);
		explorer2.ShiftingandDraw(window);
		window.display();
		
		
	}
	return EXIT_SUCCESS;
}