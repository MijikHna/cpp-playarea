#include <cstdlib>

#include <iostream>
#include <string>
#include <vector>

#include "./include/PrismAlgorithm.hpp"
#include "./include/Vertex.hpp"
#include "./include/VertexGraphDrawer.hpp"

using namespace std;
using namespace GraphAlgo;

int main(int argc, char* argv[]) {
  Vertex a = Vertex("A");
  VertexWithNeighbors vertexA = VertexWithNeighbors(&a);
  Vertex b = Vertex("B");
  VertexWithNeighbors vertexB = VertexWithNeighbors(&b);
  Vertex c = Vertex("C");
  VertexWithNeighbors vertexC = VertexWithNeighbors(&c);
  Vertex d = Vertex("D");
  VertexWithNeighbors vertexD = VertexWithNeighbors(&d);
  Vertex e = Vertex("E");
  VertexWithNeighbors vertexE = VertexWithNeighbors(&e);
  Vertex f = Vertex("F");
  VertexWithNeighbors vertexF = VertexWithNeighbors(&f);
  Vertex g = Vertex("G");
  VertexWithNeighbors vertexG = VertexWithNeighbors(&g);

  vertexA.addNeighbor(VertexNeighbor(&b, 2));
  vertexA.addNeighbor(VertexNeighbor(&d, 4));
  vertexA.addNeighbor(VertexNeighbor(&c, 1));

  vertexB.addNeighbor(VertexNeighbor(&a, 2));
  vertexB.addNeighbor(VertexNeighbor(&c, 3));
  vertexB.addNeighbor(VertexNeighbor(&e, 7));

  vertexD.addNeighbor(VertexNeighbor(&a, 4));
  vertexD.addNeighbor(VertexNeighbor(&c, 2));
  vertexD.addNeighbor(VertexNeighbor(&f, 6));

  vertexC.addNeighbor(VertexNeighbor(&a, 1));
  vertexC.addNeighbor(VertexNeighbor(&b, 3));
  vertexC.addNeighbor(VertexNeighbor(&d, 2));
  vertexC.addNeighbor(VertexNeighbor(&e, 9));
  vertexC.addNeighbor(VertexNeighbor(&f, 8));
  vertexC.addNeighbor(VertexNeighbor(&g, 4));

  vertexE.addNeighbor(VertexNeighbor(&b, 7));
  vertexE.addNeighbor(VertexNeighbor(&c, 9));
  vertexE.addNeighbor(VertexNeighbor(&g, 3));

  vertexF.addNeighbor(VertexNeighbor(&d, 6));
  vertexF.addNeighbor(VertexNeighbor(&c, 8));
  vertexF.addNeighbor(VertexNeighbor(&g, 1));

  vertexG.addNeighbor(VertexNeighbor(&c, 4));
  vertexG.addNeighbor(VertexNeighbor(&e, 3));
  vertexG.addNeighbor(VertexNeighbor(&f, 1));

  vector<VertexWithNeighbors> vertexes = {vertexA, vertexB, vertexD, vertexC, vertexE, vertexF, vertexG};
  vector<int> graphOrder {2, 3, 2};

  VertexGraphDrawer vertexGraphDrawer(vertexes);
  vertexGraphDrawer.draw(graphOrder);

  PrismAlgorithm PrismAlgorithm(vertexes);
  vector<VertexWithNeighbors> newVertices = PrismAlgorithm.runPrismAlgorithm(vertexC.getVertex());

  cout << endl
       << endl
       << "Prism Algorithm" << endl
       << endl;

  VertexGraphDrawer vertexGraphDrawerAfter(newVertices);
  vertexGraphDrawerAfter.draw(graphOrder, true);

  return EXIT_SUCCESS;
}
