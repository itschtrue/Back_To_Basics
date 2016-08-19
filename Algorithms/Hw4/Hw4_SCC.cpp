#include<iostream>
#include<fstream>
#include<string>
#include<sstream>

#include<vector>
#include<stack>

struct Vertex
{

	bool flag;
	unsigned leader;
	std::vector<unsigned> edges;
	std::vector<unsigned> redges;

	Vertex( ):flag( true), leader(0){};
	Vertex( bool val): flag(val), leader(0) {};

};

struct Edge
{

	unsigned vertices[2];

};

class Graph
{

	private:
		std::vector< Vertex > vertices;
		std::vector< Edge > edges;

	public:
		Graph(){};
		Graph( std::istream &);

		void Print_Vertex(void) const;
		void Print_Edge(void) const;
		unsigned VCount(void) const { return vertices.size(); };
		unsigned ECount(void) const { return edges.size(); };

		void SCC( void );

		~Graph(void){};


};

Graph::Graph( std::istream &i_stream)
{

	unsigned tmp1, tmp2, tail;

	Edge tmp_edge;

	std::string holder;
	std::stringstream s_holder;

	tail = 0;

	while( std::getline( i_stream, holder ) )
	{
	
		if( !holder.empty() )
		{	

			s_holder.str( holder );

			s_holder >> tmp1;
			s_holder >> tmp2;
			tmp_edge.vertices[0] = tmp1 - 1;
			tmp_edge.vertices[1] = tmp2 - 1;

			edges.push_back( tmp_edge );		
			s_holder.clear();

			if( tail < tmp1 )
				tail = tmp1 ;


		}

	}

	vertices.resize( tail );

	for( std::vector< Edge >::size_type i = 0; i < edges.size(); ++i)
	{

		vertices[ edges[i].vertices[0] ].edges.push_back( i );	
		vertices[ edges[i].vertices[1] ].redges.push_back( i );

	}

}

void Graph::SCC( void )
{

	const unsigned fsize = vertices.size();
	unsigned f[ fsize ];
	int tmp = 0, tmp_vertices, point; 
	bool flag;
	std::stack< unsigned > work_stack;

	for( int i = fsize - 1; i >= 0; --i )
	{

		if( vertices[i].flag )
		{

			vertices[i].flag = false;
			work_stack.push( i );
			while( !work_stack.empty() )
			{
			
				flag = true;
				tmp_vertices = work_stack.top();
//				std::cout << tmp_vertices << ":\n";
				for( std::vector< unsigned >::size_type j = 0; j < vertices[tmp_vertices].redges.size(); ++j )
				{

					point = edges[ vertices[tmp_vertices].redges[j] ].vertices[0];	
					if( vertices[ point ].flag )
					{
//						std::cout << point<< " ";
						flag = false;
						vertices[ point].flag = false;
						work_stack.push( point );
			
					}

				}
//				std::cout << std::endl;
				if( flag )
				{

					work_stack.pop();
					f[ tmp++ ] = tmp_vertices;

				} 

			}

		}

	}

//	std::cout << "f:";
//	for( unsigned i = 0; i < fsize; ++i)
//		std::cout << f[i] << " ";
//	std::cout << std::endl;

	for( int i = fsize - 1; i >= 0; --i )
	{
	
		tmp = f[ i ];
		f[i] = 0;
//		std::cout << "i="<<i << std::endl;
		if( !vertices[ tmp ].flag )
		{
			vertices[ tmp ].flag = true;
			work_stack.push( tmp );
			while( !work_stack.empty() )
			{
			
				flag = true;
				tmp_vertices = work_stack.top();
//				std::cout << tmp_vertices << ":\n";
				for( std::vector< unsigned >::size_type j = 0; j < vertices[tmp_vertices].edges.size(); ++j )
				{

					point = edges[ vertices[tmp_vertices].edges[j] ].vertices[1];
					if(!vertices[ point ].flag )
					{
						
//						std::cout << point<< " ";
						flag = false;
						vertices[ point].flag = true;
						work_stack.push( point );
			
					}

				}
//				std::cout << std::endl;

				if( flag )
				{

					work_stack.pop();
					vertices[ tmp_vertices ].leader = i;
					++f[ i ];

				} 

			}

		}

	}

	for( unsigned i = 0; i < 5; ++i)
	{

		tmp = 0;
		for( unsigned j = 0; j < fsize; ++j)
		{

			if( f[j] > f[ tmp ] )
				tmp = j; 

		}

		std::cout<< tmp << " " << f[tmp] << std::endl;
		f[tmp] = 0;

	}

}

void Graph::Print_Vertex(void) const
{

  std::cout << "Vertices: " << std::endl;
  for( std::vector< Vertex>::size_type i = 0; i < vertices.size(); ++i )
  {

    std::cout << i << ":\n";
    for( std::vector< unsigned >::size_type j = 0; j < vertices[i].edges.size(); ++j)
      std::cout << vertices[i].edges[j] << " ";
    std::cout << std::endl;
		for( std::vector< unsigned >::size_type j = 0; j < vertices[i].redges.size(); ++j)
      std::cout << vertices[i].redges[j] << " ";
    std::cout << std::endl;


  }
	std::cout << std::endl;

}

void Graph::Print_Edge( void ) const
{

  std::cout << "Edges: " << std::endl;
  for(std::vector< Edge >::size_type i = 0; i< edges.size(); ++i)
    std::cout << i << ": (" << edges[i].vertices[0] << ", " << edges[i].vertices[1] << ")\n";
	std::cout << std::endl;

}

int main( const int argc, const char* argv[] )
{


	std::ifstream i_file( argv[1] );

	Graph graph( i_file );
	i_file.close();

//	graph.Print_Vertex();
//	graph.Print_Edge();

	graph.SCC();

	return 0;
}
