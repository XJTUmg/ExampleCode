#include <boost/config.hpp>
#include <iostream>
#include <vector>
#include <boost/graph/strong_components.hpp>
#include <boost/graph/adjacency_list.hpp>

using namespace boost;

int main(int, char* [])
{
	//Creates a graph object with 7 vertices and 7 edges
	adjacency_list <vecS, vecS, directedS> G;
	add_edge(0, 1, G);
	add_edge(1, 2, G);
	add_edge(0, 2, G);
	add_edge(2, 4, G);
	add_edge(4, 1, G);
	add_edge(3, 5, G);
	add_edge(5, 6, G);

	//Calculates strongly connected components
	std::vector<int> component(num_vertices(G));
	int num = strong_components(G, &component[0]);

	//Output
	std::vector<int>::size_type i;
	std::cout << "Total number of strongly connected components: " << num << std::endl;
	for (i = 0; i != component.size(); i++)
		std::cout << "Vertex " << i << " is in strongly connected component " << component[i] << std::endl;

	return 0;
}
