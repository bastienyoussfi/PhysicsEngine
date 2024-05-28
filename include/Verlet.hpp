#pragma once
#include <vector>
#include <cmath>
#include <SFML/Graphics.hpp>

#include "math.hpp"

struct Verlet
{
	sf::Vector2f pos_curr;
	sf::Vector2f pos_old;
	sf::Vector2f acceleration;
	float        radius = 50.0f;
	sf::Color    color = sf::Color::White;

	Verlet() = default;

	Verlet(sf::Vector2f position_, float radius_)
		: pos_curr{ position_ }
		, pos_old{ position_ }
		, acceleration{ 0.0f, 0.0f }
		, radius{ radius_ }
	{}

	Verlet(float x, float y, float radius_)
		: pos_curr{ sf::Vector2f(x, y) }
		, pos_old{ sf::Vector2f(x, y) }
		, acceleration{ 0.0f, 0.0f }
		, radius{ radius_ }
	{}

	void updatePositions(float dt)
	{
		const sf::Vector2f velocity = pos_curr - pos_old;
		// Save current position
		pos_old = pos_curr;
		pos_curr = pos_curr + velocity + acceleration * dt * dt;
		// Reset acceleration
		acceleration = {};
	}

	void accelerate(sf::Vector2f acc, int32_t direction)
	{
		acceleration += acc;
		if (direction == -1) {
			acceleration = -acceleration;
		}
	}

	void setVelocity(sf::Vector2f v, float dt)
	{
		pos_old = pos_curr - (v * dt);
	}
};

