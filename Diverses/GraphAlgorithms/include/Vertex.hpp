#ifndef __VERTEX__
#define __VERTEX__

#include <any>
#include <functional>
#include <map>
#include <string>
#include <vector>

using namespace ::std;

namespace GraphAlgo {
  class Vertex {

  private:
    string name;

  public:
    Vertex(string name);
    Vertex(Vertex&&) = default;
    Vertex(const Vertex&) = default;
    Vertex& operator=(Vertex&&) = default;
    Vertex& operator=(const Vertex&) = default;
    ~Vertex() = default;

    auto getName() const -> string;
  };
} // namespace GraphAlgo

#endif // __VERTEX__
