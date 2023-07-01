#ifndef __VERTEX_NEIGHBOR__
#define __VERTEX_NEIGHBOR__

#include "Vertex.hpp"

namespace GraphAlgo {

  class VertexNeighbor {
  private:
    int weight;
    Vertex* vertex;

  public:
    VertexNeighbor(Vertex* vertex, int weight);
    VertexNeighbor(VertexNeighbor&&);                 // move-constructor
    VertexNeighbor(const VertexNeighbor&);            // copy constructor
    VertexNeighbor& operator=(VertexNeighbor&&);      // move
    VertexNeighbor& operator=(const VertexNeighbor&); // copy
    ~VertexNeighbor() = default;

    auto getVertex() -> Vertex*;
    auto getWeight() -> int;
  };
} // namespace GraphAlgo
#endif // !__VERTEX_NEIGHBOR__
       //
