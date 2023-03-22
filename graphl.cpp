#include "graphl.h"
// constructor for graphl class
GraphL::GraphL() {
  size = 0;
  for (int i = 1; i < MAXNODES; i++) {
    graphArr[i].visited = false;
    graphArr[i].edgeHead = NULL;
    graphArr[i].data = NULL;
  }
}
// destructor for graphl class
GraphL::~GraphL() {
  for (int i = 1; i <= size; i++) {
    EdgeNode *current = graphArr[i].edgeHead;
    while (current != nullptr) {
      EdgeNode *temp = current;
      current = current->nextEdge;
      delete temp;
    }
    delete graphArr[i].data;
  }
}
// build graph function to build the graph
void GraphL::buildGraph(ifstream &infile) {
  infile >> size;
  string line = "";
  getline(infile, line);
  for (int i = 1; i <= size; i++) {
    getline(infile, line);
    NodeData *tmp = new NodeData(line);
    graphArr[i].data = tmp;
  }
  int n, m;
  while (infile >> n >> m) {
    if (n == 0) {
      break;
    }
    if (graphArr[n].edgeHead == NULL) {
      EdgeNode *node = new EdgeNode;
      node->adjGraphNode = m;
      graphArr[n].edgeHead = node;
      graphArr[n].edgeHead->nextEdge = NULL;
    } else {
      EdgeNode *node = new EdgeNode;
      node->adjGraphNode = m;
      node->nextEdge = graphArr[n].edgeHead;
      graphArr[n].edgeHead = node;
    }
  }
}
// displays each node information and edge in the graph
void GraphL::displayGraph() {
  cout << "Graph:" << endl;
  for (int i = 1; i <= size; i++) {
    cout << "Node " << i << " " << *graphArr[i].data << endl;
    EdgeNode *temp = graphArr[i].edgeHead;
    while (temp != NULL) {
      cout << "   Edge " << i << " " << temp->adjGraphNode << endl;
      temp = temp->nextEdge;
    }
  }
}
// makes a depth-first search and displays each node in depth-first order
void GraphL::depthFirstSearch() {
  cout << "DFS order:";
  for (int i = 1; i <= size; i++) {
    if (!graphArr[i].visited) {
      depthFirstSearchHelper(i);
    }
  }
  cout << endl;
}
// helper function for dfs
void GraphL::depthFirstSearchHelper(int current) {
  cout << " " << current;
  graphArr[current].visited = true;
  EdgeNode *temp = graphArr[current].edgeHead;
  while (temp != NULL) {
    if (!graphArr[temp->adjGraphNode].visited) {
      depthFirstSearchHelper(temp->adjGraphNode);
    } else {
      temp = temp->nextEdge;
    }
  }
}