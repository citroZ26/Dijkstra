#include <fstream>
#include <cstdlib>
#include "Directed_graph.hpp"

using namespace std;

void visit(int u) {
	cout << u << " ";
}

int main(int argc, char *argv[]) {
	
	ifstream file;
	
	if (argc == 4) {
		
		Directed_graph g;
		
		cout << "Reading graph: ";
		
		file.open(argv[1]);
		if (!file.is_open()) {
			cout << "Cannot read file " << argv[1] << ", exiting" << endl;
			exit(0);
		}

		file >> g;
		cout << "ok" << endl << endl;

		cout << g << endl;

		int source = atoi(argv[2]);

		cout << "Applying Dijkstra's algorithm with source " << source << endl << endl;
		
		Dijkstra_results res = g.dijkstra(source);
		
		cout << "dist: ";
		for (auto d: res.dist) cout << d << " ";
		cout << endl;
		
		cout << "prev: ";
		for (auto p: res.prev) cout << p << " ";
		cout << endl << endl;
		
		int target = atoi(argv[3]);
		
		cout << "Shortest path from " << source << " to " << target << ":" << endl << endl;
		
		Path p = g.shortest_path(source, target);
		
		for (auto u: p.vertices) cout << u << " ";
		cout << "(" << p.weight << ")" << endl;
		
		

	} else {
	
		cout << "Need to supply on command line: file containing graph, id of source and target nodes" << endl;
	
	}
}
