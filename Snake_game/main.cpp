#include <SFML/Graphics.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Snake"); // Render window

    // El squaro
    sf::RectangleShape square(sf::Vector2f(20.f, 20.f));
    square.setFillColor(sf::Color::Green);
    square.setPosition(400.f, 300.f);

    // Movement
    float speed = 200.f; // Pixels per second
    sf::Vector2f direction(1.f, 0.f); // Move right Coordinate type stuff
    sf::Clock clock; // Tracking time

    while (window.isOpen()) { // While the window is open do below:
        float dt = clock.restart().asSeconds();

        sf::Event event; // Stores a single event (keypress, close, resize etc)
        while (window.pollEvent(event)) { // Checks the event queue, returns true if there's an event to process
            if (event.type == sf::Event::Closed) // If the event was the X button being clicked
                window.close(); // Close the window
            
            // Events such as movement added here (interaction)
            if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::W)
                direction = sf::Vector2f(0.f, -1.f);
            if (event.key.code == sf::Keyboard::S)
                direction = sf::Vector2f(0.f, 1.f);
            if (event.key.code == sf::Keyboard::A)
                direction = sf::Vector2f(-1.f, 0.f);
            if (event.key.code == sf::Keyboard::D)
                direction = sf::Vector2f(1.f, 0.f);
    }
        }

        square.move(direction * speed * dt); // Move el squaro
        
        // Dont forget to draw to screen
        window.clear(sf::Color::Black); // Wipe the previous frame with black
        window.draw(square);
        window.display(); // Show the new frame
    }
}