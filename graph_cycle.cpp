#include <iostream>
#include <iterator>
#include <map>
#include <vector>
#include <stdexcept>
#include "my_graph.h"

using namespace std;

class GraphCycle : public Graph
{
public:
    GraphCycle(const vector<int> &starts, const vector<int> &ends) : Graph(starts, ends) {}
    vector<int> hasCycle();

private:
    vector<int> hasCycle(int node, vector<bool> &visited, vector<int> &path);
    vector<int> hasCycleUtil(int node, vector<bool> &visited, vector<int> &path, int i, vector<int> &list);
};

vector<int> GraphCycle::hasCycle()
{
    vector<int> pathC;
    vector<bool> vistedC(numNodes());
    vector<int> cycle;
    return hasCycle(outgoing.begin()->first, vistedC, pathC);
}
vector<int> GraphCycle::hasCycle(int node, vector<bool> &visited, vector<int> &path)
{
    visited[node] = true;
    vector<int> list;
    path.push_back(node);
    for (int i = 0; i < Graph::outgoing[node].size(); i++) // for every node that it adjacent to that node
    {
        if (!visited[outgoing[node][i]])
            list = hasCycle(outgoing[node][i], visited, path);
        else
            return hasCycleUtil(node, visited, path, i, list);
    }
    return path;
}

vector<int> GraphCycle::hasCycleUtil(int node, vector<bool> &visited, vector<int> &path, int i, vector<int> &list)
{

    for (int j = 0; j < path.size(); j++)
    {
        if (path[j] == outgoing[node][i])
        {
            for (int k = j; k < path.size(); k++)
                list.push_back(path[k]);
            list.push_back(outgoing[node][i]);
            return list;
        }
    }
    return list;
}

int main()
{
    vector<int> start1;
    vector<int> end1;
    vector<int> cycle1;
    start1 = {1, 2, 3, 3};
    end1 = {2, 3, 1, 4};
    GraphCycle g1(start1, end1);

    cycle1 = g1.hasCycle();

    for (int i : cycle1)
    {
        cout << i << " ";
    }

    cout << endl;
    cout << endl;

    vector<int> start2;
    vector<int> end2;
    vector<int> cycle2;
    start2 = {1, 2, 3, 5, 5};
    end2 = {2, 3, 4, 1, 4};
    GraphCycle g2(start2, end2);

    cycle1 = g2.hasCycle();

    for (int i : cycle2)
    {
        cout << i << " ";
    }
}