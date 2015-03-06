// ACHTUNG: RACE CONDITION!
#include <thread>
#include <iostream>


int main()
{
	volatile long n = 0;

	std::thread t1( [&n](){ for(int i = 0; i < 10000000; i++ )
	                        n++;
	                       } );
	std::thread t2( [&n](){ for(int i = 0; i < 10000000; i++ )
	                        n++;
	                       } );
	                       
	t1.join();
	t2.join();
	
	std::cout << n << std::endl;

}



