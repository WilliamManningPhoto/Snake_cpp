#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>

const int CELL = 20; // Constant for cell size in pixel value

void drawGrid(sf::RenderWindow& window) {
    sf::Color gridColor(40, 40, 40); // dark grey
    sf::RectangleShape line; 

    // vertical lines
    for (int x = 0; x < 800; x += CELL) {
        line.setSize(sf::Vector2f(1.f, 600.f));
        line.setFillColor(gridColor);
        line.setPosition(x, 0);
        window.draw(line);
    }
    // horizontal lines
    for (int y = 0; y < 600; y += CELL) {
        line.setSize(sf::Vector2f(800.f, 1.f));
        line.setFillColor(gridColor);
        line.setPosition(0, y);
        window.draw(line);
    }
}

int main() {
    // Utilise random seed at current time
    srand(time(0));

    sf::RenderWindow window(sf::VideoMode(800, 600), "Snake"); // Render window

    // Movement
    sf::Vector2f direction(1.f, 0.f); // Move right Coordinate type stuff
    sf::Clock clock; // Tracking time
    float moveTimer = 0.f;
    float moveInterval = 0.05f; // seconds between each step

    // Food
    sf::Vector2f food;
    food.x = (rand() % (800 / CELL)) * CELL;
    food.y = (rand() % (600 / CELL)) * CELL;

    // El squaro snako
    std::vector<sf::Vector2f> snake;
    snake.push_back(sf::Vector2f(400.f, 300.f)); // head
    snake.push_back(sf::Vector2f(380.f, 300.f)); // segment
    snake.push_back(sf::Vector2f(360.f, 300.f)); // tail

    sf::RectangleShape square(sf::Vector2f(20.f, 20.f));

    while (window.isOpen()) { // While the window is open do below:
        float dt = clock.restart().asSeconds();
        moveTimer += dt;

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
        // only move when timer exceeds interval
        if (moveTimer >= moveInterval) {
            moveTimer = 0.f;
            for (int i = snake.size() - 1; i > 0; i--)
                snake[i] = snake[i - 1];
            snake[0] += direction * (float)CELL; // move one full cell
        }

        window.clear(sf::Color::Black);
        drawGrid(window);
        // draw every segment after head
        for (int i = 0; i < snake.size(); i++) {
            square.setPosition(snake[i]);
            if (i == 0)
                square.setFillColor(sf::Color::Magenta);  // head
            else
                square.setFillColor(sf::Color::Green);    // body
            window.draw(square);
        }
        
        // Place food
        square.setFillColor(sf::Color::Red);
        square.setPosition(food);
        window.draw(square);

        window.display(); // Show the new frame
    }
}