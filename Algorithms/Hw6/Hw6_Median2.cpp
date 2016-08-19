#include<iostream>
#include<fstream>

#include<vector>

class Medians
{

	private:
		std::vector<unsigned> keys;

	public:
		void Insert( const unsigned );
		unsigned Evaluate();
};

void Medians::Insert( const unsigned val )
{

	std::vector<unsigned>::iterator it = keys.begin();

	for( ; it != keys.end() && *it < val; ++it);


	keys.insert( it, val);

//	for(unsigned i = 0; i < keys.size(); ++i )
//		std::cout << keys[i] <<  " ";
//	std::cout << std::endl;

}

unsigned Medians::Evaluate( void )
{

	return keys[ ( keys.size() - 1)/2 ];

}
int main( const int argc, const char* argv[] )
{

	long int sum = 0;
	unsigned tmp, jnk;
	std::ifstream ifile( argv[1] );

	Medians heap;

	while( ifile >> tmp )
	{

		heap.Insert( tmp );
		jnk= heap.Evaluate();
		sum += jnk;
//		std::cout << tmp << " :: Current median is :: " << jnk << std::endl;
//		std::cout << sum << std::endl << std::endl;

	}

	ifile.close();

	std::cout << "Final solution: " << sum % 10000 << std::endl;

	return 0;
}
