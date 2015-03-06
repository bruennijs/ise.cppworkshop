
#include <thread>
#include <mutex>
#include <iostream>
#include <atomic>

#define ANZAHL 100000

class Zaehler
{
public:
	Zaehler() : n(0) {}
	
	long wert()
	{
		std::lock_guard<std::mutex> lock( mn );
		return n;
	}
	
	void inc()
	{
		std::lock_guard<std::mutex> lock( mn );
		n++;
	}
	
	void reset()
	{
		std::lock_guard<std::mutex> lock( mn );
		n = 0;
	}
	
private:
	volatile long n = 0;
	std::mutex mn;
};

Zaehler z;

void threadFunction()
{
	for(int i = 0; i < ANZAHL; i++ )
	{
		z.inc();
	}                   
}

int main()
{
	

	std::thread t1( threadFunction );
	std::thread t2( threadFunction );
	                       
	t1.join();
	t2.join();
	
	std::cout << z.wert() << std::endl;
}



