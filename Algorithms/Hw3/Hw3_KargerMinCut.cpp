#include<iostream>
#include<fstream>
#include<string>
#include<sstream>

#include<vector>
#include<cmath>

#include<ctime>
#include<cstdlib>

struct Vertex
{

	unsigned point;
	std::vector<unsigned> edges;

	Vertex( void ) {};
	Vertex( unsigned val ) : point( val ) {};

};

struct Edge
{

	unsigned vertices[2];

};

class Graph
{

	private:

		unsigned edge_tail;
		std::vector< Vertex > vertices;
		std::vector< Edge > edges;

		bool Merge( const unsigned );

	public:

		Graph(){};
		Graph( std::istream &);
		void Print_Vertex(void) const;
		void Print_Edge(void) const;
		unsigned VCount(void) const { return vertices.size(); };
		unsigned ECount(void) const { return edges.size() - edge_tail; };
		unsigned KargerMinCut( void );

		~Graph(void){};


};

Graph::Graph( std::istream &i_stream ): edge_tail(0)
{

	unsigned temp1, temp2;
	std::string holder;
	std::stringstream s_holder;

	srand( time(NULL) );

	Vertex temp_vertex( -1 );
	Edge temp_edge;	

	while( std::getline( i_stream, holder ) )
	{
		if( !holder.empty())
		{ 

			s_holder.str( holder );
			s_holder >> temp1;
			--temp1;
			while( s_holder >> temp2 )
			{
				--temp2;
				if( temp2 > temp1)
				{

					temp_edge.vertices[0] = temp1;
					temp_edge.vertices[1] = temp2;
					edges.push_back( temp_edge );

				}

			}

			vertices.push_back( temp_vertex );

			s_holder.clear();

		}
	}

	for( std::vector< Edge >::size_type i = 0; i < edges.size(); ++i)
	{

		vertices[ edges[i].vertices[0] ].edges.push_back(i);
		vertices[ edges[i].vertices[1] ].edges.push_back(i);		

	}

}

bool Graph::Merge( const unsigned edge_i )
{

	bool flag;
	unsigned i , j, loops, swap;
	unsigned tmp;

	i = vertices[ edges[ edge_i ].vertices[0] ].point; 
	j = vertices[ edges[ edge_i ].vertices[1] ].point; 

	loops = edges[ edge_i ].vertices[0];
	while( i != -1 )
	{
		loops = i;
		i = vertices[ i ].point;
	}

	Vertex &vert1 = vertices[loops];

	loops = edges[ edge_i].vertices[1];
	while( j != -1 )
	{
		loops = j;
		j = vertices[ j].point;
	}
	Vertex &vert2 = vertices[loops];

	const unsigned size_edge = vert1.edges.size() + vert2.edges.size();
	std::vector<unsigned> tmp_edge = vert1.edges;
	vert1.edges.clear();
	
	vert2.point = edges[ edge_i ].vertices[0];

	Edge swap_edge;	

	i = 0;
	j = 0;
	loops = 0;

	for( unsigned k = 0; k < size_edge; ++k )
	{

		if( i < tmp_edge.size() && j < vert2.edges.size() )
		{

			if( tmp_edge[i] != vert2.edges[j] )
			{

				if( tmp_edge[ i ] > vert2.edges[j] )
					vert1.edges.push_back( vert2.edges[j++] );
				else
					vert1.edges.push_back( tmp_edge[i++] );

			}
			else
			{

				swap_edge = edges[ edge_tail ];
				edges[ edge_tail ] = edges[ tmp_edge[i] ];
				edges[ tmp_edge[i] ] = swap_edge;
		
				flag = true;
				
				swap = swap_edge.vertices[ 0];
				tmp = vertices[ swap ].point;

				while( tmp != -1 )
				{
					swap = tmp;
					tmp = vertices[ tmp ].point;
				}
	
				for( unsigned it = 0; flag && it < vertices[ swap ].edges.size() - 1; ++it)
				{
	
					if( vertices[ swap ].edges[ it + 1 ] < tmp_edge[i] )
						vertices[ swap ].edges[ it ] =  vertices[ swap ].edges[ it + 1 ];
					else
					{
						flag = false;
						vertices[ swap ].edges[ it ] = tmp_edge[i];
					}

				}  
			 
				if( flag )
					vertices[ swap ].edges[ vertices[ swap ].edges.size() - 1 ] = tmp_edge[i];

				
				flag = true;
				swap = swap_edge.vertices[ 1 ];
				tmp = vertices[ swap ].point;

				while( tmp != -1 )
				{

					swap = tmp;
					tmp = vertices[ tmp ].point;
				}

				for( unsigned it = 0; flag && it < vertices[ swap ].edges.size() - 1; ++it)
				{

					if( vertices[ swap ].edges[ it + 1 ] < tmp_edge[i] )
						vertices[ swap ].edges[ it ] =  vertices[ swap ].edges[ it + 1 ];
					else
					{
						flag = false;
						vertices[ swap ].edges[ it ] = tmp_edge[i];
					}

				}  
			 
				if( flag )
					vertices[ swap ].edges[ vertices[ swap ].edges.size() - 1 ] = tmp_edge[i];

				++edge_tail;
				++i;
				++j;
				--k;
				++loops;

			}

		}
		else
		{

			if( j < vert2.edges.size() )
				vert1.edges.push_back( vert2.edges[j++] );
			if( i < tmp_edge.size() )
				vert1.edges.push_back( tmp_edge[ i++ ] );

		}				

	}

	vert2.edges.clear();

	return true;
	
}

unsigned Graph::KargerMinCut( void )
{	

	unsigned n = vertices.size(), con_edge;
	for( unsigned i = 0; i < n - 2; ++i)
	{

		con_edge = edge_tail + rand()%( edges.size() - edge_tail );
		Merge( con_edge );
		
	}

	return edges.size() - edge_tail;

}

void Graph::Print_Vertex(void) const
{

	std::cout << "Vertices: " << std::endl;
	for( std::vector< Vertex>::size_type i = 0; i < vertices.size(); ++i )
	{

		std::cout << i << ": ";
		for( std::vector< unsigned >::size_type j = 0; j < vertices[i].edges.size(); ++j)
			std::cout << vertices[i].edges[j] << " ";
		std::cout << std::endl;

	}

}

void Graph::Print_Edge( void ) const
{

	unsigned i;

	std::cout <<"Contracted Edges:"<<std::endl;
	for( i = 0; i < edge_tail; ++i )
		std::cout << i << ": (" << edges[i].vertices[0] << ", " << edges[i].vertices[1] << ")\n";

	std::cout << "Edges: " << std::endl;
	for(;i< edges.size(); ++i)
		std::cout << i << ": (" << edges[i].vertices[0] << ", " << edges[i].vertices[1] << ")\n";

}

int main( const int argc, const char * argv[] )
{

	unsigned n, mincut, trial;
	std::ifstream i_file( argv[1]);

	const Graph graph( i_file );
	Graph tmp_graph;
	i_file.close();

	mincut = graph.ECount();
	n = graph.VCount();
	n = n*n*std::log(n);

	std::cout << n << std::endl;

	for(unsigned i = 0; i < n; ++i)
	{

		tmp_graph = graph;

		trial = tmp_graph.KargerMinCut();

		//tmp_graph.Print_Vertex();
		//tmp_graph.Print_Edge();
	
		if( mincut > trial)
			mincut = trial;

		//std::cout << trial << std::endl;

		if( !(i%10000) )
			std::cout << i<< " " << mincut << std::endl;

	}

	std::cout << "Min Cut count: " << mincut << std::endl;

	return 0;

}

