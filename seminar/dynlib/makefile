
build: m

libf1.so: f1.cpp f.hpp
	c++ --std=c++11 --shared -fPIC f1.cpp -o libf1.so

libf2.so: f2.cpp f.hpp
	c++ --std=c++11 --shared -fPIC f2.cpp -o libf2.so

m: m.cpp f.hpp libf1.so libf2.so
	c++ --std=c++11 m.cpp -L. -lf1 -lf2 -o m

# export LD_LIBRARY_PATH=.
