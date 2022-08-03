#include <cstdio>
#include <vector>

#include "Graph2.hh"

void showPath(int, std::vector<int>&);

int main()
{
    Graph2 g;
    g.loadInfo("../data/people.txt");
    g.loadEdges("../data/relationship.txt");

    g.showGraph();

    std::vector<int> path;
    g.findEulerPath(path);
    reverse(path.begin(), path.end());

    g.showPath(path);
    return 0;
}
