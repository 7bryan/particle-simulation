#include "SFML/Graphics/Rect.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/System/Vector2.hpp"
#include "SFML/Window/Keyboard.hpp"
#include "SFML/Window/Mouse.hpp"
#include "SFML/Window/VideoMode.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

enum class CellType { Empty, Sand, Water, Smoke, Fire, GunPowder };

struct Cell {
  CellType type = CellType::Empty;
  bool update = false; // preventing doubling movement
  int lifetime = 0;    // for smoke and fire
};

const int cellsize = 5;
const int cols = 1500 / cellsize;
const int rows = 900 / cellsize;

std::vector<std::vector<Cell>>
    grid(rows, std::vector<Cell>(cols)); // 0 for empty space

void update_sand(int col, int row) {
  // apply gravity for sand
  if (row + 1 < rows && grid[row + 1][col].type == CellType::Empty) {
    std::swap(grid[row][col], grid[row + 1][col]);
  }
}

void update_water() { return; }

void update_smoke() { return; }

void update_fire() { return; }

void update_gunpowder() { return; }

void update_grid() {
  // updating from bottom to up
  for (int row = rows - 1; row >= 0; row--) {
    for (int col = 0; col < cols; col++) {
      switch (grid[row][col].type) {
      case CellType::Sand:
        update_sand(col, row);
        break;
      case CellType::Water:
        update_water();
        break;
      case CellType::Smoke:
        update_smoke();
        break;
      case CellType::Fire:
        update_fire();
        break;
      case CellType::GunPowder:
        update_gunpowder();
        break;
      }
    }
  }
}

void draw_grid(sf::RenderWindow &window) {
  // draw every particle
  sf::RectangleShape rect;
  rect.setSize(sf::Vector2f{cellsize, cellsize});

  for (int row = 0; row < rows; row++) {
    for (int col = 0; col < cols; col++) {
      // draw everything if the grid is not empty
      if (grid[row][col].type != CellType::Empty) {
        rect.setPosition(
            sf::Vector2f{(float)(col * cellsize), (float)(row * cellsize)});

        if (grid[row][col].type == CellType::Sand)
          rect.setFillColor(sf::Color::Yellow);

        window.draw(rect);
      }
    }
  }
}

int main() {
  sf::Color black = sf::Color::Black;
  sf::Color white = sf::Color::White;

  CellType current_type = CellType::Sand;

  sf::RenderWindow window(sf::VideoMode({1500, 900}), "sand particle");

  while (window.isOpen()) {
    while (const std::optional event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>())
        window.close();
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
      for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
          grid[row][col].type = CellType::Empty;
        }
      }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::C)) {
      grid.erase(grid.begin(), grid.end());
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
      sf::Vector2i mouse = sf::Mouse::getPosition(window);

      int col = mouse.x / cellsize;
      int row = mouse.y / cellsize;

      if (row >= 0 && row < rows && col >= 0 && col < cols) {
        // logic for determining fucntion to call based on the type inside the
        // grid
        grid[row][col].type = current_type;
      }
    }

    update_grid();
    window.clear(black);
    draw_grid(window);
    window.display();
  }

  return 0;
}
