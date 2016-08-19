#include<iostream>
#include<fstream>
#include<cmath>
#include<vector>

void Test( unsigned *arr, const unsigned size )
{

	for( unsigned i = 0; i < size; ++i)
		std::cout << arr[i] << std::endl;
	std::cout << std::endl;

}

void MergeSort( unsigned *arr, const unsigned size )
{

//	const unsigned level = Log( size ) / Log( 2 );

	if( size <= 1 )
		return;

	unsigned i=0, j = size/2;
	unsigned temp_arr[size];

	MergeSort( &arr[ i ], j );
	MergeSort( &arr[ j ], size - j );

	for( unsigned k = 0; k < size; ++k)
		temp_arr[k] = arr[k];

	for( unsigned k = 0; k < size; ++k)
	{

		if( j < size )
		{
	
			if( i < size/2 && temp_arr[i] < temp_arr[j] )
				arr[k] = temp_arr[ i++ ];
			else
				arr[k] = temp_arr[ j++ ];

		}
		else
			arr[k] = temp_arr[ i++ ];
	}

}

void Iter_MergeSort( unsigned *arr, const unsigned size )
{

//	const unsigned level = Log( size ) / Log( 2 );

	unsigned i, j, del;
	unsigned temp_arr[size];

	for( del = 2; del < size; )
	{

		for( unsigned count = 0; count < size; )
		{
			
			for( unsigned k = count; k < size && k < count + del; ++k)
				temp_arr[k] = arr[k];

			i = count;
			j = count + del/2;
			for( unsigned k = count; k < size &&  k < count + del; ++k)
			{

				if( j < size && j < count + del )
				{
	
					if( i < count + del/2 && temp_arr[i] < temp_arr[j] )
						arr[k] = temp_arr[ i++ ];
					else
						arr[k] = temp_arr[ j++ ];

				}
				else
					arr[k] = temp_arr[ i++ ];
			}

			count += del;
		}

		del *= 2;
	}

	i = 0;
	j = del/2;
	for( unsigned k = 0; k < size; ++k)
		temp_arr[k] = arr[k];
		
	for( unsigned k = 0; k < size; ++k)
	{

		if( j < size )
		{
	
			if( i < del/2 && temp_arr[i] < temp_arr[j] )
				arr[k] = temp_arr[ i++ ];
			else
				arr[k] = temp_arr[ j++ ];

		}
		else
			arr[k] = temp_arr[ i++ ];
	}

}

unsigned Inv_MergeSort( unsigned *arr, const unsigned size )
{

//	const unsigned level = Log( size ) / Log( 2 );

	unsigned sum = 0;
	if( size <= 1 )
		return sum;

	unsigned i=0, j = size/2;
	unsigned temp_arr[size];

	sum = Inv_MergeSort( &arr[ i ], j );
	sum = sum + Inv_MergeSort( &arr[ j ], size - j );

	for( unsigned k = 0; k < size; ++k)
		temp_arr[k] = arr[k];

	for( unsigned k = 0; k < size; ++k)
	{

		if( j < size )
		{
	
			if( i < size/2 && temp_arr[i] < temp_arr[j] )
				arr[k] = temp_arr[ i++ ];
			else
			{

				arr[k] = temp_arr[ j++ ];
				sum += size/2 - i;
			}

		}
		else
			arr[k] = temp_arr[ i++ ];
	}

	return sum;
}

int main( const int argc, const char* argv[])
{

	unsigned temp, answer, sum;
	std::vector<unsigned> iarr;

	std::ifstream i_file( argv[1] );

	while( i_file >> temp )
		iarr.push_back( temp );

	i_file.close();

	std::cout << "Size of array read in: " << iarr.size() << std::endl;

	if( iarr.size() % 10 )
	{
		answer = iarr.back();
		iarr.pop_back();
		std::cout << "Answer included in file: " << answer << std::endl; 
		std::cout << "Actual size of array: " << iarr.size() << std::endl;

	}

//	for( std::vector<unsigned>::size_type i = 0; i < iarr.size(); ++i )
//		std::cout << iarr[i] << std::endl;

	Test(&iarr[0], iarr.size() );
//	sum = Inv_MergeSort( &iarr[0], iarr.size() );

	Iter_MergeSort(  &iarr[0], iarr.size() );
	std::cout << "\n";
	Test( &iarr[0], iarr.size() );

//	if( answer )
//		std::cout << "\nAnswer: " << answer << " ";  
//	std::cout << "\nCalculated: "<< sum << std::endl; 

	return 0;
}
