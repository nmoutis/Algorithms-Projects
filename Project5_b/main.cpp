#include <boost/graph/adjacency_list.hpp>
#include <iostream>
#include <fstream>
#include "Heap.hpp"
#include "Heap.cpp"

using namespace boost;
using namespace std;

/* This project contains implementations of Dijkstra's and Bellman-Ford's algorithms using the boost graph library and prority queues implimented as heaps. The main function creates a directed graph from a text file and runs the two algorithms on this graph. It then prints out the shortest path (node by node) from the first node to the last node if such a path exists. The structure of the text file containing the graph is as follows:
    number of vertices /n
    first node /n
    last node /n
    node node directed_edgeweight /n
    node node directed_edgeweight /n
    ...
 
 */

struct VertexProperties;
struct EdgeProperties;

typedef adjacency_list<vecS, vecS, bidirectionalS, VertexProperties, EdgeProperties, property<vertex_index_t, int>> Graph;

struct VertexProperties
{
    Graph::vertex_descriptor pred; // predecessor node
    int weight;
    bool visited;
    bool marked;
    
};

struct EdgeProperties // Create a struct to hold properties for each edge
{
    int weight;
    bool visited;
    bool marked;
};

vector<Graph::vertex_descriptor> vertexvector;

void initializeGraph(Graph &g, Graph::vertex_descriptor &start, Graph::vertex_descriptor &end, ifstream &fin)
// Initialize g using data from fin.  Set start and end equal to the start and end nodes.
{
    EdgeProperties e;
    
    int n, i, j;
    int startId, endId;
    fin >> n;
    fin >> startId >> endId;
    Graph::vertex_descriptor v;
    
    // Add nodes.
    for (int i = 0; i < n; i++)
    {
        v = add_vertex(g);
        if (i == startId)
            start = v;
        if (i == endId)
            end = v;
    }
    
    while (fin.peek() != '.')
    {
        fin >> i >> j >> e.weight;
        add_edge(i,j,e,g);
    }
}

bool relax(Graph &g, Graph::vertex_descriptor u, Graph::vertex_descriptor v) //relax edges from u to v
{
    pair<Graph::edge_descriptor, bool> edgePair = boost::edge(u, v, g);
    Graph::edge_descriptor edge = edgePair.first;
    if(g[v].weight > (g[u].weight + g[edge].weight))
    {
        g[v].weight = (g[u].weight + g[edge].weight);
        g[v].pred = u;
        return true;
    }
    return false;
}

bool Dijkstra(Graph &g, Graph::vertex_descriptor start) //Dijkstras shortest path algorithm
{
    //set shortest path to all nodes = largevalue
    pair<Graph::vertex_iterator, Graph::vertex_iterator> vItrRange = vertices(g);
    for (Graph::vertex_iterator vItr = vItrRange.first; vItr != vItrRange.second; ++vItr)
    {
        g[*vItr].weight = LargeValue;
    }
    //set start node shortest path = 0
    g[start].weight = 0;
    
    heapV<Graph::vertex_descriptor, Graph> myminheap;
    myminheap.initializeMinHeap(vertexvector, g);
    while(myminheap.size() != 0)
    {
        Graph::vertex_descriptor vmin = myminheap.extractMinHeapMinimum(g);
        if(g[vmin].weight == LargeValue)
        {
            return false;
        }
        pair<Graph::adjacency_iterator, Graph::adjacency_iterator> adjItrRange = adjacent_vertices(vmin,g);
        for (Graph::adjacency_iterator aItr = adjItrRange.first; aItr != adjItrRange.second; ++aItr)
        {
            if(relax(g, vmin, *aItr))
            {
                Graph::vertex_descriptor vdes = *aItr;
                int heapindex = myminheap.getIndex(vdes);
                myminheap.minHeapDecreaseKey(heapindex, g);
            }
        }
    }
    return true;
}

bool BellmanFord(Graph &g, Graph::vertex_descriptor start) //BellmanFord shortest path algorithm
{
    //set shortest path to all nodes = largevalue
    pair<Graph::vertex_iterator, Graph::vertex_iterator> vItrRange = vertices(g);
    for (Graph::vertex_iterator vItr = vItrRange.first; vItr != vItrRange.second; ++vItr)
    {
        g[*vItr].weight = LargeValue;
    }
    //set start node shortest path = 0
    g[start].weight = 0;
    
    for (int i =1; i< num_vertices(g); i++)
    {
        pair<Graph::edge_iterator, Graph::edge_iterator> eItrRange = edges(g);
        for (Graph::edge_iterator eItr = eItrRange.first; eItr != eItrRange.second; ++eItr)
        {
            Graph::vertex_descriptor u = source(*eItr,g);
            Graph::vertex_descriptor v = target(*eItr,g);
            relax(g,u,v);
        }
    }
    bool negcycle = false;
    pair<Graph::edge_iterator, Graph::edge_iterator> eItrRange = edges(g);
    for (Graph::edge_iterator eItr = eItrRange.first; eItr != eItrRange.second; ++eItr)
    {
        Graph::vertex_descriptor u = source(*eItr,g);
        Graph::vertex_descriptor v = target(*eItr,g);
        if(g[v].weight > (g[u].weight + g[*eItr].weight))
        {
            negcycle = true;
            g[v].marked = true;
        }
    }
    return !negcycle;
}

void Createvertexvector(Graph &g) //create vector of vertices in graph g
{
    pair<Graph::vertex_iterator, Graph::vertex_iterator> vItrRange = vertices(g);
    for (Graph::vertex_iterator vItr = vItrRange.first; vItr != vItrRange.second; ++vItr)
    {
        vertexvector.push_back(*vItr);
    }
}

void PrintPath(Graph &g, Graph::vertex_descriptor u ,Graph::vertex_descriptor v) // print shortest path from start to end node is exists
{
    if((g[v].weight == LargeValue)| (g[v].marked == true))
    {
        cout<<"No shortest path exists."<<endl;
        return;
    }
    if (v == u)
    {
        cout<<v<<endl;
    }
    else
    {
        PrintPath(g, u, g[v].pred);
        cout<<v<<endl;
    }
}

int main(int argc, const char * argv[]) { //initialize graph from file and run Dijkstra or Bellman-Ford, then print shortest path
    
    Graph g;
    string graphfile;
    cout<<"Input graph file path."<<endl;
    cin>>graphfile;
    ifstream fin;
    fin.open(graphfile.c_str());
    if (!fin)
    {
        cerr << "Cannot open " << fileName << endl;
        exit(1);
    }
    Graph::vertex_descriptor v;
    Graph::vertex_descriptor v1;
    initializeGraph(g, v, v1, fin);
    
    fin.close();
    
    Createvertexvector(g);
    
    Dijkstra(g, v);
//    BellmanFord(g, v);
    
    PrintPath(g, v, v1);
}
