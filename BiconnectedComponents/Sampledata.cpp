#include <boost/config.hpp>
#include <vector>
#include <list>
#include <boost/graph/biconnected_components.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <iterator>
#include <iostream>

using namespace boost;

struct edge_component_t 
{
	enum {
		num = 555 
	};
	typedef edge_property_tag kind;
}edge_component;

typedef adjacency_list<vecS, vecS, undirectedS,
	no_property, property<edge_component_t, std::size_t> >graph_t;
graph_t g;

void add_edge_g(int source, int target,
		float cost, float reverse_cost,
		bool directed)
{
	//pgRouting sample data vertex start counting vertex from 1, 
	//but boost start from 0
	source--, target--;
	if (directed) {
		if (cost > 0)
			add_edge(source, target, g);
		if (reverse_cost > 0)
			add_edge(target, source, g);
	} else {
		if (cost > 0 || reverse_cost > 0)
			add_edge(source, target, g);
	}
}

void CreateGraph(void)
{
	add_edge_g(1, 2, 1, 1, false);
	add_edge_g(2, 3, -1, 1, false);
	add_edge_g(3, 4, -1, 1, false);
	add_edge_g(2, 5, 1, 1, false);
	add_edge_g(3, 6, 1, -1, false);
	add_edge_g(4, 9, 1, 1, false);
	add_edge_g(5, 6, 1, 1, false);
	add_edge_g(6, 9, 1, 1, false);
	add_edge_g(7, 8, 1, 1, false);
	add_edge_g(8, 5, 1, 1, false);
	add_edge_g(5, 10, 1, 1, false);
	add_edge_g(6, 11, 1, -1, false);
	add_edge_g(9, 12, 1, 1, false);
	add_edge_g(10, 11, 1, -1, false);
	add_edge_g(11, 12, 1, -1, false);
	add_edge_g(10, 13, 1, 1, false);
	add_edge_g(14, 15, 1, 1, false);
	add_edge_g(16, 17, 1, 1, false);
}

int main(int, char* [])
{
	//Creates a graph object with 17 vertices and 18 edges
	CreateGraph();	

	//Calculates biconnected components
	property_map < graph_t, edge_component_t >::type
	component = get(edge_component, g);
	std::size_t num_comps = biconnected_components(g, component);

	//Output
	std::cout << "Total number of biconnected components " << num_comps << std::endl;
	graph_traits < graph_t >::edge_iterator ei, ei_end;
	for (boost::tie(ei, ei_end) = edges(g); ei != ei_end; ++ei)
		std::cout << "Edge " << source(*ei, g) + 1 << " -- " 
			<< target(*ei, g) + 1
			<< " is in biconnected component " << component[*ei] << std::endl;

	return 0;
}
