#include <iostream>
#include <limits.h>
#include <vector>
#include <list>
#include <fstream>
#include <queue>
#include <boost/graph/adjacency_list.hpp>
#include "maze.hpp"

using namespace boost;
using namespace std;

std::ostream& operator<<(std::ostream& os, const Graph &g) //overloads output operator
{
    os<<"Vertex Properties"<<endl;
    typedef graph_traits<Graph>::vertex_iterator vertex_iter;
    pair<vertex_iter, vertex_iter> vp;
    for (vp = vertices(g); vp.first != vp.second; ++vp.first)
    {
        os <<"cell: ["<< g[*vp.first].cell.first<<", "<<g[*vp.first].cell.second<<"]"<<endl;
        os<<"pred: "<<g[*vp.first].pred<<endl;
        os <<"weight: "<< g[*vp.first].weight<<endl;
        os<<"visited: "<<g[*vp.first].visited<<endl;
        os<<"marked: "<<g[*vp.first].marked<<endl<<endl;
    }
    os<<"Edge Properties"<<endl;
    typedef graph_traits<Graph>::edge_iterator edge_iter;
    pair<edge_iter, edge_iter> ep;
    edge_iter editer, editer_end;
    for (tie(editer, editer_end) = edges(g); editer != editer_end; ++editer)
    {
        os <<"weight: "<< g[*editer].weight << endl;
        os <<"visited: "<< g[*editer].visited << endl;
        os <<"marked: "<< g[*editer].marked << endl<<endl;
    }
    return os;
}

int main(int argc, const char * argv[]) {
    try
    {
        string fileName;
        cout << "Enter Filename" << endl;
        cin >> fileName;
        
        ifstream fin;
        
        fin.open(fileName.c_str());
        if (!fin)
        {
            cerr << "Cannot open " << fileName << endl;
            exit(1);
        }
        maze m(fin);
        fin.close();
        
        m.print(m.numRows()-1,m.numCols()-1,0,0); //print maze unsolved
        Graph g; //declare graph
        m.mapMazeToGraph(g);
//        std::cout << g << endl; //print mapped graph using overloaded output operator
        stack<Graph::vertex_descriptor> vstack;
        pair<int, int> goal (19,19);
//        m.FindPathDFSRecursive(g, 0, goal, vstack);
        
        //create parameters for shortest path finder
        vector<Graph::vertex_descriptor> shrtstckvector;
        stack<Graph::vertex_descriptor> shortstack;
//        m.FindSHortestPathDFS(g, 0, goal, vstack, shrtstckvector, shortstack);
        
//        m.FindPthDFSStack(g, 0, goal, vstack);
        
        queue<Graph::vertex_descriptor> vqueue;
        m.FindShortestPathBFS(g, 0, goal, vqueue, vstack);
        
        m.printPath(vstack, g);
    }
    catch(std::exception &ex)
    {
        cout<<ex.what()<<endl;
    }
    return 0;
}