#include "../include/Vertex.hpp"
#include "../include/VertexWithNeighbors.hpp"

#ifndef __PRISM_ALGORITHM__
#define __PRISM_ALGORITHM__

namespace GraphAlgo {
  class PrismAlgorithm {
  private:
    vector<VertexWithNeighbors> vertexes;

  private:
    auto findMinWeight(vector<VertexWithNeighbors>& vertices) -> pair<Vertex*, VertexNeighbor*>;
    auto checkIfFinished(vector<bool> mapSpanTreeTracker) -> bool;

  public:
    PrismAlgorithm(vector<VertexWithNeighbors> vertexes);
    PrismAlgorithm(PrismAlgorithm&&) = default;
    PrismAlgorithm(const PrismAlgorithm&) = default;
    PrismAlgorithm& operator=(PrismAlgorithm&&) = default;
    PrismAlgorithm& operator=(const PrismAlgorithm&) = default;
    ~PrismAlgorithm() = default;

    auto runPrismAlgorithm(const Vertex* sartVertex) -> vector<VertexWithNeighbors>;
  };
} // namespace GraphAlgo
#endif // !__PRISM_ALGORITHM__
