#include "maze.hpp"
maze::maze(ifstream &fin)
// Initializes a maze by reading values from fin.  Assumes that the
// number of rows and columns indicated in the file are correct.
{
    fin >> rows;
    fin >> cols;
    
    char x;
    vertexdescriptors.resize(rows, cols);
    value.resize(rows,cols);
    for (int i = 0; i <= rows-1; i++)
        for (int j = 0; j <= cols-1; j++)
        {
            fin >> x;
            if (x == 'O')
                value[i][j] = true;
            else
                value[i][j] = false;
        }
    
}

void maze::print(int goalI, int goalJ, int currI, int currJ)
// Print out a maze, with the goal and current cells marked on the
// board.
{
    cout << endl;
    
    if (goalI < 0 || goalI > rows || goalJ < 0 || goalJ > cols)
        throw rangeError("Bad value in maze::print");
    
    if (currI < 0 || currI > rows || currJ < 0 || currJ > cols)
        throw rangeError("Bad value in maze::print");
    
    for (int i = 0; i <= rows-1; i++)
    {
        for (int j = 0; j <= cols-1; j++)
        {
            if (i == goalI && j == goalJ)
                cout << "*";
            else
                if (i == currI && j == currJ)
                    cout << "+";
                else
                    if (value[i][j])
                        cout << " ";
                    else
                        cout << "X";
        }
        cout << endl;
    }
    cout << endl;
}

bool maze::isLegal(int i, int j)
// Return the value stored at the (i,j) entry in the maze, indicating
// whether it is legal to go to cell (i,j).
{
    if (i < 0 || i > rows || j < 0 || j > cols)
        throw rangeError("Bad value in maze::isLegal");
    
    return value[i][j];
}

void maze::mapMazeToGraph(Graph &g) //takes a graph as an input and creates vertices and edges corresponding to all valid paths in the maze structure
{
    for(int i=0; i<rows; i++)
    {
        for(int j=0; j<cols; j++)
        {
            if(value[i][j] == true){
                Graph::vertex_descriptor v = add_vertex(g);
                vertexdescriptors[i][j] = v;
                pair<int,int> mazeindex(i,j);
                g[vertexdescriptors[i][j]].cell = mazeindex;
                if(i>0)
                {
                    if(value[i-1][j] == true)
                    {
                        pair<Graph::edge_descriptor, bool> e = add_edge(vertexdescriptors[i-1][j], vertexdescriptors[i][j], g);
                        pair<Graph::edge_descriptor, bool> e1 = add_edge(vertexdescriptors[i][j], vertexdescriptors[i-1][j], g);
                        g[e.first].weight =4;
                        g[e.first].visited =false;
                        g[e.first].marked =false;
                    }
                }
                if(j>0)
                {
                    if(value[i][j-1] == true)
                    {
                        pair<Graph::edge_descriptor, bool> e = add_edge(vertexdescriptors[i][j-1], vertexdescriptors[i][j], g);
                        pair<Graph::edge_descriptor, bool> e1 = add_edge(vertexdescriptors[i][j], vertexdescriptors[i][j-1], g);
                        g[e.first].weight =4;
                        g[e.first].visited =false;
                        g[e.first].marked =false;
                    }
                }
            }
        }
    }
}

void maze::printPath(stack<Graph::vertex_descriptor> &s, Graph g)
{
    stack<Graph::vertex_descriptor> realorder;
    int vsize = s.size();
    for(int i = 0; i< vsize; i++)
    {
        realorder.push(s.top());
        s.pop();
    }
    for(int i = 0; i< vsize; i++)
    {
        cout<<"["<<g[realorder.top()].cell.first<<", "<<g[realorder.top()].cell.second<<"]"<<endl;
        realorder.pop();
    }
}

bool maze::FindPathDFSRecursive(Graph &g, Graph::vertex_descriptor v, pair<int,int> goal, stack<Graph::vertex_descriptor> &vstack)
{
    g[v].visited = true; //mark as visited
    vstack.push(v);
    if (g[v].cell == goal) //check if its the goal
    {
        return true;
    }
    else
    {
        bool unvisitedneighbors = false;
        pair<Graph::adjacency_iterator, Graph::adjacency_iterator> adjnodes = adjacent_vertices(v,g);
        for (adjnodes; adjnodes.first != adjnodes.second; ++adjnodes.first) //loop through adjacent nodes
        {
            if (g[*adjnodes.first].visited == false)
            {
                unvisitedneighbors = true;
                if (FindPathDFSRecursive(g, *adjnodes.first, goal, vstack) ==true)
                {
                    return true;
                }
            }
        }
        if (unvisitedneighbors == false)
        {
            vstack.pop(); //if the loop ended and no unvisited neighbors returned true, return false
            return false;
        }
        vstack.pop();
        return false;
    }
}

void maze::test(Graph &g, Graph::vertex_descriptor v)
{
    pair<Graph::adjacency_iterator, Graph::adjacency_iterator> adjnodes = adjacent_vertices(v,g);
    for (adjnodes; adjnodes.first != adjnodes.second; ++adjnodes.first)
    {
        cout<<g[*adjnodes.first].cell.first<<", "<<g[*adjnodes.first].cell.second<<endl;
    }
}

void maze::FindSHortestPathDFS(Graph &g, Graph::vertex_descriptor v, pair<int, int> goal, stack<Graph::vertex_descriptor> &vstack, vector<Graph::vertex_descriptor> &shrtstckvector, stack<Graph::vertex_descriptor> &shortstack)
{
    g[v].visited = true; //mark as visited
    vstack.push(v);
    shrtstckvector.push_back(v);
    if (g[v].cell == goal) //check if its the goal
    {
        if (vstack.size() < shortstack.size())
        {
            int shortsize = shortstack.size();
            for(int i = 0; i< shortsize; i++)
            {
                shortstack.pop();
            }
            for(int i = (int)(shrtstckvector.size()-1) ; i>-1; i--)
            {
                shortstack.push(shrtstckvector[i]);
            }
        }
        if (shortstack.size() ==0)
        {
            for(int i = (int)(shrtstckvector.size()-1) ; i>-1; i--)
            {
                shortstack.push(shrtstckvector[i]);
            }
        }
    }
    else
    {
        bool unvisitedneighbors = false;
        pair<Graph::adjacency_iterator, Graph::adjacency_iterator> adjnodes = adjacent_vertices(v,g);
        for (Graph::adjacency_iterator aditer= adjnodes.first; aditer != adjnodes.second; ++aditer) //loop through adjacent nodes
        {
            if (g[*aditer].visited == false)
            {
                unvisitedneighbors = true;
                FindSHortestPathDFS(g, *aditer, goal, vstack, shrtstckvector, shortstack);
            }
        }
        if (unvisitedneighbors == false)
        {
            vstack.pop(); //if the loop ended and no unvisited neighbors returned true, return false
            shrtstckvector.pop_back();
        }
        if (vstack.size() > 0)
        {
            vstack.pop();
            shrtstckvector.pop_back();
        }
    }
}

void maze::FindPthDFSStack(Graph &g, Graph::vertex_descriptor v, pair<int, int> goal, stack<Graph::vertex_descriptor> &vstack)
{
    g[v].visited = true;
    vstack.push(v);
    while (vstack.empty() ==false)
    {
        g[vstack.top()].visited =true;
        if (g[vstack.top()].cell == goal)
        {
            return;
        }
        bool unvisitedneighbors = false;
        pair<Graph::adjacency_iterator, Graph::adjacency_iterator> adjnodes = adjacent_vertices(vstack.top(),g);
        
        for (Graph::adjacency_iterator aditer = adjnodes.first ; aditer!= adjnodes.second; ++aditer) //loop through adjacent nodes
        {
            if (g[*aditer].visited == false)
            {
                unvisitedneighbors = true;
                vstack.push(*aditer);
            }
        }
        if (unvisitedneighbors ==false)
        {
            vstack.pop();
        }
    }
}

void maze::FindShortestPathBFS(Graph &g, Graph::vertex_descriptor v, pair<int, int> goal, queue<Graph::vertex_descriptor> &vqueue, stack<Graph::vertex_descriptor> &vstack)
{
    g[v].visited = true;
    vqueue.push(v);
    
    while (vqueue.empty() == false)
    {
        g[vqueue.front()].visited = true;
        if (g[vqueue.front()].cell == goal)
        {
            Graph::vertex_descriptor v = vqueue.front();
            while (v>0)
            {
                vstack.push(v);
                v=g[v].pred;
            }
            vstack.push(v);
            return;
        }
        bool unvisitedneighbors = false;
        pair<Graph::adjacency_iterator, Graph::adjacency_iterator> adjnodes = adjacent_vertices(vqueue.front(),g);
        
        for (Graph::adjacency_iterator aditer = adjnodes.first ; aditer!= adjnodes.second; ++aditer) //loop through adjacent nodes
        {
            if (g[*aditer].visited == false)
            {
                unvisitedneighbors = true;
                vqueue.push(*aditer);
                g[*aditer].pred = vqueue.front();
            }
        }
        vqueue.pop();
    }
}




