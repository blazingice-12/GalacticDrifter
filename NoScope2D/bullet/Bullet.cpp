#include "Bullet.h"

Bullet::Bullet(sf::Vector2f position, sf::Vector2f forward, sf::Vector2f shipVelocity, float speed, float lifeTime) :
	velocity(forward), speed(speed), lifeTime(lifeTime), shipVelocity(shipVelocity)
{
	shape.setFillColor(sf::Color::Red);
	shape.setRadius(3.f);
	shape.setOrigin({ 3.f, 3.f });
	shape.setPosition(position);
}

void Bullet::update(float dt)
{
	move(dt);
	lifeTime -= dt;

	if (lifeTime <= 0.f)
	{
		alive = false;
	}
}

void Bullet::move(float dt)
{
	shape.move((shipVelocity + velocity * speed) * dt);
}

void Bullet::draw(sf::RenderWindow& window)
{
	window.draw(shape);
}

bool Bullet::isAlive()
{
	return alive;
}

const sf::CircleShape& Bullet::getBounds() const
{
	return shape;
}
