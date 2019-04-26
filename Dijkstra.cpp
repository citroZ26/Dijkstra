//
// Created by delab on 15/04/2019.
//

#include <fstream>
#include "Directed_graph.hpp"

Dijkstra_results Directed_graph::dijkstra(int source)
{
    Dijkstra_results res;

    std::set<int> S{};
    std::set<int> Q{1,2,3,4};

    int minDist = NULL;
    int u = 0;

    for (int i = 0; i <= Q.size(); ++i) {
        res.dist[i] = INFINITY;
        res.prev[i] = NULL;
    }

    res.dist[1] = 0;
    res.prev[1] = 1;

    while(!Q.empty())
    {
        if(res.dist[u] < minDist ){
            minDist = res.dist[u];
        }
        u++;
    }
    S.insert(minDist);

    return res;
}

Path Directed_graph::shortest_path(int u, int v) {
    Path p;
    return p;
}