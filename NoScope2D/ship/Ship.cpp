#include "Ship.h"

Ship::Ship(sf::Vector2f startPosition, sf::Color color, int maxHealth, float acceleration, float maxSpeed, float rotationSpeed, float WIDTH, float HEIGHT) :
	maxHealth(maxHealth), remainingHealth(maxHealth), velocity(0.f, 0.f), acceleration(acceleration), maxSpeed(maxSpeed), rotationSpeed(rotationSpeed),
	WIDTH(WIDTH), HEIGHT(HEIGHT), forward(0.f, -1.f)
{
	shape.setPointCount(3);

	shape.setPoint(0, { 0.f, -20.f });
	shape.setPoint(1, { -15.f, 20.f });
	shape.setPoint(2, { 15.f, 20.f });

	shape.setOrigin({ 0.f, 0.f });

	shape.setFillColor(color);

	shape.setPosition(startPosition);
}

void Ship::update(float dt)
{
	move(dt);
	wrap();
}

void Ship::move(float dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
	{
		shape.rotate(sf::degrees(-rotationSpeed * dt));
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		shape.rotate(sf::degrees(rotationSpeed * dt));
	}

	float angle = shape.getRotation().asDegrees() - 90.f;

	constexpr float PI = 22.f / 7.f;
	auto radians = angle * PI/180;

	forward.x = std::cos(radians);
	forward.y = std::sin(radians);


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
	{
		velocity += forward * acceleration * dt;
	}
	else
	{
		velocity -= velocity * 0.5f * dt;
	}

	float currentSpeed = velocity.length();

	if (currentSpeed > maxSpeed)
	{
		velocity = velocity.normalized() * maxSpeed;
	}

	shape.move(velocity * dt);
}

void Ship::draw(sf::RenderWindow& window)
{
	window.draw(shape);
}

void Ship::wrap()
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

sf::Vector2f Ship::getPosition()
{
	return shape.getPosition();
}

sf::Vector2f Ship::getForward()
{
	return forward;
}

sf::Vector2f Ship::getVelocity()
{
	return velocity;
}