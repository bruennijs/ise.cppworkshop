// C++11
#include <iostream>
#include <future>
#include <mutex>
#include <list>

volatile long n = 0;
std::mutex m;

void threadFunction()
{
	for( int i = 0; i < 1000; ++i )
	{
		std::lock_guard<std::mutex> guard( m );
		n++;
	}
}

int main()
{
	std::list<std::future<void>> tasks;
	for( int i = 0; i < 1000; ++i )
		tasks.push_back( std::move( std::async( std::launch::deferred, threadFunction ) ) ); 

	for( auto &e : tasks )
		e.wait();
	
	std::cout << n << std::endl;

	return 0;
}

