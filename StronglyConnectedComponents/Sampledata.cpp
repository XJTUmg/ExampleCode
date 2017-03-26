#include <boost/config.hpp>
#include <iostream>
#include <vector>
#include <boost/graph/strong_components.hpp>
#include <boost/graph/adjacency_list.hpp>

using namespace boost;

adjacency_list <vecS, vecS, directedS> G;

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
	add_edge_G(1, 2, 1, 1, true);
	add_edge_G(2, 3, -1, 1, true);
	add_edge_G(3, 4, -1, 1, true);
	add_edge_G(2, 5, 1, 1, true);
	add_edge_G(3, 6, 1, -1, true);
	add_edge_G(4, 9, 1, 1, true);
	add_edge_G(5, 6, 1, 1, true);
	add_edge_G(6, 9, 1, 1, true);
	add_edge_G(7, 8, 1, 1, true);
	add_edge_G(8, 5, 1, 1, true);
	add_edge_G(5, 10, 1, 1, true);
	add_edge_G(6, 11, 1, -1, true);
	add_edge_G(9, 12, 1, 1, true);
	add_edge_G(10, 11, 1, -1, true);
	add_edge_G(11, 12, 1, -1, true);
	add_edge_G(10, 13, 1, 1, true);
	add_edge_G(14, 15, 1, 1, true);
	add_edge_G(16, 17, 1, 1, true);
}

int main(int, char* [])
{
	//Creates a graph object with 17 vertices and 30 edges
	CreateGraph();

	//Calculates strongly connected components
	std::vector<int> component(num_vertices(G));
	int num = strong_components(G, &component[0]);

	//Output
	std::vector<int>::size_type i;
	std::cout << "Total number of strongly connected components: " << num << std::endl;
	for (i = 0; i != component.size(); i++)
		std::cout << "Vertex " << i + 1 << " is in strongly connected component " << component[i] << std::endl;

	return 0;
}
