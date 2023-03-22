#include "nodedata.h"
#include <fstream>
#include <iomanip>
#include <iostream>

using namespace std;

int const MAXNODES = 100;

class GraphL {
public:
  GraphL();
  ~GraphL();
  void buildGraph(ifstream &infile);
  void displayGraph();
  void depthFirstSearch();

private:
  struct EdgeNode;

  struct GraphNode {
    EdgeNode *edgeHead;
    NodeData *data;
    bool visited;
  };
  GraphNode graphArr[MAXNODES];
  struct EdgeNode {
    int adjGraphNode;
    EdgeNode *nextEdge;
  };

  GraphNode graphNodes[MAXNODES];
  int size;
  void depthFirstSearchHelper(int current);
};