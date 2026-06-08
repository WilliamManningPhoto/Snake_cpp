#include <iostream>      // For std::cout to print score to terminal on game over
#include <SFML/Graphics.hpp> // SFML graphics library for window, shapes, text and events
#include <vector>        // For std::vector to store snake segments
#include <cstdlib>       // For rand() and srand() to generate random food positions
#include <string>        // For std::to_string() to convert score int to string for display

const int CELL = 20; // Constant for cell size in pixel value

void drawGrid(sf::RenderWindow& window) {
    sf::Color gridColor(40, 40, 40); // Dark grey
    sf::RectangleShape line; 

    // Vertical lines
    for (int x = 0; x < 800; x += CELL) {
        line.setSize(sf::Vector2f(1.f, 600.f));
        line.setFillColor(gridColor);
        line.setPosition(x, 0);
        window.draw(line);
    }
    // Horizontal lines
    for (int y = 0; y < 600; y += CELL) {
        line.setSize(sf::Vector2f(800.f, 1.f));
        line.setFillColor(gridColor);
        line.setPosition(0, y);
        window.draw(line);
    }
}

int main() {
    // Path to a locally saved font
    sf::Font font;
    font.loadFromFile("C:/Windows/Fonts/arial.ttf");

    // Formatting of a font
    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(10.f, 10.f);
    int score = 0;

    // Utilise random seed at current time
    srand(time(0));

    sf::RenderWindow window(sf::VideoMode(800, 600), "Snake"); // Render window

    // Movement
    sf::Vector2f direction(1.f, 0.f); // Move right Coordinate type stuff
    sf::Clock clock; // Tracking time
    float moveTimer = 0.f;
    float moveInterval = 0.1f; // seconds between each step

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
        scoreText.setString("Score: " + std::to_string(score));
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
        // Only move when timer exceeds interval
        if (moveTimer >= moveInterval) {
            moveTimer = 0.f;
            for (int i = snake.size() - 1; i > 0; i--)
                snake[i] = snake[i - 1];
            snake[0] += direction * (float)CELL; // move one full cell

                // Check if head is on food
            if (snake[0] == food) {
                // Grow snake by adding a segment at the tail (lonk)
                snake.push_back(snake.back());
                // Respawn food
                food.x = (rand() % (800 / CELL)) * CELL;
                food.y = (rand() % (600 / CELL)) * CELL;
                // Incrementing score
                score++;
            }

            // Losing conditions
            if (snake[0].x < 0 || snake[0].x >= 800 ||
                snake[0].y < 0 || snake[0].y >= 600) {
                window.close(); // Exit game as you lsoe
                std::cout << "Your score was: " << score << std::endl;
            }
            for (int i = 1; i < snake.size(); i++) {
                if (snake[0] == snake[i]) {
                    window.close();
                    std::cout << "Your score was: " << score << std::endl;
                }
            }           
        }

        window.clear(sf::Color::Black);
        drawGrid(window);
        // Draw every segment after head
        for (int i = 0; i < snake.size(); i++) {
            square.setPosition(snake[i]);
            if (i == 0)
                square.setFillColor(sf::Color::Magenta);  // Head
            else
                square.setFillColor(sf::Color::Green);    // Body
            window.draw(square);
        }
        
        // Place food
        square.setFillColor(sf::Color::Red);
        square.setPosition(food);
        window.draw(square);

        // Draw text
        window.draw(scoreText);

        window.display(); // Show the new frame
    }
}