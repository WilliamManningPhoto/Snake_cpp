#include <SFML/Graphics.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Snake"); // Render window

    sf::RectangleShape square(sf::Vector2f(20.f, 20.f));
    square.setFillColor(sf::Color::Green);
    square.setPosition(400.f, 300.f);

    while (window.isOpen()) { // While the window is open do below:
        sf::Event event; // Stores a single event (keypress, close, resize etc)
        while (window.pollEvent(event)) { // Checks the event queue, returns true if there's an event to process
            if (event.type == sf::Event::Closed) // If the event was the X button being clicked
                window.close(); // Close the window
        }
        
        // Dont forget to draw to screen
        window.clear(sf::Color::Black); // Wipe the previous frame with black
        window.draw(square);
        window.display(); // Show the new frame
    }
}