#include <SFML/Graphics.hpp>
#include <vector>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Snake"); // Render window

    // Movement
    float speed = 200.f; // Pixels per second
    sf::Vector2f direction(1.f, 0.f); // Move right Coordinate type stuff
    sf::Clock clock; // Tracking time

    // El squaro snako
    std::vector<sf::Vector2f> snake;
    snake.push_back(sf::Vector2f(400.f, 300.f)); // head
    snake.push_back(sf::Vector2f(380.f, 300.f)); // segment
    snake.push_back(sf::Vector2f(360.f, 300.f)); // tail

    sf::RectangleShape square(sf::Vector2f(20.f, 20.f));

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

        // Move each snake segment to position one in front of each other
        for (int i = snake.size() - 1; i > 0; i--) {
            snake[i] = snake[i - 1];
        }
        // move the head
        snake[0] += direction * speed * dt;

        window.clear(sf::Color::Black);
        // draw every segment after head
        for (int i = 0; i < snake.size(); i++) {
            square.setPosition(snake[i]);
            if (i <= 2)
                square.setFillColor(sf::Color::Green);  // head
            else
                square.setFillColor(sf::Color::Red);    // body
            window.draw(square);
        }
            
        window.display(); // Show the new frame
    }
}