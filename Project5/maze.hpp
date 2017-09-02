#ifndef maze_hpp
#define maze_hpp

#include <stdio.h>
#include <iostream>
#include <limits.h>
#include <list>
#include <fstream>
#include <queue>
#include <vector>
#include <stack>
#include <boost/graph/adjacency_list.hpp>
#include "boost/graph/directed_graph.hpp"
#include "boost/graph/undirected_graph.hpp"
#include "d_except.h"
#include "d_matrix.h"

#define LargeValue 99999999

using namespace std;
using namespace boost;

struct VertexProperties;
struct EdgeProperties;

typedef adjacency_list<vecS, vecS, bidirectionalS, VertexProperties, EdgeProperties, property<vertex_index_t, int>> Graph;

struct VertexProperties
{
    pair<int,int> cell; // maze cell (x,y) value
    Graph::vertex_descriptor pred; // predecessor node
    int weight;
    bool visited;
    bool marked;
    
};

// Create a struct to hold properties for each edge
struct EdgeProperties
{
    int weight;
    bool visited;
    bool marked;
};

// typedef property<edge_weight_t, int> EdgeProperty;

class maze
{
public:
    maze(ifstream &fin);
    void print(int,int,int,int);
    bool isLegal(int i, int j);
    void mapMazeToGraph(Graph &g);
    void printPath(stack<Graph::vertex_descriptor> &s, Graph g);
    int numRows(){return rows;};
    int numCols(){return cols;};
    void clearVisited(Graph &g);
    // Mark all nodes in g as not visited.
    
    void setNodeWeights(Graph &g, int w);
    // Set all node weights to w.
    
    void clearMarked(Graph &g);
//    friend ostream& operator<<(std::ostream& os, const Graph &g);
    bool FindPathDFSRecursive(Graph &g, Graph::vertex_descriptor v, pair<int,int> goal, stack<Graph::vertex_descriptor> &vstack);
    void test(Graph &g, Graph::vertex_descriptor v);
    void FindSHortestPathDFS(Graph &g, Graph::vertex_descriptor v, pair<int,int> goal, stack<Graph::vertex_descriptor> &vstack, vector<Graph::vertex_descriptor> &shrtstckvector, stack<Graph::vertex_descriptor> &shortstack);
    void FindPthDFSStack(Graph &g, Graph::vertex_descriptor v, pair<int,int> goal, stack<Graph::vertex_descriptor> &vstack);
    void FindShortestPathBFS(Graph &g, Graph::vertex_descriptor v, pair<int,int> goal, queue<Graph::vertex_descriptor> &vqueue, stack<Graph::vertex_descriptor> &vstack);
    
private:
    int rows; // number of rows in the maze
    int cols; // number of columns in the maze12 a
    matrix<Graph::vertex_descriptor> vertexdescriptors;
    
    matrix<bool> value;
};

#endif /* maze_hpp */