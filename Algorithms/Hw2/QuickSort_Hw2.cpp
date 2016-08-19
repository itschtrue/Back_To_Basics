#include<iostream>
#include<fstream>
#include<vector>

unsigned QuickSort( unsigned *arr, const unsigned size )
{

	if( size <= 1 )
		return 0;

	unsigned sum, pivot, temp; 
	unsigned barrier = 1;

/*
	temp = arr[ size - 1 ];
	arr[ size - 1 ] = arr[ 0 ];
	arr[ 0 ] = temp;
*/

	if( arr[ size - 1 ] < arr[( size - 1) /2] )
	{

		pivot = ( arr[ (size - 1)/2] < arr[ 0 ] )? (size-1)/2: ( ( arr[0] < arr[size - 1] )? size - 1 : 0 );

	}
	else
	{

		// arr[size/2] < arr[size - 1]
		pivot = ( arr[size - 1] < arr[ 0 ] )? size - 1: (( arr[(size-1)/2] > arr[0] )? (size-1)/2: 0 );

	}

//	std::cout << arr[0] << " " << arr[(size-1)/2] << " " << arr[size -1] << std::endl;	

//	std::cout << "pivot: " << arr[0] << std::endl;
//	for( unsigned i = 0; i < size; ++i )
//		std::cout << arr[ i ] << std::endl;

	if( pivot ) 
	{

		temp = arr[ pivot ];
		arr[ pivot ] = arr[0];
		arr[0] = temp;

	}

//	std::cout << "pivot: " << arr[0] << std::endl;

	pivot = arr[ 0 ];
	for( unsigned i = 1; i < size; ++i )
	{

		if( pivot > arr[ i ] )
		{

			temp = arr[ barrier ];
			arr[ barrier ] = arr[ i ];
			arr[ i ] = temp;
			++barrier; 

		}

	}

	arr[ 0 ] = arr[ barrier - 1 ];
	arr[ barrier - 1 ] = pivot;

	sum = size - 1;

	sum += QuickSort( &arr[0], barrier - 1 );
	sum += QuickSort( &arr[barrier ], size - barrier  );

	return sum;

}

int main( const int argc, const char* argv[] )
{

	unsigned temp;
	std::ifstream i_file( argv[1] );
	std::vector<unsigned> ivec;
	
	while( i_file >> temp )
		ivec.push_back( temp );
 
	i_file.close();

	temp = QuickSort( &ivec[0], ivec.size() );

	std::cout << "Number of comparisons: " << temp << std::endl;

//	for( std::vector<unsigned>::size_type i = 0; i < ivec.size(); ++i)
//		std::cout << ivec[i] << std::endl;

	return 0;

}
