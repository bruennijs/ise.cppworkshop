#include <thread>
#include <iostream>
#include <mutex>
#include <time.h>
#include <atomic>

class NoOperator
{
public:
	NoOperator();
	~NoOperator();

	/* data */
};

int main() {
	long n = 0;

	std::mutex m1;

	std::atomic<long> na(n);

	auto l1 = [&n, &na, &m1](void) 
		{ 
			for (int i=0; i<10000000; i++)
			{
				std::lock_guard<std::mutex> lock(m1);
				n -= 1;
				n += 2;				
			}
		};

	auto l2 = [&n, &na, &m1](void) 
		{ 
			for (int i=0; i<10000000; i++)
			{
				na -= 1;
				na += 2;
			}

			std::cout << "n=" << (long)n << std::endl; 
			std::cout << "na=" << (long)na << std::endl; 
		};

	std::thread t1(l2);

	std::thread t2(l2);

	t1.join();
	t2.join();

	std::cout << "END n=" << (long)n << std::endl; 
	std::cout << "END na=" << (long)na << std::endl; 
}