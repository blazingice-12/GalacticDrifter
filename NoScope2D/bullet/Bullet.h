#pragma once
#include <SFML/Graphics.hpp>

class Bullet
{
private:
	sf::CircleShape shape;
	sf::Vector2f velocity;
	sf::Vector2f shipVelocity;
	float speed;
	float lifeTime;
	float alive = true;

public:
	Bullet(sf::Vector2f position, sf::Vector2f forward, sf::Vector2f shipVelocity, float speed, float lifeTime);
	void update(float dt);
	void move(float dt);
	void draw(sf::RenderWindow& window);
	bool isAlive();
	const sf::CircleShape& getBounds() const;
};
