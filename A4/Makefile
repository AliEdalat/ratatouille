all: main.o food.o restaurant.o customer.o order.o
	g++ -std=c++98 main.o food.o restaurant.o customer.o order.o
	./a.out<in.txt>w.txt
main.o: main.cpp
	g++ -std=c++98 -c main.cpp
food.o: food.cpp food.h
	g++ -std=c++98 -c food.cpp
restaurant.o: restaurant.cpp restaurant.h
	g++ -std=c++98 -c restaurant.cpp
order.o: order.cpp order.h
	g++ -std=c++98 -c order.cpp
customer.o: customer.cpp customer.h
	g++ -std=c++98 -c customer.cpp
