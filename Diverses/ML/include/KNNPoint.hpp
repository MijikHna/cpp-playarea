#ifndef __KNN_PIONT__
#define __KNN_PIONT__

#include "ColorEnum.hpp"
#include <utility>

class KNNPoint {

private:
  int x;
  int y;
  Color color;

public:
  KNNPoint(int x, int y);
  KNNPoint(int x, int y, Color color);
  KNNPoint(KNNPoint &&) = default;
  KNNPoint(const KNNPoint &) = default;
  KNNPoint &operator=(KNNPoint &&) = default;
  KNNPoint &operator=(const KNNPoint &) = default;
  ~KNNPoint() = default;

  int getX();
  int getY();
  Color getColor();

  auto setColor(Color color) -> void;

  auto calcDistance(KNNPoint knnPoint) -> double;
};
#endif // !__KNN_PIONT__
#define __KNN_PIONT__
