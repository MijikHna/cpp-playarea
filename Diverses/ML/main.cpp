#include "include/ColorEnum.hpp"
#include "include/KNNPoint.hpp"
#include "include/XYGraphDrawer.hpp"

#include <iostream>
#include <stdlib.h>
#include <vector>

int main(int argc, char *argv[]) {
  std::vector<KNNPoint> knnPoints = {
      KNNPoint(40, 20, Color::RED),  KNNPoint(50, 50, Color::BLUE),
      KNNPoint(60, 90, Color::BLUE), KNNPoint(10, 25, Color::RED),
      KNNPoint(70, 70, Color::BLUE), KNNPoint(60, 10, Color::RED),
      KNNPoint(25, 80, Color::BLUE),
  };

  XYGraphDrawer xyGraphDrawer1(knnPoints, 100, 100);
  xyGraphDrawer1.drawGraph();

  KNNPoint *newKnnPoint = new KNNPoint(20, 35, Color::UNKNOWN);

  std::vector<KNNPoint> top5KnnPoints{};
  std::vector<double> top5Distances{};

  for (KNNPoint knnPoint : knnPoints) {
    bool inserted = false;
    double knnDistance = newKnnPoint->calcDistance(knnPoint);

    vector<KNNPoint>::iterator itTop5KnnPoints = top5KnnPoints.begin();
    vector<double>::iterator itTop5Distances = top5Distances.begin();

    for (int i = 0; i < top5Distances.size(); i++) {
      if (knnDistance < top5Distances.at(i)) {
        if (top5Distances.size() >= 5) {
          top5KnnPoints.pop_back();
          top5Distances.pop_back();
        }
        top5KnnPoints.insert(itTop5KnnPoints + i, knnPoint);
        top5Distances.insert(itTop5Distances + i, knnDistance);

        inserted = true;
        break;
      }
    }

    if (!inserted && top5KnnPoints.size() < 5) {
      top5Distances.push_back(knnDistance);
      top5KnnPoints.push_back(knnPoint);
    }
  }

  knnPoints.push_back(*newKnnPoint);
  newKnnPoint = &knnPoints.at(knnPoints.size() - 1);
  XYGraphDrawer xyGraphDrawer2(knnPoints, 100, 100);
  xyGraphDrawer2.drawGraph();

  int countBlue = 0;
  int countRed = 0;
  for (KNNPoint knnPoint : top5KnnPoints) {
    if (knnPoint.getColor() == Color::BLUE)
      countBlue++;
    if (knnPoint.getColor() == Color::RED)
      countRed++;
  }

  if (countBlue > countRed)
    newKnnPoint->setColor(Color::BLUE);
  else
    newKnnPoint->setColor(Color::RED);

  XYGraphDrawer xyGraphDrawer3(knnPoints, 100, 100);
  xyGraphDrawer3.drawGraph();

  return EXIT_SUCCESS;
}
