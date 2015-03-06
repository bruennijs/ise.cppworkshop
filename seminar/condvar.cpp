// C++11

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>


std::condition_variable cond;
std::mutex mut;
enum { NONE, PING, PONG, KLING, KLONG } state;


void wait_for_ping_to_process()
{
    std::unique_lock<std::mutex> lock(mut);
    while( state != PING )
    {
        cond.wait(lock);
    }
    std::cout << "ping" << std::endl;
    state = PONG;
    cond.notify_all();
}

void wait_for_pong_to_process()
{
    std::unique_lock<std::mutex> lock(mut);
    while( state != PONG )
    {
        cond.wait(lock);
    }
    std::cout << "pong" << std::endl;
    state = KLING;
    cond.notify_all();
}

void wait_for_kling_to_process()
{
    std::unique_lock<std::mutex> lock(mut);
    while( state != KLING )
    {
        cond.wait(lock);
    }
    std::cout << "kling" << std::endl;
    state = KLONG;
    cond.notify_all();
}

void wait_for_klong_to_process()
{
    std::unique_lock<std::mutex> lock(mut);
    while( state != KLONG )
    {
        cond.wait(lock);
    }
    std::cout << "klong" << std::endl;
}

int main()
{
	std::thread workerThread1(wait_for_ping_to_process);
	std::thread workerThread2(wait_for_pong_to_process);
	std::thread workerThread3(wait_for_kling_to_process);
	std::thread workerThread4(wait_for_klong_to_process);
	
	{
		std::lock_guard<std::mutex> lock(mut);
		state = PING;
	}
	cond.notify_all();
	
	workerThread1.join();
	workerThread2.join();
	workerThread3.join();
	workerThread4.join();

	return 0;
}

