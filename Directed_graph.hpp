#include <vector>		// vector
#include <functional>	// function
#include <string>		// string
#include <queue>		// queue
#include <stack>		// stack
#include <set>			// tuple

#include <cstdlib>
#include <sstream>
#include <iostream>
#include <ctime>

using namespace std;


// declarations

struct Arc {
	int nb;
	int weight;
};

struct Dijkstra_results {
	vector<int> dist;
	vector<int> prev;
};

struct Path {
	vector<int> vertices;
	int weight;
};

void visit(int u);

class Directed_graph{
	public:	
		Directed_graph(int number);
		Directed_graph() = default;

		void insert_arc(int u, int v, int w = 1);
		void bfs(int start);
		void dfs(int start);

		friend ostream &operator<<(ostream &os, const Directed_graph &g);
		friend istream &operator>>(istream &is, Directed_graph &g);
        friend bool operator==(const Arc& first, const Arc& second);
        friend bool operator<(const Arc& first, const Arc& second);

		Dijkstra_results dijkstra(int source);
		Path shortest_path(int u, int v);
		
	private:
		vector<set<Arc>> adjacency_list;
};