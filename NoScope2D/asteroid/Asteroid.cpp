#include "Asteroid.h"

Asteroid::Asteroid(sf::Vector2f position, sf::Vector2f velocity, float radius, float WIDTH, float HEIGHT) : 
	HEIGHT(HEIGHT), WIDTH(WIDTH), radius(radius), velocity(velocity)
{
	shape.setFillColor(sf::Color::Red);
	shape.setRadius(radius);
	shape.setOrigin({ radius, radius });
	shape.setPosition(position);
}

void Asteroid::update(float dt)
{
	move(dt);
	wrap();
}

void Asteroid::draw(sf::RenderWindow& window)
{
	window.draw(shape);
}

void Asteroid::move(float dt)
{
	shape.move(velocity * dt);
}

void Asteroid::wrap()
{
	sf::Vector2f pos = shape.getPosition();
	if (pos.x > WIDTH)
	{
		shape.setPosition({ 0, pos.y });
	}
	if (pos.x < 0)
	{
		shape.setPosition({ WIDTH, pos.y });
	}
	if (pos.y > HEIGHT)
	{
		shape.setPosition({ pos.x, 0 });
	}
	if (pos.y < 0)
	{
		shape.setPosition({ pos.x, HEIGHT });
	}
}

bool Asteroid::isAlive()
{
	return alive;
}

sf::Vector2f Asteroid::getPosition()
{
	return shape.getPosition();
}

float Asteroid::getRadius()
{
	return radius;
}

sf::CircleShape Asteroid::getBounds()
{
	return shape;
}