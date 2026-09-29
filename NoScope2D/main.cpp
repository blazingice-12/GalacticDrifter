#include <SFML/Graphics.hpp>
#include <vector>
#include <algorithm>
#include <iostream>
#include "ship/Ship.h"
#include "bullet/Bullet.h"
#include "asteroid/Asteroid.h"

int main()
{
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
	const float WIDTH = static_cast<float>(desktop.size.x), HEIGHT = static_cast<float>(desktop.size.y);

	sf::RenderWindow window(desktop, "Asteroids2D", sf::State::Windowed);

	sf::View view(window.getDefaultView());

	sf::Clock clock;

	sf::Vector2f pos = { WIDTH/2.f, HEIGHT/2.f };

	float acceleration = 300.f, maxSpeed = 600.f;
	float rotationSpeed = 180.f;
	Ship player(pos, sf::Color::White, 100, acceleration, maxSpeed, rotationSpeed, WIDTH, HEIGHT);

	std::vector<Bullet> bullets;
	float fireCooldown = 0.f;

	std::vector<Asteroid> asteroids;

	//=======================================================================================================================================
	asteroids.emplace_back(
		sf::Vector2f(100.f, 100.f),
		sf::Vector2f(100.f, 50.f),
		40.f,
		WIDTH,
		HEIGHT
	);

	asteroids.emplace_back(
		sf::Vector2f(600.f, 300.f),
		sf::Vector2f(-80.f, 120.f),
		30.f,
		WIDTH,
		HEIGHT
	);

	asteroids.emplace_back(
		sf::Vector2f(1000.f, 600.f),
		sf::Vector2f(-150.f, -40.f),
		50.f,
		WIDTH,
		HEIGHT
	);
	//=======================================================================================================================================
	while (window.isOpen())
	{
		while (const std::optional event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
			{
				window.close();
			}
		}
		float dt = clock.restart().asSeconds();

		window.setView(view);
		
		//=======================================================================================================================================
		//UPDATE
		//=======================================================================================================================================
		player.update(dt);

		fireCooldown -= dt;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && fireCooldown <= 0)
		{
			fireCooldown = 0.2f;
			sf::Vector2f bulletPosition = player.getPosition();
			sf::Vector2f bulletForward = player.getForward();
			sf::Vector2f shipVelocity = player.getVelocity();

			Bullet bullet(bulletPosition + bulletForward * 20.f, bulletForward, shipVelocity, 300.f, 4.f);

			bullets.push_back(bullet);
		}

		for (Bullet& bullet : bullets)
		{
			bullet.update(dt);
		}

		for (int i = 0; i < bullets.size();)
		{
			if (!bullets[i].isAlive())
			{
				bullets.erase(bullets.begin() + i);
			}
			else
			{
				i++;
			}
		}

		for (Asteroid& asteroid : asteroids)
		{
			asteroid.update(dt);
		}
		//Check bullet-astweroid collisions
		for (int i = 0; i < bullets.size();)
		{
			for (int j = 0; j < asteroids.size();)
			{
				if (bullets[i].getBounds().getGlobalBounds().findIntersection(asteroids[j].getBounds().getGlobalBounds()))
				{
					bullets.erase(bullets.begin() + i);
					asteroids.erase(asteroids.begin() + j);
					break;
				}
				else
				{
					j++;
				}
			}
			if (i < bullets.size())
			{
				i++;
			}
		}

		//=======================================================================================================================================
		//=======================================================================================================================================
		//=======================================================================================================================================
		
		window.clear(sf::Color::Black);

		//=======================================================================================================================================
		//DRAW
		//=======================================================================================================================================
		player.draw(window);

		for (Bullet& bullet : bullets)
		{
			bullet.draw(window);
		}

		for (Asteroid& asteroid : asteroids)
		{
			asteroid.draw(window);
		}
		//=======================================================================================================================================
		//=======================================================================================================================================
		//=======================================================================================================================================

		window.display();
	}

	return 0;
}
