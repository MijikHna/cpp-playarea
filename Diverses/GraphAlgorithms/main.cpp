#include <cstdlib>

#include <iostream>
#include <string>
#include <vector>

#include "./include/Vertex.hpp"
#include "./include/VertexGraphDrawer.hpp"

#include "./include/DijkstraAlgorithm.hpp"
#include "./include/PrismAlgorithm.hpp"

using namespace std;
using namespace GraphAlgo;

int main(int argc, char* argv[]) {

  Vertex aPrism = Vertex("A");
  VertexWithNeighbors vertexAPrism = VertexWithNeighbors(&aPrism);
  Vertex bPrism = Vertex("B");
  VertexWithNeighbors vertexBPrism = VertexWithNeighbors(&bPrism);
  Vertex cPrism = Vertex("C");
  VertexWithNeighbors vertexCPrism = VertexWithNeighbors(&cPrism);
  Vertex dPrism = Vertex("D");
  VertexWithNeighbors vertexDPrism = VertexWithNeighbors(&dPrism);
  Vertex ePrism = Vertex("E");
  VertexWithNeighbors vertexEPrism = VertexWithNeighbors(&ePrism);
  Vertex fPrism = Vertex("F");
  VertexWithNeighbors vertexFPrism = VertexWithNeighbors(&fPrism);
  Vertex gPrism = Vertex("G");
  VertexWithNeighbors vertexGPrism = VertexWithNeighbors(&gPrism);

  vertexAPrism.addNeighbor(VertexNeighbor(&bPrism, 2));
  vertexAPrism.addNeighbor(VertexNeighbor(&dPrism, 4));
  vertexAPrism.addNeighbor(VertexNeighbor(&cPrism, 1));

  vertexBPrism.addNeighbor(VertexNeighbor(&aPrism, 2));
  vertexBPrism.addNeighbor(VertexNeighbor(&cPrism, 3));
  vertexBPrism.addNeighbor(VertexNeighbor(&ePrism, 7));

  vertexDPrism.addNeighbor(VertexNeighbor(&aPrism, 4));
  vertexDPrism.addNeighbor(VertexNeighbor(&cPrism, 2));
  vertexDPrism.addNeighbor(VertexNeighbor(&fPrism, 6));

  vertexCPrism.addNeighbor(VertexNeighbor(&aPrism, 1));
  vertexCPrism.addNeighbor(VertexNeighbor(&bPrism, 3));
  vertexCPrism.addNeighbor(VertexNeighbor(&dPrism, 2));
  vertexCPrism.addNeighbor(VertexNeighbor(&ePrism, 9));
  vertexCPrism.addNeighbor(VertexNeighbor(&fPrism, 8));
  vertexCPrism.addNeighbor(VertexNeighbor(&gPrism, 4));

  vertexEPrism.addNeighbor(VertexNeighbor(&bPrism, 7));
  vertexEPrism.addNeighbor(VertexNeighbor(&cPrism, 9));
  vertexEPrism.addNeighbor(VertexNeighbor(&gPrism, 3));

  vertexFPrism.addNeighbor(VertexNeighbor(&dPrism, 6));
  vertexFPrism.addNeighbor(VertexNeighbor(&cPrism, 8));
  vertexFPrism.addNeighbor(VertexNeighbor(&gPrism, 1));

  vertexGPrism.addNeighbor(VertexNeighbor(&cPrism, 4));
  vertexGPrism.addNeighbor(VertexNeighbor(&ePrism, 3));
  vertexGPrism.addNeighbor(VertexNeighbor(&fPrism, 1));

  vector<VertexWithNeighbors> verticesPrism = {vertexAPrism, vertexBPrism, vertexDPrism, vertexCPrism, vertexEPrism, vertexFPrism, vertexGPrism};

  vector<int> graphOrder {2, 3, 2};
  VertexGraphDrawer vertexGraphDrawer(verticesPrism);
  vertexGraphDrawer.draw(graphOrder);

  PrismAlgorithm prismAlgorithm(verticesPrism);
  vector<VertexWithNeighbors> verticesPrismProcessed = prismAlgorithm.runPrismAlgorithm(vertexCPrism.getVertex());

  cout << endl
       << endl
       << "Prism Algorithm" << endl
       << endl;

  VertexGraphDrawer vertexGraphDrawerAfter(verticesPrismProcessed);
  vertexGraphDrawerAfter.draw(graphOrder, true);

  cout << endl
       << endl;

  Vertex aDijkstra = Vertex("A");
  VertexWithNeighbors vertexADijkstra = VertexWithNeighbors(&aDijkstra);
  Vertex bDijkstra = Vertex("B");
  VertexWithNeighbors vertexBDijkstra = VertexWithNeighbors(&bDijkstra);
  Vertex cDijkstra = Vertex("C");
  VertexWithNeighbors vertexCDijkstra = VertexWithNeighbors(&cDijkstra);
  Vertex dDijkstra = Vertex("D");
  VertexWithNeighbors vertexDDijkstra = VertexWithNeighbors(&dDijkstra);
  Vertex eDijkstra = Vertex("E");
  VertexWithNeighbors vertexEDijkstra = VertexWithNeighbors(&eDijkstra);

  vertexADijkstra.addNeighbor(VertexNeighbor(&bDijkstra, 6));
  vertexADijkstra.addNeighbor(VertexNeighbor(&cDijkstra, 2));

  vertexBDijkstra.addNeighbor(VertexNeighbor(&aDijkstra, 6));
  vertexBDijkstra.addNeighbor(VertexNeighbor(&cDijkstra, 1));
  vertexBDijkstra.addNeighbor(VertexNeighbor(&dDijkstra, 3));
  vertexBDijkstra.addNeighbor(VertexNeighbor(&eDijkstra, 2));

  vertexCDijkstra.addNeighbor(VertexNeighbor(&aDijkstra, 2));
  vertexCDijkstra.addNeighbor(VertexNeighbor(&bDijkstra, 1));

  vertexDDijkstra.addNeighbor(VertexNeighbor(&bDijkstra, 3));
  vertexDDijkstra.addNeighbor(VertexNeighbor(&eDijkstra, 5));

  vertexEDijkstra.addNeighbor(VertexNeighbor(&bDijkstra, 2));
  vertexEDijkstra.addNeighbor(VertexNeighbor(&dDijkstra, 5));

  vector<VertexWithNeighbors> verticesDijkstra = {vertexADijkstra, vertexDDijkstra, vertexBDijkstra, vertexCDijkstra, vertexEDijkstra};

  vector<int> graphOrderDijkstra {2, 1, 2};
  VertexGraphDrawer vertexGraphDrawerDijkstra(verticesDijkstra);
  vertexGraphDrawerDijkstra.draw(graphOrderDijkstra);

  DijkstraAlgorithm dijkstraAlgorithm(verticesDijkstra);
  vector<VertexWithNeighbors> verticesDijkstraProcessed = dijkstraAlgorithm.runDijkstraAlgorithm(vertexADijkstra.getVertex());

  cout << endl
       << endl
       << "Dijkstra Algorithm" << endl
       << endl;
  VertexGraphDrawer vertexGraphDrawerAfterDijkstra(verticesDijkstraProcessed);
  vertexGraphDrawerAfterDijkstra.draw(graphOrderDijkstra, true);

  DijkstraAlgorithm dijkstraAlgorithm2(verticesPrism);
  auto verticesDijkstraProcessed2 = dijkstraAlgorithm2.runDijkstraAlgorithm(vertexAPrism.getVertex());

  cout << endl;

  VertexGraphDrawer vertexGraphDrawerAfterDijkstra2(verticesDijkstraProcessed2);
  vertexGraphDrawerAfterDijkstra2.draw(graphOrder, true);

  return EXIT_SUCCESS;
}
