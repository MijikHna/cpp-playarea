#include "../include/XYGraphDrawer.hpp"

#include <iostream>
#include <vector>

using std::cout;
using std::endl;

using std::vector;

XYGraphDrawer::XYGraphDrawer(vector<KNNPoint> knnPoints, int xLen, int yLen)
    : xLength(xLen), yLength(yLen) {
  // TODO: check if x/yLen at least 10
  this->xStepUnits = xLen / 10;
  this->yStepUnits = yLen / 10;

  this->xy = new char *[10];

  for (int i = 0, yAxisI = 0; yAxisI < yLen; yAxisI += this->yStepUnits, i++) {
    this->xy[i] = new char[10];
    for (int j = 0, xAxisI = 0; xAxisI < xLen;
         xAxisI += this->xStepUnits, j++) {
      KNNPoint *foundedKNNPoint = nullptr;

      for (KNNPoint knnPoint : knnPoints) {
        if (knnPoint.getX() >= i * this->xStepUnits &&
            knnPoint.getX() < (i + 1) * this->xStepUnits &&
            knnPoint.getY() >= j * this->yStepUnits &&
            knnPoint.getY() < (j + 1) * this->yStepUnits) {
          foundedKNNPoint = &knnPoint;
          break;
        }
      }

      if (foundedKNNPoint) {
        this->xy[i][j] = static_cast<char>(foundedKNNPoint->getColor());
      } else {
        this->xy[i][j] = '*';
      }
    }
  }
}

XYGraphDrawer::~XYGraphDrawer() {
  for (int i = 0; i < 10; i++) {
    delete this->xy[i];
  }
  delete[] this->xy;
}

void XYGraphDrawer::drawGraph() {
  cout << '^' << endl;

  for (int i = 9; i > 0; i--) {
    cout << '|';
    for (int j = 0; j < 10; j++) {
      cout << this->xy[i][j];
    }
    cout << endl;
  }

  cout << 0;

  for (int i = 0; i < 10; i++) {
    cout << '-';
  }
  cout << '>' << endl;
}
