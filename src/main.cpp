#include <iostream>
#include <SFML/Graphics.hpp>

#include "number_generator.hpp"
#include "math.hpp"
#include "Solver.hpp"
#include "Renderer.hpp"

int32_t main(int32_t, char* [])
{
    // Create window
    constexpr int32_t window_width = 1000;
    constexpr int32_t window_height = 1000;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 1;
    sf::RenderWindow window(sf::VideoMode(window_width, window_height), "Verlet", sf::Style::Default, settings);
    const uint32_t frame_rate = 60;
    window.setFramerateLimit(frame_rate);

    Solver solver;
    Renderer renderer{ window };

    const float        object_spawn_delay = 0.4f;
    const float        object_spawn_speed = 1200.0f;
    const sf::Vector2f object_spawn_position = { 750.0f, 300.0f };
    const float        object_min_radius = 1.0f;
    const float        object_max_radius = 20.0f;
    const uint32_t     max_objects_count = 0;
    const float        max_angle = 1.0f;

    bool add_mode = false;
    float preview_size = 20.0;
    float fps;
    sf::Clock clock2 = sf::Clock::Clock();
    sf::Time previousTime = clock2.getElapsedTime();
    sf::Time currentTime;

    sf::Clock clock;
    // Main loop
    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                window.close();
            }
            else if (event.type == sf::Event::KeyPressed) {
                const sf::Keyboard::Key keycode = event.key.code;
                if (keycode == sf::Keyboard::A) {
                    add_mode = not add_mode;
                }
                if (keycode == sf::Keyboard::Up) {
                    preview_size += 5;
                }
                if (keycode == sf::Keyboard::Down) {
                    preview_size -= 5;
                }
                if (keycode == sf::Keyboard::R) {
                    solver.clean();
                }
                if (keycode == sf::Keyboard::I) {
                    solver.invert_gravity();
                }
            }
            else if (event.type == sf::Event::MouseButtonPressed) {
                const sf::Mouse::Button button = event.mouseButton.button;
                if (button == sf::Mouse::Left) {
                    if (add_mode) {
                        Verlet object = Verlet(sf::Mouse::getPosition().x - window.getPosition().x, sf::Mouse::getPosition().y - window.getPosition().y - 30, preview_size);
                        solver.setObjectVelocity(object, object_spawn_speed * sf::Vector2f{ 0, 1 });
                        solver.addObject(object);
                    }
                }
            }
            else if (event.type == sf::Event::MouseWheelScrolled) 
            {
                if (event.mouseWheelScroll.delta > 0) // moving up
                {
                    preview_size += 5;
                }
                else
                {
                    preview_size -= 5;
                }
            }
        }

        if (solver.getObjectsCount() < max_objects_count && clock.getElapsedTime().asSeconds() >= object_spawn_delay) {
            clock.restart();
            Verlet object = Verlet(object_spawn_position, 15.0f);
            solver.setObjectVelocity(object, object_spawn_speed * sf::Vector2f{ 0, 1 });
            solver.addObject(object);
            const float t = solver.getTime();
        }

        /*currentTime = clock2.getElapsedTime();
        fps = 1.0f / (currentTime.asSeconds() - previousTime.asSeconds()); // the asSeconds returns a float
        std::cout << "fps =" << floor(fps) << std::endl; // flooring it will make the frame rate a rounded number
        previousTime = currentTime;
        std::cout << "Mouse x =" << sf::Mouse::getPosition().x << "Mouse y =" << sf::Mouse::getPosition().y << std::endl;*/ // flooring it will make the frame rate a rounded number
            
        // std::cout << add_mode << std::endl;

        solver.update(0.01f);
        window.clear(sf::Color::Black);
        renderer.render(solver);
        if (true) {
            sf::CircleShape circle{ 1.0f };
            circle.setPointCount(128);
            circle.setOrigin(1.0f, 1.0f);
            circle.move(sf::Mouse::getPosition().x-window.getPosition().x, sf::Mouse::getPosition().y - window.getPosition().y-30);
            circle.setScale(preview_size, preview_size);
            circle.setFillColor(sf::Color(255, 255, 255, 122));
            window.draw(circle);
        } 
        window.display();
    }
    return 0;
}