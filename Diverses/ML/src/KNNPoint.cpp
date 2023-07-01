#include "../include/KNNPoint.hpp"

#include <cmath>

KNNPoint::KNNPoint(int x, int y) : x(x), y(y) {
  if (x < 50 && y < 50)
    this->color = Color::RED;
  else if (x > 50 && y > 50)
    this->color = Color::BLUE;
  else
    this->color = Color::UNKNOWN;
}

KNNPoint::KNNPoint(int x, int y, Color color) : x(x), y(y), color(color) {}

auto KNNPoint::getX() -> int { return this->x; }
auto KNNPoint::getY() -> int { return this->y; }
auto KNNPoint::getColor() -> Color { return this->color; }

auto KNNPoint::setColor(Color color) -> void { this->color = color; }

auto KNNPoint::calcDistance(KNNPoint knnPoint) -> double {
  return std::sqrt((this->x - knnPoint.x) * (this->x - knnPoint.x) +
                   (this->y - knnPoint.y) * (this->y - knnPoint.y));
}
