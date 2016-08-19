#include<iostream>
#include<fstream>
#include<cmath>
#include<cstdlib>

#include<list>

class Two_Sum
{

	private:
		std::list<long int> *key;
		std::list<int> interval;
		const unsigned offset;
		const unsigned key_len;

		unsigned hashfunction( int val){ return std::abs(val) % key_len;};

	public:

	Two_Sum( void ): offset( 0 ), key_len(10){};
	Two_Sum( std::istream &, const unsigned & );

	void Evaluate( void );

	~Two_Sum(void);

};

Two_Sum::Two_Sum( std::istream &i_stream, const unsigned &val ): offset( val ), key_len( 500009)
{

	bool flag;
	long int tmp;
	unsigned pos;

	key = new std::list<long int>[ key_len ];

	for( unsigned i = 0; i < 2 * val + 1; ++i )
		interval.push_back( i - val );

	while( i_stream >> tmp )
	{

		pos = hashfunction( tmp );	

		flag = true;
		for( std::list<long int>::iterator it = key[pos].begin(); flag && it != key[ pos ].end(); ++it )
		{

			if( *it == tmp )
				flag = false;

		}

		if( flag )
			key[ pos ].push_front( tmp );

	}

/*	for( unsigned i = 0; i < val; ++i)
	{

		if( !key[i].empty() )
		{

			for( std::list<long int>::iterator it = key[i].begin(); it != key[ i ].end(); ++it )
				std::cout << *it << " ";
			std::cout << std::endl;

		}	
	}
*/

}

void Two_Sum::Evaluate( void )
{

	bool flag;
	long int tmp;
	unsigned pos;	

	for( unsigned i = 0; i < key_len; ++i)
	{

		if( i % offset == 0 )
			std::cout << i << std::endl ;
			for( std::list<long int>::iterator it1 = key[i].begin(); it1 != key[ i ].end(); ++it1 )
			{

				for( std::list<int>::iterator it2 = interval.begin(); it2 != interval.end(); ++it2 )
				{

					tmp = *it2 - *it1;
					if( tmp != *it1 )
					{
						flag = true;
						pos = hashfunction( tmp );
						for( std::list<long int>::iterator it3 = key[pos].begin(); flag && it3 != key[ pos ].end(); ++it3 )
						{

							if( *it3 == tmp )
							{

//								std::cout <<*it1 << " " <<*it3 << " Found it: " << *it2<< std::endl;
								interval.erase( it2-- );
								key[pos].erase( it3--);
								flag = false;

							}

						}

					}

				}

				key[i].erase( it1--);
			}

	}

	std::cout << "\nFound sums: " << 2*offset + 1 - interval.size() << std::endl;

}

Two_Sum::~Two_Sum( void )
{

	delete [] key;

}

int main( const int argc, const char* argv[])
{

	std::ifstream ifile( argv[1] );
	unsigned num = atoi( argv[2] );

	Two_Sum problem( ifile, num );
	ifile.close();

	problem.Evaluate();

	return 0;
}
