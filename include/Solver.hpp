#pragma once
#include <vector>
#include <cmath>
#include <SFML/Graphics.hpp>

#include "Verlet.hpp"
#include "math.hpp"

struct Solver
{
	// Defining constants
	sf::Vector2f m_gravity = { 0.0f, 1000.0f };
	std::vector<Verlet> m_objects;
	sf::Vector2f m_constraint_center = { 500.0f, 500.0f };
	float m_constraint_radius = 400.0f;
	float m_time = 0.0f;
	float m_frame_dt = 0.0f;
	uint32_t m_sub_steps = 8;
	int32_t direction = 1;

	Solver() = default;

	void addObject(Verlet obj)
	{
		m_objects.push_back(obj);
	}

	void update(float dt)
	{
		const uint32_t sub_steps = 8;
		const float sub_dt = dt / (float) sub_steps;
		for (uint32_t i{ m_sub_steps }; i--;) {
			applyGravity();
			applyConstraints();
			checkCollisions();
			updatePositions(sub_dt);
		}
	}

	void updatePositions(float dt)
	{
		for (auto& obj : m_objects)
		{
			obj.updatePositions(dt);
		}
	}

	void applyGravity()
	{
		for (auto& obj : m_objects)
		{
			obj.accelerate(m_gravity, direction);
		}
	}

	void applyConstraints()
	{
		for (auto& obj : m_objects) {
			const sf::Vector2f v =  m_constraint_center - obj.pos_curr;
			const float dist = sqrt(v.x * v.x + v.y * v.y);
			if (dist > (m_constraint_radius - obj.radius))
			{
				const sf::Vector2f n = v / dist;
				obj.pos_curr = m_constraint_center - n * (m_constraint_radius - obj.radius);
			}
		}
	}

	void applyConstraintsSquare()
	{
		for (auto& obj : m_objects) {
			const sf::Vector2f v = m_constraint_center - obj.pos_curr;
			const float dist = sqrt(v.x * v.x + v.y * v.y);
			if (dist > (m_constraint_radius - obj.radius))
			{
				const sf::Vector2f n = v / dist;
				obj.pos_curr = m_constraint_center - n * (m_constraint_radius - obj.radius);
			}
		}
	}

	void checkCollisions()
	{
		const float    response_coef = 0.75f;
		const uint64_t objects_count = m_objects.size();
		// Iterate on all objects
		for (uint64_t i{ 0 }; i < objects_count; ++i) {
			Verlet& object_1 = m_objects[i];
			// Iterate on object involved in new collision pairs
			for (uint64_t k{ i + 1 }; k < objects_count; ++k) {
				Verlet& object_2 = m_objects[k];
				const sf::Vector2f v = object_1.pos_curr - object_2.pos_curr;
				const float dist2 = v.x * v.x + v.y * v.y;
				// The minimum distance is the sum of the two radius of the objects
				const float min_dist = object_1.radius + object_2.radius;
				// Check overlapping
				if (dist2 < min_dist * min_dist) {
					const float        dist = sqrt(dist2);
					const sf::Vector2f n = v / dist;
					const float mass_ratio_1 = object_1.radius / (object_1.radius + object_2.radius);
					const float mass_ratio_2 = object_2.radius / (object_1.radius + object_2.radius);
					const float delta = 0.5f * response_coef * (dist - min_dist);
					// Update positions
					object_1.pos_curr -= n * (mass_ratio_2 * delta);
					object_2.pos_curr += n * (mass_ratio_1 * delta);
				}
			}
		}
	}

	void setObjectVelocity(Verlet& object, sf::Vector2f v)
	{
		object.setVelocity(v, getStepDt());
	}

	void invert_gravity() {
		direction = -direction;
	}

	void clean() {
		m_objects = {};
	}

	[[nodiscard]]
	const std::vector<Verlet>& getObjects() const
	{
		return m_objects;
	}

	[[nodiscard]]
	sf::Vector3f getConstraint() const
	{
		return { m_constraint_center.x, m_constraint_center.y, m_constraint_radius };
	}

	[[nodiscard]]
	uint64_t getObjectsCount() const
	{
		return m_objects.size();
	}

	[[nodiscard]]
	float getTime() const
	{
		return m_time;
	}

	[[nodiscard]]
	float getStepDt() const
	{
		return m_frame_dt / static_cast<float>(m_sub_steps);
	}
};