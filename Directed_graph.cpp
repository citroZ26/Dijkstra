#include "Directed_graph.hpp"

ostream &operator<<(ostream &os, const Directed_graph &g) {
	for (auto u = g.adjacency_list.begin();u != g.adjacency_list.end(); ++u){
		os << '['<<distance(g.adjacency_list.begin(),u)<<"] ";
		for (auto v : *u){
			os << v.nb << " ("<<v.weight<<") ";
		}
		os<<endl;
	}
	return os;
}

istream &operator>>(istream &is, Directed_graph &g){
	string line;
	stringstream line_stream;
	int u, v, w;
	while (getline(is,line)) {
		line_stream.clear();
		line_stream.str(line);
		if (line_stream>>u>>v) {
			if (line_stream>>w) {
				g.insert_arc(u, v, w);
			} else {
				g.insert_arc(u, v);
			}
		} 
	}
	return is;
}

bool operator==(const Arc& first, const Arc& second){
	return (first.nb==second.nb);
}

bool operator<(const Arc& first, const Arc& second){
	return (first.nb<second.nb);
}


void dfs_recursive(const vector<set<Arc>> &adjacency_list, const int &u, vector<bool>& visited) {
		
	visit(u);
	visited[u] = true;
				
	for (const auto& a: adjacency_list[u]){
		if (!visited[a.nb]){
			dfs_recursive(adjacency_list, a.nb, visited);
		}
	}
}


void dfs_iterative(const vector<set<Arc>> &adjacency_list, const int &start, vector<bool>& visited) {

	stack<int> pending;  
	pending.push(start);
			
	while (!pending.empty()) {
		int u = pending.top();
		pending.pop();
		if (!visited[u]) {
			visit(u);
			visited[u] = true;
			for (auto v = adjacency_list[u].rbegin(); v != adjacency_list[u].rend(); ++v)
				pending.push(v->nb);
		}
	}
}

void Directed_graph::dfs(int start) {
	/* Voir cours
	   "Parcours en profondeur
	   Au début, on marque le sommet s et on le met dans une pile.
	   Tant que la pile n'est pas vide, on dépile un sommet,
	   et pour chacun de ses successeurs v, on marque v et on l’empile.
	   Exploration en O(m)"
	   */
	bool recursive = false;
	
	vector<bool> visited(this->adjacency_list.size(),false);

	if (recursive) {

	    dfs_recursive(adjacency_list, start, visited);

	} else {

		dfs_iterative(adjacency_list, start, visited);

	}

}

void Directed_graph::bfs(int start){
	/* Voir cours
	   "Parcours en largeur
	   Au début, on marque le sommet s et on le met dans une file.
	   Tant que la file n'est pas vide, on sort un sommet de la file,
	   et pour chacun de ses successeurs v, on marque v et on le met dans la file.
	   Exploration en O(m) (on parcourt au maximum chacun des arcs)"
	*/
	
	queue<int> pending; 
	pending.push(start);

	vector<bool> visited(adjacency_list.size(),false);

	while (!pending.empty()) {
		int u = pending.front();
		pending.pop();

		if (!visited[u]) {
			visited[u] = true;
			visit(u);
			for (const auto& a: adjacency_list[u])
				pending.push(a.nb);
		}

	}
}


const float initial_proportionality = 3./4.;

Directed_graph::Directed_graph(int number_of_edges){
	const int max_number_of_vertex = number_of_edges * initial_proportionality;
	adjacency_list.resize(max_number_of_vertex);
	int i1, i2;
	srand(time(NULL));
	for (int i = 0; i < number_of_edges; ++i){
		i1 = rand() % max_number_of_vertex;
		i2 = rand() % max_number_of_vertex;
		this->insert_arc(i1,i2);
	}
	vector<bool> visited(this->adjacency_list.size(),false);
	dfs_iterative(this->adjacency_list, 0, visited);
	for (int i = 1;i < this->adjacency_list.size();++i) {
		if (!visited[i]){
			i1 = i/2;
			i2 = i;
			this->insert_arc(i1,i);
		}
	}
}

void Directed_graph::insert_arc(int u, int v, int w){
	if (u>=this->adjacency_list.size()||v>=this->adjacency_list.size()) {
		this->adjacency_list.resize(max(u,v)+1);
	}
	this->adjacency_list[u].insert(Arc{v,w});
}