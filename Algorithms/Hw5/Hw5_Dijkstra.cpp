#include<iostream>
#include<fstream>
#include<string>
#include<sstream>

#include<vector>

struct Vertex
{

	bool flag;
	unsigned key;
	std::vector<unsigned> arcs;

	Vertex(): flag(true), key( -1 ){};

};

struct Arc
{

	unsigned length;
	unsigned vertices[2];

};

class Graph
{

	private:
		std::vector< Vertex > vertices;
		std::vector< Arc > arcs;
		std::vector< unsigned > keys;

		void Min_Heapify( const unsigned);
		void Heapify( const unsigned );
		unsigned Extract_Min( void );

	public:
		Graph(void){};
		Graph(std::istream &);

		void Print_Vertex( void ) const;
		void Print_Arc( void ) const;
		void Print_Keys( void ) const;

		void Dijkstra_ShortestPath( const unsigned );

		~Graph( void ) {};

};

Graph::Graph( std::istream &i_stream)
{

	char ctmp;
	std::string hold;
	std::stringstream s_hold;

	Arc tmp_arc;
	Vertex tmp_vertex;

	while( std::getline( i_stream, hold ) )
	{

		if( !hold.empty() )
		{

			s_hold.str( hold );

			s_hold >> tmp_arc.vertices[0];
			--( tmp_arc.vertices[0] );
			while( s_hold >> tmp_arc.vertices[1])
			{
	
				--(tmp_arc.vertices[1]);
				s_hold >> ctmp >> tmp_arc.length;
				arcs.push_back( tmp_arc );

			}

			vertices.push_back( tmp_vertex );
			s_hold.clear();


		}

	}

	for( std::vector< Arc >::size_type i = 0; i < arcs.size(); ++i )
		vertices[ arcs[i].vertices[ 0 ] ].arcs.push_back( i );

}

void Graph::Min_Heapify( const unsigned i_vert )
{

	unsigned smalls = i_vert;
	unsigned lchild = 2*i_vert + 1;
	unsigned rchild = lchild + 1;

	if( lchild < keys.size() && vertices[ keys[ i_vert ] ].key > vertices[ keys[ lchild ] ].key )  
		smalls = lchild;

	if( rchild < keys.size() && vertices[ keys[ smalls ] ].key > vertices[ keys[ rchild ] ].key )  
		smalls = rchild;

	if( smalls != i_vert )
	{

		lchild = keys[ i_vert ];
		keys[ i_vert ] = keys[ smalls ];
		keys[ smalls ] = lchild;

		Min_Heapify( smalls );
	}


}

void Graph::Heapify( const unsigned i_vert )
{

	unsigned tail_vert, tmp, base = vertices[i_vert].key;
	for( std::vector< unsigned >::size_type j = 0; j < vertices[i_vert].arcs.size(); ++j )
	{

		tmp = vertices[ i_vert ].arcs[j];
		tail_vert = arcs[ tmp ].vertices[1];
		if( vertices[ tail_vert ].key == -1u )
			keys.push_back( tail_vert );

		if( vertices[ tail_vert].flag && vertices[ tail_vert ].key > vertices[i_vert].key + arcs[tmp].length )
			vertices[tail_vert].key = vertices[ i_vert ].key + arcs[tmp].length;	

	}

	for( unsigned j = ( keys.size() - 1 )/2; j < -1; --j )
		Min_Heapify( j );

}

unsigned Graph::Extract_Min( void )
{

	unsigned pos_min = keys[0];

	keys[ 0 ] = keys[ keys.size() - 1];
	keys.pop_back();

	Heapify( pos_min );

	vertices[ pos_min ].flag = false;
	return vertices[ pos_min ].key;

}

void Graph::Dijkstra_ShortestPath( const unsigned source )
{

	unsigned solution[] = {7,37,59,82,99,115,133,165,188,197}; 

	vertices[ source ].key = 0;
	Heapify( source );

//	Print_Keys();
	while( !keys.empty())
		Extract_Min();
//	std::cout << "Extract One:" << std::endl;
//	Print_Keys();

	for( unsigned i = 0; i < 10; ++i )
		std::cout<< vertices[ solution[i]-1 ].key <<",";
	std::cout << std::endl; 

}

void Graph::Print_Keys(void) const
{

	for( std::vector<unsigned>::size_type i = 0; i < keys.size(); ++i)
		std::cout << keys[i] << " " << vertices[ keys[i] ].key << std::endl;

}

void Graph::Print_Vertex( void ) const
{

  std::cout << "Vertices: " << std::endl;
  for( std::vector< Vertex>::size_type i = 0; i < vertices.size(); ++i )
  {

    std::cout << i << ":\n";
    for( std::vector< unsigned >::size_type j = 0; j < vertices[i].arcs.size(); ++j)
      std::cout << vertices[i].arcs[j] << " ";
    std::cout << vertices[i].key << std::endl;

  }
	std::cout << std::endl;


}

void Graph::Print_Arc( void ) const
{

  std::cout << "Arcs: " << std::endl;
  for(std::vector< Arc >::size_type i = 0; i< arcs.size(); ++i)
    std::cout << i << ": (" << arcs[i].vertices[0] << ", " << arcs[i].vertices[1] << ") = " << arcs[i].length << std::endl;
	std::cout << std::endl;

}

int main( const int argc, const char* argv[])
{

	std::ifstream i_file( argv[1] );

	Graph graph( i_file );
	i_file.close();

//	graph.Print_Vertex();
//	graph.Print_Arc();

	graph.Dijkstra_ShortestPath( 0 );	

	return 0;
}
