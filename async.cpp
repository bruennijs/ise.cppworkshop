#include <iostream>
#include <future>
#include <list>

int main() {
	std::list<std::future<int>> tasks;

	auto l1 = [&](int i) -> int 
		{  
			std::cout << "i=" << i << std::endl;
			return i * i;
		};

	tasks.push_back(std::async( std::launch::async, l1, 2));
	tasks.push_back(std::async( std::launch::async, l1, 21));

	for (auto& f : tasks)
		f.wait();

	for (auto& f : tasks)
		std::cout << f.get() << std::endl;
}