all: 1.out 2.out 3.out

1.out: 1.cpp
	g++ -std=c++17 -o 1.out 1.cpp

2.out: 2.cpp
	g++ -std=c++17 -o 2.out 2.cpp

3.out: 3.cpp
	g++ -std=c++17 -o 3.out 3.cpp

clean:
	rm 1.out 2.out 3.out