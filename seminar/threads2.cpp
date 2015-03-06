
#include <thread>
#include <mutex>
#include <iostream>
#include <windows.h>

#define ANZAHL 10000000

volatile long n = 0;
std::mutex mn;

int main()
{
	

	std::thread t1( [](){ for(int i = 0; i < ANZAHL; i++ )
	                      {
							mn.lock();
	                        n++;
	                        mn.unlock();
	                       }
	                       } );
	std::thread t2( [](){ for(int i = 0; i < ANZAHL; i++ )
	                       {
	                        mn.lock();
	                        n++;
	                        mn.unlock();
	                        }
	                       } );
	                       
	t1.join();
	t2.join();
	
	std::cout << n << std::endl;

}



