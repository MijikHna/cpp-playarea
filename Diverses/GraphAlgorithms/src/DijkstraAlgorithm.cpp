#include "../include/DijkstraAlgorithm.hpp"

#include "Vertex.hpp"
#include "VertexNeighbor.hpp"
#include "VertexWithNeighbors.hpp"

#include <algorithm>
#include <limits>
#include <string>
#include <vector>

#include <iostream>

using namespace std;

namespace GraphAlgo {
  DijkstraAlgorithm::DijkstraAlgorithm(vector<VertexWithNeighbors> vertices) : vertices(vertices) {}
  auto DijkstraAlgorithm::runDijkstraAlgorithm(const Vertex* startVertex) -> vector<VertexWithNeighbors> {
    vector<string> unvisitedVertices(this->vertices.size());
    vector<string> visitedVertices;
    vector<VertexNeighbor> calculatedWeightVertices;

    vector<VertexWithNeighbors> result(this->vertices.size());

    transform(
      this->vertices.begin(),
      this->vertices.end(),
      unvisitedVertices.begin(),
      [](VertexWithNeighbors vertex) {
        return vertex.getVertex()->getName();
      });
    transform(
      this->vertices.begin(),
      this->vertices.end(),
      result.begin(),
      [](VertexWithNeighbors vertex) {
        return VertexWithNeighbors(vertex.getVertex());
      });

    // find start vertex index
    auto firstVertex = find_if(
      this->vertices.begin(),
      this->vertices.end(),
      [&startVertex](VertexWithNeighbors& vertex) {
        return vertex.getVertex()->getName().compare(startVertex->getName()) == 0;
      });

    // add start vertex with its neighbors to result
    auto resultVertex = find_if(
      result.begin(),
      result.end(),
      [&startVertex](VertexWithNeighbors& vertex) {
        return vertex.getVertex()->getName().compare(startVertex->getName()) == 0;
      });
    auto firstVertexNeighbors = firstVertex->getNeighbors();
    for_each(
      firstVertexNeighbors.begin(),
      firstVertexNeighbors.end(),
      [&resultVertex](VertexNeighbor& neighbor) {
        resultVertex->addNeighbor(neighbor);
      });

    // add to visitedVertices
    visitedVertices.push_back(firstVertex->getVertex()->getName());
    // add to calculatedWeightVertices with its weight
    calculatedWeightVertices.push_back(VertexNeighbor(firstVertex->getVertex(), 0));

    for_each(
      firstVertexNeighbors.begin(),
      firstVertexNeighbors.end(),
      [&calculatedWeightVertices](VertexNeighbor& neighbor) {
        calculatedWeightVertices.push_back(VertexNeighbor(neighbor.getVertex(), neighbor.getWeight()));
      });

    // remove from unvisitedVertices vector if equals to startVertex
    unvisitedVertices.erase(
      remove_if(
        unvisitedVertices.begin(),
        unvisitedVertices.end(),
        [this, firstVertex](string vertexName) {
          return vertexName.compare(firstVertex->getVertex()->getName()) == 0;
        }),
      unvisitedVertices.end());

    // run trough unvisitedVertices: ACTUALL ALGORITHM
    while (!unvisitedVertices.empty()) {
      auto nextVertexNeighbor = this->selectNextVertexWithMinWeight(calculatedWeightVertices, visitedVertices);

      auto nextVertex = find_if(
        this->vertices.begin(),
        this->vertices.end(),
        [&nextVertexNeighbor](VertexWithNeighbors& vertex) {
          return vertex.getVertex()->getName().compare(nextVertexNeighbor->getVertex()->getName()) == 0;
        });

      // add to visitedVertices
      visitedVertices.push_back(nextVertex->getVertex()->getName());
      // remove from unvisitedVertices
      unvisitedVertices.erase(
        remove_if(
          unvisitedVertices.begin(),
          unvisitedVertices.end(),
          [&nextVertexNeighbor](string vertexName) {
            return vertexName.compare(nextVertexNeighbor->getVertex()->getName()) == 0;
          }),
        unvisitedVertices.end());

      // find vertex in result
      auto vertexResult = find_if(
        result.begin(),
        result.end(),
        [&nextVertexNeighbor](VertexWithNeighbors& vertex) {
          return vertex.getVertex()->getName().compare(nextVertexNeighbor->getVertex()->getName()) == 0;
        });

      // run throw all vertex neighbors
      auto nextVertexNeighbors = nextVertex->getNeighbors();
      for_each(
        nextVertexNeighbors.begin(),
        nextVertexNeighbors.end(),
        [this, &vertexResult, &visitedVertices, &nextVertexNeighbor, &calculatedWeightVertices, &result](VertexNeighbor& vertexNeighbor) {
          // if in visitedVertices continue
          if (
            find_if(
              visitedVertices.begin(),
              visitedVertices.end(),
              [&vertexNeighbor](string vertexName) {
                return vertexName.compare(vertexNeighbor.getVertex()->getName()) == 0;
              }) != visitedVertices.end()) {
            return;
          }

          auto neighborWeight = this->calcWeight(*nextVertexNeighbor, vertexNeighbor);

          // add vertexNeighbor to claculatedWeightVertices if not already in
          if (
            find_if(
              calculatedWeightVertices.begin(),
              calculatedWeightVertices.end(),
              [&vertexNeighbor](VertexNeighbor& calculatedWeightVertex) {
                return calculatedWeightVertex.getVertex()->getName().compare(vertexNeighbor.getVertex()->getName()) == 0;
              }) == calculatedWeightVertices.end()) {
            calculatedWeightVertices.push_back(VertexNeighbor(vertexNeighbor.getVertex(), neighborWeight));
            vertexResult->addNeighbor(vertexNeighbor);
          }
          // if vertexNeighbor in calculatedWeightVertices and weight is smaller than current weight
          else if (
            find_if(
              calculatedWeightVertices.begin(),
              calculatedWeightVertices.end(),
              [&vertexNeighbor, &neighborWeight](VertexNeighbor& vertex) {
                return vertex.getVertex()->getName().compare(vertexNeighbor.getVertex()->getName()) == 0 && vertex.getWeight() > neighborWeight;
              }) != calculatedWeightVertices.end()) {
            // update weight
            auto vertexToUpdate = find_if(
              calculatedWeightVertices.begin(),
              calculatedWeightVertices.end(),
              [&vertexNeighbor](VertexNeighbor& vertex) {
                return vertex.getVertex()->getName().compare(vertexNeighbor.getVertex()->getName()) == 0;
              });
            // run throw neighbors in result and delete vertexNeighbor if eqauls to vertexToUpdate
            this->removeNeighborsFromResult(result, vertexToUpdate->getVertex());

            vertexToUpdate->setWeight(neighborWeight);
            vertexResult->addNeighbor(vertexNeighbor);
          }
        });
    }

    return result;
  }

  auto DijkstraAlgorithm::calcWeight(VertexNeighbor& currentVertex, VertexNeighbor& neighbor) -> int {
    return currentVertex.getWeight() + neighbor.getWeight();
  }

  auto DijkstraAlgorithm::selectNextVertexWithMinWeight(vector<VertexNeighbor>& calculatedWeightVertices, vector<string>& visitedVertices) -> VertexNeighbor* {
    // find Vertex from calculatedWeightVertices with min weight and which name is not in visitedVertices
    VertexNeighbor* minVertex = nullptr;
    int minWeight = std::numeric_limits<int>::max();

    for_each(calculatedWeightVertices.begin() + 1, calculatedWeightVertices.end(), [&visitedVertices, &minVertex, &minWeight](VertexNeighbor& vertex) {
      // if not vertex not in visitedVertices
      if (
        vertex.getWeight() < minWeight &&
        find_if(visitedVertices.begin(), visitedVertices.end(), [&vertex](string vertexName) {
          return vertexName.compare(vertex.getVertex()->getName()) == 0;
        }) == visitedVertices.end()) {
        minVertex = &vertex;
        minWeight = vertex.getWeight();
      }
    });

    return minVertex;
  }

  auto DijkstraAlgorithm::removeNeighborsFromResult(vector<VertexWithNeighbors>& result, Vertex* vertexToRemove) -> void {
    for_each(
      result.begin(),
      result.end(),
      [&vertexToRemove](VertexWithNeighbors& vertex) {
        auto vertexNeighbor = vertex.getNeighbors();
        for_each(
          vertexNeighbor.begin(),
          vertexNeighbor.end(),
          [&vertexToRemove, &vertex](VertexNeighbor& neighbor) {
            if (neighbor.getVertex()->getName().compare(vertexToRemove->getName()) == 0)
              vertex.deleteNeighbor(neighbor.getVertex()->getName());
          });
      });
  }
} // namespace GraphAlgo
