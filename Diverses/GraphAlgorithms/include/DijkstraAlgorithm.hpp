#include "../include/Vertex.hpp"
#include "../include/VertexWithNeighbors.hpp"
#include <string>
#include <vector>

#ifndef __DIJSTRA_ALGORITHM__
#define __DIJKSTRA_ALGORITHM__

namespace GraphAlgo {
  class DijkstraAlgorithm {
  private:
    vector<VertexWithNeighbors> vertices;

  private:
    auto calcWeight(VertexNeighbor& currentVertex, VertexNeighbor& neighbor) -> int;

  private:
    auto selectNextVertexWithMinWeight(vector<VertexNeighbor>& calculatedWeight, vector<string>& visitedVertices) -> VertexNeighbor*;
    auto removeNeighborsFromResult(vector<VertexWithNeighbors>& resultVertices, Vertex* vertex) -> void;

  public:
    DijkstraAlgorithm(vector<VertexWithNeighbors> vertices);
    DijkstraAlgorithm(DijkstraAlgorithm&&) = default;
    DijkstraAlgorithm(const DijkstraAlgorithm&) = default;
    DijkstraAlgorithm& operator=(DijkstraAlgorithm&&) = default;
    DijkstraAlgorithm& operator=(const DijkstraAlgorithm&) = default;
    ~DijkstraAlgorithm() = default;

    auto runDijkstraAlgorithm(const Vertex* startVertx) -> vector<VertexWithNeighbors>;
  };
} // namespace GraphAlgo
#endif // !__DIJKSTRA_ALGORITHM__
