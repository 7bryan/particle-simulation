#include "SFML/Graphics/Rect.hpp"
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

  float velocity = 0.f;
  float gravity_force = 0.07f; // gravity acceleration

  Sand(sf::Vector2f size, sf::Vector2f pos, sf::Color color)
      : size(size), pos(pos), color(color) {
    rect.setSize(size);
    rect.setPosition(pos);
    rect.setFillColor(color);
    rect.setOrigin(size / 2.f); // set the origin pos to the middle of the rect
  }

  void draw(sf::RenderWindow &window) { window.draw(rect); } // draw the rect

  void gravity(float window_height) {
    velocity += gravity_force; // applying gravity (increase the velocuty by
                               // gravity force)
    rect.move({0.f, velocity});

    float bottom =
        rect.getPosition().y +
        size.y / 2.f; // define tge bottom of the sand (center + half its size)

    if (bottom >= window_height) { // check if the sand position greater than
                                   // the window height
      // clamp the sand perfectly to bottom
      rect.setPosition({rect.getPosition().x, window_height - size.y / 2.f});
      velocity = 0.f; // stop
    }
  }

  void collision(Sand sand, Sand other_sand) { return; }
};

std::vector<Sand> sands; // vector of sand

int main() {
  sf::Color black = sf::Color::Black;
  sf::Color white = sf::Color::White;

  sf::RenderWindow window(sf::VideoMode({1500, 900}), "sand particle");

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
      Sand sand({5.f, 5.f}, sf::Vector2f(sf::Mouse::getPosition(window)),
                white);
      sands.push_back(sand);
    }

    std::cout << sands.size() << "\n";

    window.clear(black);

    for (Sand &sand : sands) {
      sand.gravity(window.getSize().y);
      sand.draw(window);
    }

    window.display();
  }

  return 0;
}
