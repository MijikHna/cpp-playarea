#include "../include/Vertex.hpp"

#include <algorithm>
#include <any>
#include <map>
#include <string>
#include <vector>

using namespace std;

namespace GraphAlgo {
  Vertex::Vertex(string name) : name(name) {}

  /* Vertex::Vertex(const Vertex& vertex) { */
  /*   this->name = vertex.name; */
  /*   this->neighbors = vector<map<string, any>>(); */
  /* } */

  auto Vertex::getName() const -> string {
    return this->name;
  }

} // namespace GraphAlgo
