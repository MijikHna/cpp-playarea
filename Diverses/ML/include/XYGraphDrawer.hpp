#ifndef __XY_GRAPH_DRAWER__
#define __XY_GRAPH_DRAWER__

#include "../include/KNNPoint.hpp"
#include <vector>

using std::vector;

class XYGraphDrawer

{
private:
  char **xy;
  int xLength;
  int yLength;

  int xStepUnits;
  int yStepUnits;

public:
  XYGraphDrawer(vector<KNNPoint> knnPoints, int xLength, int yLenth);
  XYGraphDrawer(XYGraphDrawer &&) = default;
  XYGraphDrawer(const XYGraphDrawer &) = default;
  XYGraphDrawer &operator=(XYGraphDrawer &&) = default;
  XYGraphDrawer &operator=(const XYGraphDrawer &) = default;
  ~XYGraphDrawer();

  auto drawGraph() -> void;
};

#endif // !__XY_GRAPH_DRAWER__
