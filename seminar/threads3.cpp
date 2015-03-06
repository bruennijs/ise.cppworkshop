
#include <thread>
#include <mutex>
#include <iostream>
#include <atomic>

#define ANZAHL 10000000




int main()
{
	long a = 0;
	std::atomic<long> n(a);

	std::thread t1( [&n](){ for(int i = 0; i < ANZAHL; i++ )
	                      {
	                        n++;
	                       }
	                       } );
	std::thread t2( [&n](){ for(int i = 0; i < ANZAHL; i++ )
	                       {
	                        n++;
	                        }
	                       } );
	                       
	t1.join();
	t2.join();
	
	std::cout << n << std::endl;

}



