#include "VertexWithNeighbors.hpp"
#include "Vertex.hpp"
#include "VertexNeighbor.hpp"

#include <iostream>
#include <vector>

using namespace std;

namespace GraphAlgo {
  VertexWithNeighbors::VertexWithNeighbors(Vertex* vertex) : vertex(vertex) {
    this->neighbors = vector<VertexNeighbor>();
  }

  auto VertexWithNeighbors::getVertex() -> Vertex* {
    return this->vertex;
  }

  auto VertexWithNeighbors::getNeighbors() -> vector<VertexNeighbor> {
    return this->neighbors;
  }

  auto VertexWithNeighbors::addNeighbor(VertexNeighbor vertexNeighbor) -> void {
    this->neighbors.push_back(vertexNeighbor);
  }

  auto VertexWithNeighbors::deleteNeighbor(string name) -> void {
    vector<VertexNeighbor>::iterator neighborFound = find_if(this->neighbors.begin(), this->neighbors.end(), [name](VertexNeighbor neighbor) {
      return neighbor.getVertex()->getName().compare(name) == 0;
    });

    if (neighborFound != this->neighbors.end()) {
      this->neighbors.erase(neighborFound);
    }
  }
} // namespace GraphAlgo
