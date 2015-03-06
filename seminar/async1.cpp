// C++11
#include <iostream>
#include <future>
#include <mutex>
#include <chrono>

int main()
{
	std::mutex m;
	auto l1 = [&]()->int{      std::chrono::milliseconds duration( 1000 );
	                           for( int i = 0; i < 10; i++ )
	                           {
	                               std::this_thread::sleep_for( duration );
	                               m.lock();
	                               std::cout << "ping" << std::endl;
	                               m.unlock();
	                           }
	                           return 0; };
	auto l2 = [&]()->int{      std::chrono::milliseconds duration( 1370 );
	                           for( int i = 0; i < 7; i++ )
	                           {
	                               m.lock();
	                               std::cout << "pong" << std::endl;
	                               m.unlock();
	                               std::this_thread::sleep_for( duration );
	                           }
	                           return 0; };
	std::future<int> f1 = std::async( std::launch::async, l1 );
	std::future<int> f2 = std::async( std::launch::async, l2 );

	int r1 = f1.get();
	int r2 = f2.get();
	
	std::cout << r1 << std::endl;
	std::cout << r2 << std::endl;

	f1 = std::async( std::launch::deferred, l1 );
	f2 = std::async( std::launch::deferred, l2 );

	r1 = f1.get();
	r2 = f2.get();
	
	std::cout << r1 << std::endl;
	std::cout << r2 << std::endl;

	return 0;
}

