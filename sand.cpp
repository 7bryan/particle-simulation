#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/System/Vector2.hpp"
#include "SFML/Window/Keyboard.hpp"
#include "SFML/Window/Mouse.hpp"
#include "SFML/Window/VideoMode.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

struct Sand {
  sf::Vector2f size;
  sf::Vector2f pos;
  sf::Color color;

  sf::RectangleShape rect;

  Sand(sf::Vector2f size, sf::Vector2f pos, sf::Color color)
      : size(size), pos(pos), color(color) {
    rect.setSize(size);
    rect.setPosition(pos);
    rect.setFillColor(color);
    rect.setOrigin(size / 2.f);
  }

  void draw(sf::RenderWindow &window) { window.draw(rect); }

  void gravity() { return; }
};

std::vector<Sand> sands;

int main() {
  sf::Color black = sf::Color::Black;
  sf::Color white = sf::Color::White;

  sf::RenderWindow window(sf::VideoMode({1500, 1000}), "sand particle");

  while (window.isOpen()) {
    while (const std::optional event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>())
        window.close();
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
      if (sands.size() > 0) {
        sands.erase(sands.begin());
      }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::C)) {
      sands.erase(sands.begin(), sands.end());
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
      Sand sand({10.f, 10.f}, sf::Vector2f(sf::Mouse::getPosition(window)),
                white);
      sands.push_back(sand);
    }

    std::cout << sands.size() << "\n";

    window.clear(black);

    for (Sand &sand : sands) {
      sand.draw(window);
    }

    window.display();
  }

  return 0;
}
