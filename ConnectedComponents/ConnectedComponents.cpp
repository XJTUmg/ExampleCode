#include <boost/config.hpp>
#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/connected_components.hpp>

using namespace boost;

int main(int, char* [])
{
	//Creates a graph object with 6 vertices and 5 edges.
	adjacency_list <vecS, vecS, undirectedS> G(6);
	add_edge(0, 1, G);
	add_edge(1, 4, G);
	add_edge(0, 4, G);
	add_edge(2, 5, G);
	add_edge(3, 3, G);

	//Calculates connected components
	std::vector<int> component(num_vertices(G));
	int num = connected_components(G, &component[0]);
	
	//Output
	std::vector<int>::size_type i;
	std::cout << "Total number of components: " << num << std::endl;
	for (i = 0; i != component.size(); i++)
		std::cout << "Vertex " << i << " is in component " << component[i] << std::endl;

	return 0;
}
