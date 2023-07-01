#ifndef __VERTEX_GRAPH_DRAWER__
#define __VERTEX_GRAPH_DRAWER__

#include <algorithm>
#include <array>
#include <fstream>
#include <functional>
#include <map>
#include <vector>

#include "Vertex.hpp"
#include "VertexWithNeighbors.hpp"

using namespace std;

namespace GraphAlgo {

  class VertexGraphDrawer {
  public:
    enum class DIRECTION {
      UP,                // DONE
      UP_LEFT,           // DONE
      UP_LEFT_DOUBLE,    // DONE
      UP_RIGHT,          // DONE
      UP_RIGHT_DOUBLE,   // DONE
      LEFT,              // DONE
      RIGHT,             // DONE
      DOWN,              // DONE
      DOWN_LEFT,         // DONE
      DOWN_LEFT_DOUBLE,  // DONE
      DOWN_RIGHT,        // DONE
      DOWN_RIGHT_DOUBLE, // DONE
      NONE               // DONE
    };

  private:
    vector<VertexWithNeighbors>& vertexes;
    fstream tempFile;
    int columns;
    int lines;

  private:
    auto drawConnector(int weight, int currentCursorPos, DIRECTION direction, bool withDirection = false) -> void;
    auto calcConnectionDirection(const Vertex& vertex, const Vertex& neighborVertex, vector<int> graphOrder, bool withDirection = false) -> DIRECTION;
    auto calcOutsideInsideIndexesAndRowLength(const Vertex& vertex, vector<int>& graphOrder) -> map<string, int>;

  public:
    VertexGraphDrawer(vector<VertexWithNeighbors>& vertexes);

    VertexGraphDrawer(VertexGraphDrawer&&) = default;
    VertexGraphDrawer(const VertexGraphDrawer&) = default;
    VertexGraphDrawer& operator=(VertexGraphDrawer&&) = default;
    VertexGraphDrawer& operator=(const VertexGraphDrawer&) = default;
    ~VertexGraphDrawer();

    auto draw(vector<int> graphOrder, bool withDirection = false) -> void;
  };
} // namespace GraphAlgo

#endif // !__VERTEX_GRAPH_DRAWER__
