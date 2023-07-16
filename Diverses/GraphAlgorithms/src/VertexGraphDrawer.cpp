#include "../include/VertexGraphDrawer.hpp"
#include "../include/Vertex.hpp"
#include "VertexWithNeighbors.hpp"

#include <algorithm>
#include <cstdio>
#include <fstream>
#include <ios>
#include <iostream>
#include <map>
#include <ostream>
#include <string>
#include <vector>

#define NEXT_HORIZONTAL_CHAR_SPACE 4
#define NEXT_VERTICAL_CHAR_SPACE 3
#define TWO_VERTEXES_SPACE 8

#include <numeric>

using namespace std;

namespace GraphAlgo {
  VertexGraphDrawer::VertexGraphDrawer(vector<VertexWithNeighbors>& vertexes) : vertexes(vertexes) {}

  VertexGraphDrawer::~VertexGraphDrawer() {
    this->tempFile.close();
    remove("./temp-file.txt");
  }

  auto VertexGraphDrawer::draw(vector<int> graphOrder, bool withDirection) -> void {
    // check if drawing the graph is possible
    int totalSize = accumulate(graphOrder.begin(), graphOrder.end(), 0, [](int totalSize, int columnSize) {
      return totalSize += columnSize;
    });

    if (totalSize != this->vertexes.size()) {
      throw "Wrong graphOrder provided";
    }
    // cals rows and columns
    int maxVertexesInTheRow = graphOrder.at(0);
    for_each(graphOrder.begin(), graphOrder.end(), [&maxVertexesInTheRow](const int columnSize) {
      if (maxVertexesInTheRow < columnSize) {
        maxVertexesInTheRow = columnSize;
      }
    });

    this->columns = (maxVertexesInTheRow - 1) * TWO_VERTEXES_SPACE + 1;
    this->lines = (graphOrder.size()) * NEXT_VERTICAL_CHAR_SPACE;

    // create temp file and add for rows and columns space
    ofstream createFile("./temp-file.txt");
    createFile.close();

    this->tempFile.open("./temp-file.txt", ios::in | ios::out);

    this->tempFile.clear();
    this->tempFile.seekp(0);
    this->tempFile.seekg(0);

    for (int i = 0; i < this->lines; i++) {
      string line(this->columns, ' ');
      this->tempFile << line << "\n";
    }

    this->tempFile.clear();
    this->tempFile.seekg(0);

    // start drawing
    int currentPosition = 0;
    this->tempFile.seekp(currentPosition);

    for (int i = 0; i < graphOrder.size(); i++) {
      // calc start of the row
      int startPos = 0;
      int endPos = 0;

      if (graphOrder.at(i) < maxVertexesInTheRow) {
        startPos = endPos = (this->columns - ((graphOrder.at(i) - 1) * TWO_VERTEXES_SPACE)) / 2;
      }
      currentPosition += startPos;
      this->tempFile.seekp(currentPosition);

      // if withDirection false => draw all arrows to bottom (if neighbor is in next Row) and to the right if neighbor index is greater then own index
      int startVectorRow = accumulate(graphOrder.begin(), graphOrder.begin() + i, 0, [](int start, int columnSize) { return start += columnSize - 1; }) + i;
      for (int j = startVectorRow; j < startVectorRow + graphOrder.at(i); j++) {
        this->tempFile << this->vertexes.at(j).getVertex()->getName();

        vector<VertexNeighbor> neighborVert = this->vertexes.at(j).getNeighbors();
        for (int k = 0; k < neighborVert.size(); k++) {
          DIRECTION direction = this->calcConnectionDirection(*this->vertexes.at(j).getVertex(), *neighborVert.at(k).getVertex(), graphOrder, withDirection);
          this->drawConnector(any_cast<int>(neighborVert.at(k).getWeight()), currentPosition, direction, withDirection);
        }
        // go to next vertex
        if (j - startVectorRow < graphOrder.at(i)) {
          currentPosition += TWO_VERTEXES_SPACE;
          this->tempFile.seekp(currentPosition);
        }
      }

      currentPosition += endPos;
      currentPosition += (this->columns) * NEXT_VERTICAL_CHAR_SPACE - NEXT_VERTICAL_CHAR_SPACE * 1; // minus for /n char
      this->tempFile.seekp(currentPosition);
    }

    this->tempFile.seekg(0);
    string line;
    while (getline(tempFile, line)) {
      cout << line << '\n';
    }
    this->tempFile.close();
    remove("./temp-file.txt");
  }

  auto VertexGraphDrawer::drawConnector(int weight, int currentCursorPos, VertexGraphDrawer::DIRECTION direction, bool withDirection) -> void {
    int workingCursorPos = currentCursorPos;

    switch (direction) {
    case DIRECTION::UP:
      if (withDirection) {
        workingCursorPos -= (this->columns + 1);
        this->tempFile.seekp(workingCursorPos);
        this->tempFile << '|';
        workingCursorPos -= (this->columns + 1);
        this->tempFile.seekp(workingCursorPos);
        this->tempFile << weight;
        workingCursorPos -= (this->columns + 1);
        this->tempFile.seekp(workingCursorPos);
        this->tempFile << '^';
      } else {
        workingCursorPos -= (this->columns + 1);
        this->tempFile.seekp(workingCursorPos);
        this->tempFile << '|';
        workingCursorPos -= (this->columns + 1);
        this->tempFile.seekp(workingCursorPos);
        this->tempFile << weight;
        workingCursorPos -= (this->columns + 1);
        this->tempFile.seekp(workingCursorPos);
        this->tempFile << '|';
      }
      break;
    case DIRECTION::UP_DOUBLE:
      if (withDirection) {
        workingCursorPos -= (this->columns + 1);
        this->tempFile.seekp(workingCursorPos);
        this->tempFile << '|';
        workingCursorPos -= (this->columns + 1);
        this->tempFile.seekp(workingCursorPos);
        this->tempFile << '|';
        workingCursorPos -= (this->columns + 1);
        this->tempFile.seekp(workingCursorPos);
        this->tempFile << '|';
        workingCursorPos -= (this->columns + 1);
        this->tempFile.seekp(workingCursorPos);
        this->tempFile << weight;
        workingCursorPos -= (this->columns + 1);
        this->tempFile.seekp(workingCursorPos);
        this->tempFile << "|";
        workingCursorPos -= (this->columns + 1);
        this->tempFile.seekp(workingCursorPos);
        this->tempFile << "|";
        workingCursorPos -= (this->columns + 1);
        this->tempFile.seekp(workingCursorPos);
        this->tempFile << "^";
      } else {
        workingCursorPos -= (this->columns + 1);
        this->tempFile.seekp(workingCursorPos);
        this->tempFile << '|';
        workingCursorPos -= (this->columns + 1);
        this->tempFile.seekp(workingCursorPos);
        this->tempFile << '|';
        workingCursorPos -= (this->columns + 1);
        this->tempFile.seekp(workingCursorPos);
        this->tempFile << '|';
        workingCursorPos -= (this->columns + 1);
        this->tempFile.seekp(workingCursorPos);
        this->tempFile << weight;
        workingCursorPos -= (this->columns + 1);
        this->tempFile.seekp(workingCursorPos);
        this->tempFile << '|';
        workingCursorPos -= (this->columns + 1);
        this->tempFile.seekp(workingCursorPos);
        this->tempFile << '|';
        workingCursorPos -= (this->columns + 1);
        this->tempFile.seekp(workingCursorPos);
        this->tempFile << '|';
      }
      break;
    case DIRECTION::UP_LEFT:
      if (withDirection) {
        workingCursorPos -= (this->columns + 1) + 1;
        this->tempFile.seekp(workingCursorPos);
        this->tempFile << '\\';
        workingCursorPos -= (this->columns + 1) + 1;
        this->tempFile.seekp(workingCursorPos);
        this->tempFile << weight;
        workingCursorPos -= (this->columns + 1) + 1;
        this->tempFile.seekp(workingCursorPos);
        this->tempFile << '^';
      } else {
        workingCursorPos -= (this->columns + 1) + 1;
        this->tempFile.seekp(workingCursorPos);
        this->tempFile << '\\';
        workingCursorPos -= (this->columns + 1) + 1;
        this->tempFile.seekp(workingCursorPos);
        this->tempFile << weight;
        workingCursorPos -= (this->columns + 1) + 1;
        this->tempFile.seekp(workingCursorPos);
        this->tempFile << '\\';
      }
      break;
    case DIRECTION::UP_RIGHT:
      if (withDirection) {
        workingCursorPos -= (this->columns + 1) - 1;
        this->tempFile.seekp(workingCursorPos);
        this->tempFile << '/';
        workingCursorPos -= (this->columns + 1) - 1;
        this->tempFile.seekp(workingCursorPos);
        this->tempFile << weight;
        workingCursorPos -= (this->columns + 1) - 1;
        this->tempFile.seekp(workingCursorPos);
        this->tempFile << '^';
      } else {
        workingCursorPos -= (this->columns + 1) - 1;
        this->tempFile.seekp(workingCursorPos);
        this->tempFile << '/';
        workingCursorPos -= (this->columns + 1) - 1;
        this->tempFile.seekp(workingCursorPos);
        this->tempFile << weight;
        workingCursorPos -= (this->columns + 1) - 1;
        this->tempFile.seekp(workingCursorPos);
        this->tempFile << '/';
      }
      break;
    case DIRECTION::LEFT:
      if (withDirection) {
        workingCursorPos -= 6;
        this->tempFile.seekp(workingCursorPos);
        this->tempFile << "<-";
        this->tempFile << weight;
        this->tempFile << "--";
      } else {
        workingCursorPos -= 5;
        this->tempFile.seekp(workingCursorPos);
        this->tempFile << "--";
        this->tempFile << weight;
        this->tempFile << "--";
      }
      break;
    case DIRECTION::RIGHT:
      if (withDirection) {
        workingCursorPos += 1;
        this->tempFile.seekp(workingCursorPos);
        this->tempFile << " --";
        workingCursorPos += 3;
        this->tempFile.seekp(workingCursorPos);
        this->tempFile << weight;
        workingCursorPos += 1;
        this->tempFile.seekp(workingCursorPos);
        this->tempFile << "-> ";
      } else {
        workingCursorPos += 1;
        this->tempFile.seekp(workingCursorPos);
        this->tempFile << " --";
        workingCursorPos += 3;
        this->tempFile.seekp(workingCursorPos);
        this->tempFile << weight;
        workingCursorPos += 1;
        this->tempFile.seekp(workingCursorPos);
        this->tempFile << "-- ";
      }
      break;
    case DIRECTION::DOWN:
      if (withDirection) {
        workingCursorPos += (this->columns + 1);
        this->tempFile.seekp(workingCursorPos);
        this->tempFile << '|';
        workingCursorPos += (this->columns + 1);
        this->tempFile.seekp(workingCursorPos);
        this->tempFile << weight;
        workingCursorPos += (this->columns + 1);
        this->tempFile.seekp(workingCursorPos);
        this->tempFile << 'v';
      } else {
        workingCursorPos += (this->columns + 1);
        this->tempFile.seekp(workingCursorPos);
        this->tempFile << '|';
        workingCursorPos += (this->columns + 1);
        this->tempFile.seekp(workingCursorPos);
        this->tempFile << weight;
        workingCursorPos += (this->columns + 1);
        this->tempFile.seekp(workingCursorPos);
        this->tempFile << '|';
      }
      break;
    case DIRECTION::DOWN_DOUBLE:
      if (withDirection) {
        workingCursorPos += (this->columns + 1);
        this->tempFile.seekp(workingCursorPos);
        this->tempFile << '|';
        workingCursorPos += (this->columns + 1);
        this->tempFile.seekp(workingCursorPos);
        this->tempFile << '|';
        workingCursorPos += (this->columns + 1);
        this->tempFile.seekp(workingCursorPos);
        this->tempFile << '|';
        workingCursorPos += (this->columns + 1);
        this->tempFile.seekp(workingCursorPos);
        this->tempFile << weight;
        workingCursorPos += (this->columns + 1);
        this->tempFile.seekp(workingCursorPos);
        this->tempFile << '|';
        workingCursorPos += (this->columns + 1);
        this->tempFile.seekp(workingCursorPos);
        this->tempFile << '|';
        workingCursorPos += (this->columns + 1);
        this->tempFile.seekp(workingCursorPos);
        this->tempFile << 'v';
      } else {
        workingCursorPos += (this->columns + 1);
        this->tempFile.seekp(workingCursorPos);
        this->tempFile << '|';
        workingCursorPos += (this->columns + 1);
        this->tempFile.seekp(workingCursorPos);
        this->tempFile << '|';
        workingCursorPos += (this->columns + 1);
        this->tempFile.seekp(workingCursorPos);
        this->tempFile << '|';
        workingCursorPos += (this->columns + 1);
        this->tempFile.seekp(workingCursorPos);
        this->tempFile << weight;
        workingCursorPos += (this->columns + 1);
        this->tempFile.seekp(workingCursorPos);
        this->tempFile << '|';
        workingCursorPos += (this->columns + 1);
        this->tempFile.seekp(workingCursorPos);
        this->tempFile << '|';
        workingCursorPos += (this->columns + 1);
        this->tempFile.seekp(workingCursorPos);
        this->tempFile << '|';
      }
      break;
    case DIRECTION::DOWN_LEFT:
      if (withDirection) {
        workingCursorPos += (this->columns + 1) - 1;
        this->tempFile.seekp(workingCursorPos);
        this->tempFile << '/';
        workingCursorPos += (this->columns + 1) - 1;
        this->tempFile.seekp(workingCursorPos);
        this->tempFile << weight;
        workingCursorPos += (this->columns + 1) - 1;
        this->tempFile.seekp(workingCursorPos);
        this->tempFile << 'v';
      } else {
        workingCursorPos += (this->columns + 1) - 1;
        this->tempFile.seekp(workingCursorPos);
        this->tempFile << '/';
        workingCursorPos += (this->columns + 1) - 1;
        this->tempFile.seekp(workingCursorPos);
        this->tempFile << weight;
        workingCursorPos += (this->columns + 1) - 1;
        this->tempFile.seekp(workingCursorPos);
        this->tempFile << '/';
      }
      break;
    case DIRECTION::DOWN_RIGHT:
      if (withDirection) {
        workingCursorPos += (this->columns + 1) + 1;
        this->tempFile.seekp(workingCursorPos);
        this->tempFile << '\\';
        workingCursorPos += (this->columns + 1) + 1;
        this->tempFile.seekp(workingCursorPos);
        this->tempFile << weight;
        workingCursorPos += (this->columns + 1) + 1;
        this->tempFile.seekp(workingCursorPos);
        this->tempFile << 'v';
      } else {
        workingCursorPos += (this->columns + 1) + 1;
        this->tempFile.seekp(workingCursorPos);
        this->tempFile << '\\';
        workingCursorPos += (this->columns + 1) + 1;
        this->tempFile.seekp(workingCursorPos);
        this->tempFile << weight;
        workingCursorPos += (this->columns + 1) + 1;
        this->tempFile.seekp(workingCursorPos);
        this->tempFile << '\\';
      }
      break;
    case DIRECTION::NONE:
      break;
    default:
      throw "Direction is not specified";
      break;
    }
  }

  auto VertexGraphDrawer::calcConnectionDirection(const Vertex& vertex, const Vertex& vertexNeighbor, vector<int> graphOrder, bool withDirection) -> VertexGraphDrawer::DIRECTION {
    string connectionErrorMessage = "Connection not allowed";
    map<string, int> vertIndexes = this->calcOutsideInsideIndexesAndRowLength(vertex, graphOrder);
    map<string, int> vertNeighIndexes = this->calcOutsideInsideIndexesAndRowLength(vertexNeighbor, graphOrder);

    // vertexOutside < neighborOutside (DOWN)
    //    vertexInside < vertexInside;
    //      length < length; ..LEFT
    //      length == length; ..
    //      length > length; ..RIGHT
    //    vertexInside == vertexInside;
    //      length < length; ..LEFT
    //      length == length; ..
    //      length > length; ..RIGHT
    //    vertexInside > vertexInside; only withDirection
    // vertOutside == neighborOustide (LEFT/RIGHT)
    //
    // vertOutside > neighborOustide (UP)
    //  // check withDirection == true
    // TODO: better diff of the index = -1/0/+1
    if (vertIndexes["outsideIndex"] < vertNeighIndexes["outsideIndex"]) {
      if (vertIndexes["insideIndex"] < vertNeighIndexes["insideIndex"]) {
        if (vertIndexes["length"] < vertNeighIndexes["length"]) {
          return DIRECTION::DOWN_RIGHT;
        } else if (vertIndexes["length"] == vertNeighIndexes["length"]) {
          return DIRECTION::DOWN_RIGHT_DOUBLE;
        }
        throw std::runtime_error(connectionErrorMessage);
      } else if (vertIndexes["insideIndex"] == vertNeighIndexes["insideIndex"]) {
        if (vertIndexes["length"] < vertNeighIndexes["length"]) {
          return DIRECTION::DOWN_LEFT;
        } else if (vertIndexes["length"] == vertNeighIndexes["length"] && vertNeighIndexes["outsideIndex"] - vertIndexes["outsideIndex"] == 1) {
          return DIRECTION::DOWN;
        } else if (vertIndexes["length"] == vertNeighIndexes["length"] && vertNeighIndexes["outsideIndex"] - vertIndexes["outsideIndex"] == 2) {
          return DIRECTION::DOWN_DOUBLE;
        } else if (vertIndexes["length"] > vertNeighIndexes["length"]) {
          return DIRECTION::DOWN_RIGHT;
        }
        throw std::runtime_error(connectionErrorMessage);
      } else if (vertIndexes["insideIndex"] > vertNeighIndexes["insideIndex"]) {
        if (vertIndexes["length"] < vertNeighIndexes["length"]) {
          return DIRECTION::DOWN_RIGHT;
        } else if (vertIndexes["length"] == vertNeighIndexes["length"]) {
          return DIRECTION::DOWN_LEFT_DOUBLE;
        } else if (vertIndexes["length"] > vertNeighIndexes["length"]) {
          return DIRECTION::DOWN_LEFT;
        }

        throw std::runtime_error(connectionErrorMessage);
      }
    } else if (vertIndexes["outsideIndex"] == vertNeighIndexes["outsideIndex"]) {
      if (vertIndexes["insideIndex"] < vertNeighIndexes["insideIndex"]) {
        return DIRECTION::RIGHT;
      } else if (vertIndexes["insideIndex"] > vertNeighIndexes["insideIndex"]) {
        if (!withDirection)
          return DIRECTION::NONE;
        return DIRECTION::LEFT;
      }

      throw std::runtime_error(connectionErrorMessage);
    } else if (vertIndexes["outsideIndex"] > vertNeighIndexes["outsideIndex"]) {
      if (!withDirection)
        return DIRECTION::NONE;

      if (vertIndexes["insideIndex"] < vertNeighIndexes["insideIndex"]) {

        if (vertIndexes["length"] == vertNeighIndexes["length"]) {
          return DIRECTION::UP_LEFT_DOUBLE;
        } else if (vertIndexes["length"] < vertNeighIndexes["length"]) {
          return DIRECTION::UP_RIGHT;
        }
        throw std::runtime_error(connectionErrorMessage);
      } else if (vertIndexes["insideIndex"] == vertNeighIndexes["insideIndex"]) {
        if (vertIndexes["length"] < vertNeighIndexes["length"]) {
          return DIRECTION::UP_LEFT;
        } else if (vertIndexes["length"] == vertNeighIndexes["length"] && vertIndexes["outsideIndex"] - vertNeighIndexes["outsideIndex"] == 1) {
          return DIRECTION::UP;
        } else if (vertIndexes["length"] == vertNeighIndexes["length"] && vertIndexes["outsideIndex"] - vertNeighIndexes["outsideIndex"] == 2) {
          return DIRECTION::UP_DOUBLE;
        } else if (vertIndexes["length"] > vertNeighIndexes["length"]) {
          return DIRECTION::UP_RIGHT;
        }
        throw std::runtime_error(connectionErrorMessage);
      } else if (vertIndexes["insideIndex"] > vertNeighIndexes["insideIndex"]) {
        if (vertIndexes["length"] < vertNeighIndexes["length"]) {
          return DIRECTION::UP_RIGHT;
        } else if (vertIndexes["length"] == vertNeighIndexes["length"]) {
          return DIRECTION::UP_LEFT_DOUBLE;
        } else if (vertIndexes["length"] > vertNeighIndexes["length"]) {
          return DIRECTION::UP_LEFT;
        }
        throw std::runtime_error(connectionErrorMessage);
      }
    }

    cout << "connection no calculated:" << vertex.getName() << " -> " << vertexNeighbor.getName() << endl;
    return DIRECTION::NONE;
  }

  // NOTE: Rethink as the solution approach(data structure of the vertices) has been changed
  auto VertexGraphDrawer::calcOutsideInsideIndexesAndRowLength(const Vertex& vertex, vector<int>& graphOrder) -> map<string, int> {
    for (int i = 0; i < this->vertexes.size(); i++) {
      if (this->vertexes.at(i).getVertex()->getName() == vertex.getName()) {
        int outsideIndex;
        int insideIndex;
        int length;

        int minRange = 0;
        int maxRange = 0;
        for (int j = 0; j < graphOrder.size(); j++) {
          maxRange += graphOrder.at(j);
          if (i >= minRange && i < maxRange) {
            outsideIndex = j;
            insideIndex = i - minRange;
            length = graphOrder.at(j);
          }
          minRange += graphOrder.at(j);
        }

        return {{"outsideIndex", outsideIndex},
                {"insideIndex", insideIndex},
                {"length", length}};
      }
    }
    throw std::runtime_error("No Indexes could be calculated");
  }
} // namespace GraphAlgo
