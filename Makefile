CXX = g++
CXXFLAGS = -Wall -std=c++17

all: loadbalancer

loadbalancer: main.o WebServer.o LoadBalancer.o Switch.o
	$(CXX) $(CXXFLAGS) -o loadbalancer main.o WebServer.o LoadBalancer.o Switch.o

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

WebServer.o: WebServer.cpp
	$(CXX) $(CXXFLAGS) -c WebServer.cpp

LoadBalancer.o: LoadBalancer.cpp
	$(CXX) $(CXXFLAGS) -c LoadBalancer.cpp

Switch.o: Switch.cpp
	$(CXX) $(CXXFLAGS) -c Switch.cpp

clean:
	rm -f *.o loadbalancer