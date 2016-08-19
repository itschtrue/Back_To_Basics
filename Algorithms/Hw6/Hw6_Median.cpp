#include<iostream>
#include<fstream>

#include<vector>

class Median_Heap
{

	private:
		std::vector<unsigned> low_heap;
		std::vector<unsigned> high_heap;

		void Max_Top( const unsigned );
		void Max_Insert( const int );
		
		void Min_Top( const unsigned );
		void Min_Insert( const int );

	public:
		void Insert( unsigned );
		unsigned Median( void ); 

		~Median_Heap(){};

};

void Median_Heap::Max_Top( const unsigned node )
{

  unsigned large = node;
  unsigned lchild = 2*node + 1;
  unsigned rchild = lchild + 1;

  if( lchild < low_heap.size() && low_heap[lchild] > low_heap[node] )
    large = lchild;

  if( rchild < low_heap.size() &&  low_heap[rchild]> low_heap[large] )
    large = rchild;

  if( large != node )
  {

    lchild = low_heap[ node ];
    low_heap[ node ] = low_heap[ large ];
    low_heap[ large ] = lchild;

    Max_Top( large );
  }

}

void Median_Heap::Max_Insert( const int node )
{

	unsigned swap;
	unsigned parent = ( node - 1)/2;

	if( parent != node && low_heap[ node ] > low_heap[ parent ] )
	{

		swap = low_heap[ parent ];
		low_heap[ parent ] = low_heap[node];
		low_heap[node] = swap;

		Max_Insert( parent );

	} 

}

void Median_Heap::Min_Top( const unsigned node )
{

  unsigned small = node;
  unsigned lchild = 2*node + 1;
  unsigned rchild = lchild + 1;

  if( lchild < high_heap.size() && high_heap[lchild] < high_heap[node] )
    small = lchild;

  if( rchild < high_heap.size() &&  high_heap[rchild] < high_heap[small] )
    small = rchild;

  if( small != node )
  {

    lchild = high_heap[ node ];
    high_heap[ node ] = high_heap[ small ];
    high_heap[ small ] = lchild;

    Min_Top( small );
  }

}


void Median_Heap::Min_Insert( const int node )
{

	unsigned swap;
	unsigned parent = ( node - 1 )/2;

	if( parent != node && high_heap[ node ] < high_heap[ parent ] )
	{

		swap = high_heap[ parent ];
		high_heap[ parent ] = high_heap[node];
		high_heap[node] = swap;

		Min_Insert( parent );

	} 

}


void Median_Heap::Insert( unsigned node )
{


	unsigned hold;
	if( low_heap.size() == high_heap.size() )
	{

		if( !high_heap.empty() && node > high_heap[0] )
		{

			hold = node;
			node = high_heap[0];
			high_heap[0] = hold;		
			Min_Top( 0 );

		}

		low_heap.push_back( node );
		Max_Insert( low_heap.size() - 1 );
		

	}
	else
	{

		if( node < low_heap[0] )
		{

			hold = node;
			node = low_heap[0];
			low_heap[0] = hold;		
			Max_Top( 0 );

		}

		high_heap.push_back( node );
		Min_Insert( high_heap.size() - 1 );

	}

}

unsigned Median_Heap::Median( void )
{

	unsigned median = -1;
	if( !high_heap.empty() )
		median = high_heap[0];

	if( !low_heap.empty() && median > low_heap[0])
		median = low_heap[0];

/*	for( std::vector<unsigned>::size_type i = 0; i < low_heap.size(); ++i)
		std::cout << low_heap[i] << " ";
	std::cout << std::endl;

	for( std::vector<unsigned>::size_type i = 0; i < high_heap.size(); ++i)
		std::cout << high_heap[i] << " ";
	std::cout << std::endl;
*/
	return median;

}

int main( const int argc, const char* argv[] )
{

	long int sum = 0;
	unsigned tmp, jnk;
	std::ifstream ifile( argv[1] );

	Median_Heap heap;

	while( ifile >> tmp )
	{

		heap.Insert( tmp );
		jnk= heap.Median();
		sum += jnk;
//		std::cout << tmp << " :: Current median is :: " << jnk << std::endl;
//		std::cout << sum << std::endl << std::endl;

	}

	ifile.close();

	std::cout << "Final solution: " << sum % 10000 << std::endl;

	return 0;
}
