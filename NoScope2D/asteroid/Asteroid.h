#pragma once

#include <SFML/Graphics.hpp>

class Asteroid
{
private:
	sf::CircleShape shape;
	sf::Vector2f velocity;

	float radius;

	float WIDTH, HEIGHT;

	bool alive = true;
	void move(float dt);
	void wrap();

public:
	Asteroid(sf::Vector2f position, sf::Vector2f velocity, float radius, float WIDTH, float HEIGHT);
	void update(float dt);
	void draw(sf::RenderWindow& window);
	bool isAlive();
	sf::Vector2f getPosition();
	float getRadius();
	const sf::CircleShape& getBounds() const;
};
