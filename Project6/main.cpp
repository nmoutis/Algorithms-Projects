#include <iostream>
#include <vector>
#include <list>
#include <fstream>
#include <queue>
#include <boost/graph/adjacency_list.hpp>
#include <iostream>
#include "heap.hpp"
#include "heap.cpp"

using namespace boost;
using namespace std;

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

// Create a struct to hold properties for each edge
struct EdgeProperties
{
    int weight;
    bool visited;
    bool marked;
};

vector<Graph::vertex_descriptor> vertexvector;

void initializeGraph(Graph &g, ifstream &fin)
// Initialize g using data from fin.  Set start and end equal
// to the start and end nodes.
{
    EdgeProperties e;
    
    int n, i, j;
    fin >> n;
    Graph::vertex_descriptor v;
    
    // Add nodes.
    for (int i = 0; i < n; i++)
    {
        v = add_vertex(g);
    }
    
    while (fin.peek() != '.')
    {
        fin >> i >> j >> e.weight;
        add_edge(i,j,e,g);
    }
}

void Createvertexvector(Graph &g) //initializes vertex vector used in min heap
{
    pair<Graph::vertex_iterator, Graph::vertex_iterator> vItrRange = vertices(g);
    for (Graph::vertex_iterator vItr = vItrRange.first; vItr != vItrRange.second; ++vItr)
    {
        vertexvector.push_back(*vItr);
    }
}

int MSTPrim(Graph &g, Graph &spangraph)
{
    pair<Graph::vertex_iterator, Graph::vertex_iterator> vItrRange = vertices(g);
    for(Graph::vertex_iterator vItr = vItrRange.first; vItr != vItrRange.second; ++vItr)
    {
        g[*vItr].weight = LargeValue;
        g[*vItr].pred = LargeValue;
    }
    g[0].weight = 0;
    
    heapV<Graph::vertex_descriptor, Graph> myminheap;
    myminheap.initializeMinHeap(vertexvector, g);
    
    int count = 0;
    while(myminheap.size() != 0)
    {
        Graph::vertex_descriptor vmin = myminheap.extractMinHeapMinimum(g);
        g[vmin].visited = true;
        spangraph[vmin].visited = true;
        
        if (g[vmin].pred != LargeValue)
        {
            pair<Graph::edge_descriptor, bool> checkEdge = edge(g[vmin].pred, vmin, g);
            pair<Graph::edge_descriptor, bool> newEdge = add_edge(g[vmin].pred, vmin, spangraph);
            spangraph[newEdge.first].weight = g[checkEdge.first].weight;
            pair<Graph::edge_descriptor, bool> newEdge2 = add_edge(vmin, g[vmin].pred, spangraph);
            spangraph[newEdge2.first].weight = g[checkEdge.first].weight;
        }
        
        pair<Graph::adjacency_iterator, Graph::adjacency_iterator> adjItrRange = adjacent_vertices(vmin,g);
        for (Graph::adjacency_iterator aItr = adjItrRange.first; aItr != adjItrRange.second; ++aItr)
        {
            pair<Graph::edge_descriptor, bool> checkEdge = edge(vmin, *aItr, g);
            if ((g[*aItr].visited == false) & (g[checkEdge.first].weight < g[*aItr].weight))
            {
                g[*aItr].pred = vmin;
                g[*aItr].weight = g[checkEdge.first].weight;
                Graph::vertex_descriptor vdes = *aItr;
                int heapindex = myminheap.getIndex(vdes);
                myminheap.minHeapDecreaseKey(heapindex, g);
                //cout<<*aItr<<", "<<vmin<<endl;
            }
        }
    }
    int connectedcomp = 0;
    pair<Graph::vertex_iterator, Graph::vertex_iterator> vItrRange1 = vertices(spangraph);
    for(Graph::vertex_iterator vItr = vItrRange1.first; vItr != vItrRange1.second; ++vItr)
    {
        if (g[*vItr].pred == LargeValue)
        {
            connectedcomp++;
        }
    }
    return connectedcomp;
}

void PrintEdges(Graph &g) //prints the source and target vertices of each edge, as well as the edge weights
{
    pair<Graph::edge_iterator, Graph::edge_iterator> eItrRange = edges(g);
    for (Graph::edge_iterator eItr = eItrRange.first; eItr != eItrRange.second; ++eItr)
    {
        Graph::vertex_descriptor source1 = source(*eItr, g);
        Graph::vertex_descriptor target1 = target(*eItr, g);
        cout<<"("<<source1<<", "<<target1<<") weight: "<<g[*eItr].weight<<endl;
    }
}

int TotalWeight(Graph &g) //returns the total edge weight of a graph, dividing by two for go-back edges
{
    int weightsum = 0;
    pair<Graph::edge_iterator, Graph::edge_iterator> eItrRange = edges(g);
    for (Graph::edge_iterator eItr = eItrRange.first; eItr != eItrRange.second; ++eItr)
    {
        weightsum = weightsum + g[*eItr].weight;
    }
    return (weightsum/2);
}

void DFSConnected(Graph &g, Graph::vertex_descriptor v, int &count) //depth first search for the is connected function
{
    g[v].visited = true;
    count++;
    pair<Graph::adjacency_iterator, Graph::adjacency_iterator> vItrRange = adjacent_vertices(v,g);
    for(Graph::adjacency_iterator vItr = vItrRange.first; vItr != vItrRange.second; ++vItr)
    {
        g[*vItr].pred = v;
        if((*vItr != g[v].pred) & (g[*vItr].visited == false))
        {
            DFSConnected(g, *vItr, count);
        }
    }
}

bool DFSCyclic(Graph &g, Graph::vertex_descriptor v, Graph::vertex_descriptor start_node, int &count) //Depth first traversal for the isCyclic function
{
    g[v].visited = true;
    count++;
    pair<Graph::adjacency_iterator, Graph::adjacency_iterator> vItrRange = adjacent_vertices(v,g);
    for(Graph::adjacency_iterator vItr = vItrRange.first; vItr != vItrRange.second; ++vItr)
    {
        g[*vItr].pred = v;
        if ((g[*vItr].visited == true) & (v != start_node) & (g[v].pred != *vItr))
        {
            return true;
        }
        else if ((g[v].pred != *vItr) & (g[*vItr].visited == false))
        {
            if (DFSCyclic(g, *vItr, start_node, count) == true)
            {
                return true;
            }
        }
    }
    return false;
}

bool isConnected(Graph &g) //uses DFS function to check if the graph is connected
{
    int count = 0;
    Graph::vertex_descriptor start = 0;
    DFSConnected(g, start, count);
    bool connected;
    if (num_vertices(g) != count)
    {
        connected = false;
    }
    else
    {
        connected = true;
    }
    pair<Graph::vertex_iterator, Graph::vertex_iterator> vItrRange = vertices(g);
    for(Graph::vertex_iterator vItr = vItrRange.first; vItr != vItrRange.second; ++vItr)
    {
        g[*vItr].visited = false;
    }
    return connected;
}

bool isCyclic(Graph &g) //uses DFS function to check for cycles
{
    bool cyclic = false;
    int totalcount = 0;
    while (totalcount < num_vertices(g))
    {
        int partialcount = 0;
        pair<Graph::vertex_iterator, Graph::vertex_iterator> vItrRange = vertices(g);
        for(Graph::vertex_iterator vItr = vItrRange.first; vItr != vItrRange.second; ++vItr)
        {
            if (g[*vItr].visited == false)
            {
                if (DFSCyclic(g, *vItr, *vItr, partialcount) == true)
                {
                    cyclic = true;
                }
                break;
            }
        }
        totalcount = totalcount + partialcount;
    }
    pair<Graph::vertex_iterator, Graph::vertex_iterator> vItrRange = vertices(g);
    for(Graph::vertex_iterator vItr = vItrRange.first; vItr != vItrRange.second; ++vItr)
    {
        g[*vItr].visited = false;
    }
    return cyclic;
}

void ConnectedorCyclic(Graph &g) //prints out whether a graph is connected or cyclic
{
    if (isConnected(g))
    {
        cout<<"Graph is connected."<<endl;
    }
    else
    {
        cout<<"Graph is not connected."<<endl;
    }
    if (isCyclic(g))
    {
        cout<<"Graph contains a cycle."<<endl;
    }
    else
    {
        cout<<"Graph does not contain a cycle."<<endl;
    }
}

void DFSSpanning(Graph &g1, Graph &g2, Graph::vertex_descriptor v, Graph::vertex_descriptor from, int &count) //uses depth first traversal to create the spanning forest
{
    g1[v].visited = true; //visit on graph 1
    if (v != from)
    {
        pair<Graph::edge_descriptor, bool> newEdge = add_edge(v, from, g2);
        pair<Graph::edge_descriptor, bool> checkEdge = edge(v, from, g1);
        g2[newEdge.first].weight = g1[checkEdge.first].weight;
        pair<Graph::edge_descriptor, bool> newEdge2 = add_edge(from, v, g2);
        pair<Graph::edge_descriptor, bool> checkEdge2 = edge(from, v, g1);
        g2[newEdge2.first].weight = g1[checkEdge2.first].weight;
        //add edge between g2 vertex and from vertex
    }
    count++;
    pair<Graph::adjacency_iterator, Graph::adjacency_iterator> vItrRange = adjacent_vertices(v,g1);
    for(Graph::adjacency_iterator vItr = vItrRange.first; vItr != vItrRange.second; ++vItr)
    {
        g1[*vItr].pred = v;
        if(g1[*vItr].visited == false)
        {
            DFSSpanning(g1, g2, *vItr, v, count);
        }
    }
}

int FindSpanningForest(Graph &g1, Graph &g2) //calls the depth first spanning tree function on each connected component and returns the number of connected components
{
    int connectedcomp=0;
    pair<Graph::vertex_iterator, Graph::vertex_iterator> vItrRange = vertices(g1);
    for(Graph::vertex_iterator vItr = vItrRange.first; vItr != vItrRange.second; ++vItr)
    {
        Graph::vertex_descriptor v1 = add_vertex(g2);
    }
    if (isConnected(g1))
    {
        int count = 0;
        DFSSpanning(g1, g2, 0, 0, count);
        connectedcomp = 1;
    }
    else
    {
        int totalcount = 0;
        while (totalcount < num_vertices(g1))
        {
            int partialcount = 0;
            pair<Graph::vertex_iterator, Graph::vertex_iterator> vItrRange = vertices(g1);
            for(Graph::vertex_iterator vItr = vItrRange.first; vItr != vItrRange.second; ++vItr)
            {
                if (g1[*vItr].visited == false)
                {
                    DFSSpanning(g1, g2, *vItr, *vItr, partialcount);
                    break;
                }
            }
            totalcount = totalcount + partialcount;
            connectedcomp++;
        }
    }
    pair<Graph::vertex_iterator, Graph::vertex_iterator> vItrRange1 = vertices(g1);
    for(Graph::vertex_iterator vItr = vItrRange1.first; vItr != vItrRange1.second; ++vItr)
    {
        g1[*vItr].visited = false;
    }
    return connectedcomp;
}

int main(int argc, const char * argv[]) {
    
    Graph g;
    string fileName;
    cout<<"Input graph file name."<<endl;
    cin>>fileName;

    ifstream fin;
    fin.open(fileName.c_str());
    if (!fin)
    {
        cerr << "Cannot open " << fileName << endl;
        exit(1);
    }
    
    initializeGraph(g, fin);
    
    fin.close();
    cout << "Graph g" << endl;
    PrintEdges(g);
    ConnectedorCyclic(g);
    cout << endl;
    
    Graph gspan;
    Graph gminspan;
    
    pair<Graph::vertex_iterator, Graph::vertex_iterator> vItrRange = vertices(g);
    for(Graph::vertex_iterator vItr = vItrRange.first; vItr != vItrRange.second; ++vItr)
    {
        Graph::vertex_descriptor v1 = add_vertex(gspan);
        Graph::vertex_descriptor v2 = add_vertex(gminspan);
    }
    Createvertexvector(g);
    
    int a = FindSpanningForest(g, gspan);
    
    cout<<"Spanning Forest Results"<<endl;
    cout<<"Edges:"<<endl;
    PrintEdges(gspan);
    cout<<"Total edge weight: "<<TotalWeight(gspan)<<endl;
    cout<<"Number of connected components: "<<a<<endl<<endl;
    
    int b = MSTPrim(g, gminspan);
    
    cout<<"Minimum Spanning Forest Results"<<endl;
    cout<<"Edges:"<<endl;
    PrintEdges(gminspan);
    cout<<"Total edge weight: "<<TotalWeight(gminspan)<<endl;
    cout<<"Number of connected components: "<<b<<endl;
    
    return 0;
}
