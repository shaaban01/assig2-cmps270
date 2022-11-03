// header file for the extending of graph in graph_cycle,cpp
#include <iostream>
#include <iterator>
#include <map>
#include <vector>
#include <stdexcept>
using namespace std;

class Graph
{
protected:
    map<int, vector<int>> outgoing;

public:
    // constructor for graph
    // require: two vectors of each starting and ending vertex
    // effect: create the graph with the inputed data
    Graph(const vector<int> &starts, const vector<int> &ends);

    // to get the number of the outgoing edges
    // require: the node to be in the graph
    // effect: return the number of the outgoing edges
    int numOutgoing(const int nodeID) const;

    // adjacent nodes
    // require: the node to be in the graph
    // effect: return the adjacent nodes of the node
    const vector<int> &adjacent(const int nodeID) const;

    // extra function to return the number of nodes in the graph
    int numNodes() const;
};

// ----------------------------------------------------------------
// ----------------------------------------------------------------

Graph::Graph(const vector<int> &starts, const vector<int> &ends)
{
    if (starts.size() != ends.size())
    {
        throw invalid_argument(" Start /end point lists differ in length ");
    }

    for (unsigned i = 0; i < starts.size(); i++)
    {
        int start = starts[i], end = ends[i];
        outgoing[start].push_back(end);
        outgoing[end]; // Just to indicate this node exists
    }
}

// ----------------------------------------------------------------

int Graph::numOutgoing(const int nodeID) const
{
    return adjacent(nodeID).size();
}

// ----------------------------------------------------------------

const vector<int> &Graph ::adjacent(const int nodeID) const
{
    map<int, vector<int>>::const_iterator i = outgoing.find(nodeID);
    if (i == outgoing.end())
    {
        throw invalid_argument(" Invalid node ID");
    }
    return i->second;
}

// ----------------------------------------------------------------

int Graph::numNodes() const
{
    return outgoing.size();
}

// ----------------------------------------------------------------
// ----------------------------------------------------------------
