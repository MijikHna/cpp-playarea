#include "../include/VertexNeighbor.hpp"

namespace GraphAlgo {
  VertexNeighbor::VertexNeighbor() {}

  VertexNeighbor::VertexNeighbor(Vertex* vertex, int weight) : vertex(vertex), weight(weight) {}

  // move
  VertexNeighbor::VertexNeighbor(VertexNeighbor&& vertexMove) : vertex(std::move(vertexMove.vertex)), weight(std::move(vertexMove.weight)) {}

  VertexNeighbor::VertexNeighbor(const VertexNeighbor& vertexCopy) : vertex(vertexCopy.vertex), weight(vertexCopy.weight) {
  }
  // move
  VertexNeighbor& VertexNeighbor::operator=(VertexNeighbor&& vertexMove) {
    this->vertex = std::move(vertexMove.vertex);
    this->weight = std::move(vertexMove.weight);
    return *this;
  }
  // copy
  VertexNeighbor& VertexNeighbor::operator=(const VertexNeighbor& vertexMove) {
    this->vertex = vertexMove.vertex;
    this->weight = vertexMove.weight;
    return *this;
  }

  auto VertexNeighbor::getVertex() -> Vertex* { return this->vertex; }
  auto VertexNeighbor::getWeight() -> int { return this->weight; }

  auto VertexNeighbor::setWeight(int weight) -> void { this->weight = weight; }
} // namespace GraphAlgo
