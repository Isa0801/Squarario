#include <SFML/Graphics.hpp>
#include <time.h>
#include <cstdlib>
#include "Player.h"
#include <iostream>
#include <vector>

class foodObj{
	private:
		sf::CircleShape foodBlob;
		sf::Color foodColor;
		sf::Vector2f foodXY;
		bool eaten = false;
	public:
		void setFoodBlob(sf::CircleShape foodBlob) {
			this->foodBlob = foodBlob;
	}
		void setfoodColor(sf::Color color) {
			this->foodColor = foodColor;
		}

		void updatePos(sf::Vector2f foodXY) {
			this->foodBlob.setPosition(foodXY);
		}

		sf::CircleShape getFoodBlob() {
			return foodBlob;
		}

		bool isEaten() {
			return this->eaten;
		}

		foodObj(sf::CircleShape foodBlob, sf::Color foodColor, sf::Vector2f foodXY) {
			this->foodBlob = foodBlob;
			this->foodColor = foodColor;
			this->foodXY = foodXY;
			this->foodBlob.setFillColor(foodColor);
			this->updatePos(foodXY);
		};
		~foodObj(){};
};

void getPos(sf::Vector2f& pos, int h, int w) {
	do
	{	pos.x = rand() % w;
		pos.y = rand() % h;
	} while ((!(pos.x > 10 && pos.x < w - 10) || !(pos.y > 10 && pos.y < w - 10)));
}

int main() {
	srand(time(NULL));

	int H = 1024, W = 1024;

	// create player instance 
	Player player(sf::Vector2f(25.0f, 25.0f) , sf::Vector2f(H/2, W/2), sf::Color::Red);

	//sf::Vector2f shapeSzie1(25, 25);
	sf::RenderWindow window(sf::VideoMode(H, W), "Squarar.io");
	//sf::RectangleShape shape1(shapeSzie1);
	//sf::CircleShape  food(10.0f);
	//shape1.setFillColor(sf::Color::Red);
	//food.setFillColor(sf::Color::White);
	//shape1.setPosition(H/2,W/2);
	std::vector<foodObj> foods;

	sf::Vector2f foodpos;

	for (int i = 0; i < 5; i++)
	{
		getPos(foodpos, H, W);
		foodObj food(sf::CircleShape(5.0f), sf::Color::White, foodpos);
		foods.push_back(food);
	}

	bool eaten = false;

	float movSpeed = 0.1f;
	
	while (window.isOpen())
	{
		sf::Event evt;

		while (window.pollEvent(evt))
		{
			if (evt.type == sf::Event::Closed)
			{
				window.close();

			}
		}

		sf::Vector2f shapepos = player.getPlayerBlob().getPosition();

		for (auto&& food: foods )
		{
			if (player.getPlayerBlob().getGlobalBounds().intersects(food.getFoodBlob().getGlobalBounds()))
			{
				eaten = true;
				getPos(foodpos, H, W);
				food.updatePos(foodpos);
				player.setPlayerSpeed(player.getPlayerSpeed());
				player.setPlayerSize(sf::Vector2f(player.getPlayerSize().x + 1.0f, player.getPlayerSize().y + 1.0f));
				sf::RectangleShape p = player.getPlayerBlob();
				p.setSize(player.getPlayerSize());
				player.setPlayerBlob(p);
			}
		}

		//moves player of wasd keys are pressed and making h, w as border for now
		player.movePlayer(sf::Keyboard(), H, W);

		window.clear();

			for (auto&& food: foods)
			{
				if (!food.isEaten());
				window.draw(food.getFoodBlob());
			}

		window.draw(player.getPlayerBlob());

		window.display();

		eaten = false;

	}



	return 0;
}