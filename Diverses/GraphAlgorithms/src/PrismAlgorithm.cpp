#include "../include/PrismAlgorithm.hpp"
#include "../include/Vertex.hpp"
#include "../include/VertexNeighbor.hpp"
#include "../include/VertexWithNeighbors.hpp"

#include <algorithm>
#include <any>
#include <iostream>
#include <limits>
#include <map>
#include <numeric>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

namespace GraphAlgo {
  using namespace std;
  PrismAlgorithm::PrismAlgorithm(vector<VertexWithNeighbors> vertexes) : vertexes(vertexes) {}

  auto PrismAlgorithm::runPrismAlgorithm(const Vertex* startVertex) -> vector<VertexWithNeighbors> {
    // copy vertexes without its neighbors
    vector<VertexWithNeighbors> minSpanningTree;
    for_each(this->vertexes.begin(), this->vertexes.end(), [startVertex, &minSpanningTree](VertexWithNeighbors vertexWithNeighbors) {
      Vertex* vertex = new Vertex(vertexWithNeighbors.getVertex()->getName());
      VertexWithNeighbors* vertexWithNeighb = new VertexWithNeighbors(vertex);
      minSpanningTree.push_back(*vertexWithNeighb);
    });

    vector<bool> minSpanTreeTracker = vector<bool>(this->vertexes.size());
    transform(minSpanningTree.begin(), minSpanningTree.end(), minSpanTreeTracker.begin(), [startVertex](VertexWithNeighbors& vertexWithNeighbors) {
      if (vertexWithNeighbors.getVertex()->getName().compare(startVertex->getName()) == 0) {
        return true;
      }
      return false;
    });

    // delete first Vertex
    for_each(this->vertexes.begin(), this->vertexes.end(), [startVertex](VertexWithNeighbors& vertexWithNeighbors) {
      vertexWithNeighbors.deleteNeighbor(startVertex->getName());
    });

    // run through vertex neighbors lowest neighbor => neighbor -> vertex = add to mapTree
    // if start node skip
    while (!this->checkIfFinished(minSpanTreeTracker)) {
      // get possible vertices
      vector<VertexWithNeighbors> possibleNext;
      for (int i = 0; i < minSpanTreeTracker.size(); i++) {
        if (minSpanTreeTracker.at(i)) {
          possibleNext.push_back(this->vertexes.at(i));
        }
      }

      // call findMin
      pair<Vertex*, VertexNeighbor*> minVertexAndNeighbor = this->findMinWeight(possibleNext);
      if (minVertexAndNeighbor.first == nullptr) {
        throw runtime_error("No connections found");
      }

      // delete Neighbors, update Tracker, add neighbor to parent in minSpanningTree
      for_each(this->vertexes.begin(), this->vertexes.end(), [minVertexAndNeighbor](VertexWithNeighbors& vertex) {
        vertex.deleteNeighbor(minVertexAndNeighbor.second->getVertex()->getName());
      });

      // update Tracker NOTE: eventually replace with simple loop
      for (int i = 0; i < minSpanTreeTracker.size(); i++) {
        Vertex* neighbor = minVertexAndNeighbor.second->getVertex();
        if (this->vertexes.at(i).getVertex()->getName().compare(neighbor->getName()) == 0) {
          minSpanTreeTracker.at(i) = true;
        }
      }

      for_each(minSpanningTree.begin(), minSpanningTree.end(), [minVertexAndNeighbor](VertexWithNeighbors& vertexWithNeighbors) {
        Vertex parent = *(minVertexAndNeighbor.first);
        Vertex* neighbor = minVertexAndNeighbor.second->getVertex();
        int weight = minVertexAndNeighbor.second->getWeight();
        // NOTE: eventually override compare operator
        if (vertexWithNeighbors.getVertex()->getName().compare(parent.getName()) == 0) {
          vertexWithNeighbors.addNeighbor(*minVertexAndNeighbor.second);
        }
      });
    }
    return minSpanningTree;
  }

  auto PrismAlgorithm::findMinWeight(vector<VertexWithNeighbors>& vertices) -> pair<Vertex*, VertexNeighbor*> {
    int minWeight = numeric_limits<int>::max();
    Vertex* resultVertex = nullptr;
    VertexNeighbor* resultNeighbor = nullptr;
    for (int i = 0; i < vertices.size(); i++) {
      vector<VertexNeighbor> neighbors = vertices.at(i).getNeighbors();

      for (int j = 0; j < neighbors.size(); j++) {
        int neighborWeight = neighbors.at(j).getWeight();
        Vertex* neighborVertex = neighbors.at(j).getVertex();

        if (neighborWeight < minWeight) {
          minWeight = neighborWeight;
          resultVertex = vertices.at(i).getVertex();
          resultNeighbor = new VertexNeighbor(neighbors.at(j).getVertex(), neighbors.at(j).getWeight());
        }
      }
    }

    return pair<Vertex*, VertexNeighbor*>(resultVertex, resultNeighbor);
  }

  auto PrismAlgorithm::checkIfFinished(vector<bool> mapSpanTreeTracker) -> bool {
    return accumulate(mapSpanTreeTracker.begin(), mapSpanTreeTracker.end(), true, [](bool check, const bool& vertexCheck) {
      if (check == false) {
        return check;
      }
      if (!vertexCheck) {
        check = false;
      }
      return check;
    });
  }

} // namespace GraphAlgo
