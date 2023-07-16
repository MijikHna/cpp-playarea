#ifndef __VERTEX_WITH_NEIGHBORS__
#define __VERTEX_WITH_NEIGHBORS__

#include "Vertex.hpp"
#include "VertexNeighbor.hpp"

namespace GraphAlgo {
  class VertexWithNeighbors {
  private:
    Vertex* vertex;
    vector<VertexNeighbor> neighbors;

  public:
    VertexWithNeighbors();
    VertexWithNeighbors(Vertex* vertex);
    VertexWithNeighbors(VertexWithNeighbors&&) = default;
    VertexWithNeighbors(const VertexWithNeighbors&) = default;
    VertexWithNeighbors& operator=(VertexWithNeighbors&&) = default;
    VertexWithNeighbors& operator=(const VertexWithNeighbors&) = default;
    ~VertexWithNeighbors() = default;

    auto getVertex() -> Vertex*;
    auto getNeighbors() -> vector<VertexNeighbor>;
    auto addNeighbor(VertexNeighbor) -> void;
    auto deleteNeighbor(string name) -> void;
  };
} // namespace GraphAlgo

#endif // !__VERTEX_WITH_NEIGHBORS__
