#include "graphm.h"

// constructor for graphm class
GraphM::GraphM() {
  size = 0;
  for (int i = 1; i < MAXNODES; i++) {
    for (int j = 1; j < MAXNODES; j++) {
      C[i][j] = INT_MAX;      // infinite
      T[i][j].dist = INT_MAX; // infinite
      T[i][j].path = 0;
      T[i][j].visited = false;
    }
  }
}
// buildgraph function to build the graph
void GraphM::buildGraph(ifstream &infile) {
  infile >> size;
  string line = "";
  getline(infile, line);
  for (int i = 1; i <= size; i++) {
    data[i].setData(infile);
  }
  int n, m, p;
  while (infile >> n >> m >> p) {
    if (n == 0) {
      break;
    }
    C[n][m] = p;
  }
}
// insert an non-existing edge
void GraphM::insertEdge(int fromNode, int toNode, int distance) {
  if (fromNode < 1 || toNode < 1) {
    return;
  }
  if (distance <= 0 || distance == INT_MAX) {
    return;
  }
  if (fromNode > size || toNode > size) {
    return;
  }
  if (fromNode == toNode) {
    return;
  }
  if (C[fromNode][toNode] != INT_MAX) {
    return; // already exist
  }
  C[fromNode][toNode] = distance;
  findShortestPath(); // reset the shortest path
}
// remove an existing edge
void GraphM::removeEdge(int fromNode, int toNode) {
  if (fromNode < 1 || toNode < 1) {
    return;
  }
  if (fromNode > size || toNode > size) {
    return;
  }
  if (fromNode == toNode) {
    return;
  }
  C[fromNode][toNode] = INT_MAX;
  T[fromNode][toNode].visited = false;
  findShortestPath(); // reset the shortest path
}
// find the shortest path for every nodes
void GraphM::findShortestPath() {
  for (int source = 1; source <= size; source++) {
    T[source][source].dist = 0;
    // finds the shortest distance from source to all other nodes
    for (int i = 1; i <= size; i++) {
      int v = -1;
      int min = INT_MAX;
      for (int j = 1; j <= size; j++) {
        if (!T[source][j].visited && T[source][j].dist < min) {
          v = j;
          min = T[source][j].dist;
        }
      }
      T[source][v].visited = true;
      // update distances to all nodes adjacent to v
      for (int w = 1; w <= size; w++) {
        if (!T[source][w].visited && C[v][w] != INT_MAX &&
            T[source][w].dist > T[source][v].dist + C[v][w]) {
          T[source][w].dist = T[source][v].dist + C[v][w];
          T[source][w].path = v;
        }
      }
    }
  }
}
// display all the information
void GraphM::displayAll() const {
  cout << "Description" << setw(20) << "From node" << setw(10) << "To node"
       << setw(14) << "Dijkstra's" << setw(7) << "Path" << endl;
  for (int fromNode = 1; fromNode <= size; fromNode++) {
    cout << data[fromNode] << endl << endl;
    for (int toNode = 1; toNode <= size; toNode++) {
      if (T[fromNode][toNode].dist != 0) {
        cout << setw(27) << fromNode;
        cout << setw(10) << toNode;
        if (T[fromNode][toNode].dist == INT_MAX) {
          cout << setw(12) << "----" << endl;
        } else {
          cout << setw(12) << T[fromNode][toNode].dist;
          cout << setw(10);
          findPath(fromNode, toNode);
          cout << endl;
        }
      }
    }
  }
}
// display the shortest distance with path info between the fromNode to toNode.
void GraphM::display(int fromNode, int toNode) const {
  if (fromNode > size || toNode > size) {
    return;
  }
  if (fromNode < 1 || toNode < 1) {
    return;
  }
  if (fromNode == toNode) {
    return;
  }
  cout << "from: " << fromNode << " to: " << toNode;
  if (T[fromNode][toNode].dist != INT_MAX) {
    cout << " distance: " << T[fromNode][toNode].dist << " path: ";
    findPath(fromNode, toNode);
    cout << endl;
    findName(fromNode, toNode);
    cout << endl;
    cout << endl;
  } else {
    cout << " --- " << endl;
    return;
  }
}
// recursive helper function to get the path
void GraphM::findPath(int fromNode, int toNode) const {
  if (T[fromNode][toNode].dist == INT_MAX) {
    cout << "---" << endl;
    return;
  }
  if (fromNode == toNode) {
    cout << toNode << " ";
    return;
  }
  findPath(fromNode, T[fromNode][toNode].path);
  cout << toNode << " ";
}
// recursive helper function to get the name
void GraphM::findName(int fromNode, int toNode) const {
  if (T[fromNode][toNode].dist == INT_MAX) {
    cout << "---" << endl;
    return;
  }
  if (fromNode == toNode) {
    cout << data[toNode] << endl;
    return;
  }
  findName(fromNode, T[fromNode][toNode].path);
  cout << data[toNode] << endl;
}