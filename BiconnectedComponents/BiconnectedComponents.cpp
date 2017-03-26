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

int main(int, char* [])
{
	//Creates a graph object with 11 vertices and 11 edges
	typedef adjacency_list<vecS, vecS, undirectedS,
	  no_property, property<edge_component_t, std::size_t> >graph_t;
	graph_t g;
	add_edge(0, 1, g);
	add_edge(1, 2, g);
	add_edge(2, 0, g);
	add_edge(2, 3, g);
	add_edge(2, 4, g);
	add_edge(3, 4, g);
	add_edge(5, 6, g);
	add_edge(6, 7, g);
	add_edge(8, 9, g);
	add_edge(9, 10, g);
	add_edge(8, 10, g);

	//Calculates biconnected components
	property_map < graph_t, edge_component_t >::type
	component = get(edge_component, g);
	std::size_t num_comps = biconnected_components(g, component);

	//Output
	std::cout << "Total number of biconnected components " << num_comps << std::endl;
	graph_traits < graph_t >::edge_iterator ei, ei_end;
	for (boost::tie(ei, ei_end) = edges(g); ei != ei_end; ++ei)
		std::cout << "Edge " << source(*ei, g) << " -- " 
			<< target(*ei, g)
			<< " is in biconnected component " << component[*ei] << std::endl;

	return 0;
}
