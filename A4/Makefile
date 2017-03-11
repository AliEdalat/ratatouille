all: Main Food Restaurant Customer Order
	g++ -std=c++98 main.o food.o restaurant.o customer.o order.o
	./a.out<in.txt>w.txt
Main:
	g++ -std=c++98 -c main.cpp
Food:
	g++ -std=c++98 -c food.cpp
Restaurant:
	g++ -std=c++98 -c restaurant.cpp
Order:
	g++ -std=c++98 -c order.cpp
Customer:
	g++ -std=c++98 -c customer.cpp
