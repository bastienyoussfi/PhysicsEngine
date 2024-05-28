#pragma once
#include "solver.hpp"


class Renderer
{
public:
    explicit
        Renderer(sf::RenderTarget& target)
        : m_target{ target }
    {

    }

    void render(const Solver& solver) const
    {

        // Draw the preview circle
        const sf::Vector3f constraint = solver.getConstraint();
        sf::CircleShape constraintCircle{ constraint.z };
        constraintCircle.setOrigin(constraint.z, constraint.z);
        constraintCircle.setFillColor(sf::Color(85, 158, 131));
        constraintCircle.setPosition(500, 500);
        constraintCircle.setPointCount(128);
        m_target.draw(constraintCircle);

        // Draw all the objects in the set
        sf::CircleShape circle{ 1.0f };
        circle.setPointCount(128);
        circle.setOrigin(1.0f, 1.0f);
        const auto& objects = solver.getObjects();
        for (const auto& obj : objects) {
            circle.setPosition(obj.pos_curr);
            circle.setScale(obj.radius, obj.radius);
            circle.setFillColor(obj.color);
            m_target.draw(circle);
        }
    }

private:
    sf::RenderTarget& m_target;
};