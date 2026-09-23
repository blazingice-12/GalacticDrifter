#pragma once
#include <SFML/Graphics.hpp>

class Ship
{
private:
	int maxHealth;
	int remainingHealth;
	sf::ConvexShape shape;
	sf::Vector2f velocity;
	float acceleration;
	float rotationSpeed;
	float maxSpeed;
	float WIDTH, HEIGHT;
	void move(float dt);
	void wrap();
	sf::Vector2f forward;

public:
	Ship(sf::Vector2f startPosition, sf::Color color, int maxHealth, float acceleration,float maxSpeed, float rotationSpeed, float WIDTH, float HEIGHT);

	void update(float dt);

	void draw(sf::RenderWindow& window);

	sf::Vector2f getPosition();

	sf::Vector2f getForward();

	sf::Vector2f getVelocity();
};
