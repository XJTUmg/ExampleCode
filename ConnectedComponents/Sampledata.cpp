#include <boost/config.hpp>
#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/connected_components.hpp>

using namespace boost;

adjacency_list <vecS, vecS, undirectedS> G;

void add_edge_G(int source, int target,
		float cost, float reverse_cost,
		bool directed)
{
	//pgRouting sample data vertex start counting vertex from 1, 
	//but boost start from 0
	source--, target--;
	if (directed) {
		if (cost > 0)
			add_edge(source, target, G);
		if (reverse_cost > 0)
			add_edge(target, source, G);
	} else {
		if (cost > 0 || reverse_cost > 0)
			add_edge(source, target, G);
	}
}

void CreateGraph(void)
{
	add_edge_G(1, 2, 1, 1, false);
	add_edge_G(2, 3, -1, 1, false);
	add_edge_G(3, 4, -1, 1, false);
	add_edge_G(2, 5, 1, 1, false);
	add_edge_G(3, 6, 1, -1, false);
	add_edge_G(4, 9, 1, 1, false);
	add_edge_G(5, 6, 1, 1, false);
	add_edge_G(6, 9, 1, 1, false);
	add_edge_G(7, 8, 1, 1, false);
	add_edge_G(8, 5, 1, 1, false);
	add_edge_G(5, 10, 1, 1, false);
	add_edge_G(6, 11, 1, -1, false);
	add_edge_G(9, 12, 1, 1, false);
	add_edge_G(10, 11, 1, -1, false);
	add_edge_G(11, 12, 1, -1, false);
	add_edge_G(10, 13, 1, 1, false);
	add_edge_G(14, 15, 1, 1, false);
	add_edge_G(16, 17, 1, 1, false);
}

int main(int, char* [])
{
	//Creates a graph object with 17 vertices and 18 edges.
	CreateGraph();

	//Calculates connected components
	std::vector<int> component(num_vertices(G));
	int num = connected_components(G, &component[0]);
	
	//Output
	std::vector<int>::size_type i;
	std::cout << "Total number of components: " << num << std::endl;
	for (i = 0; i != component.size(); i++)
		std::cout << "Vertex " << i + 1 << " is in component " << component[i] << std::endl;

	return 0;
}
