#include "order.h"
#include "customer.h"
#include "food.h"
#include <iostream>
#include <vector>

using namespace std;
Order::Order(Customer* owner){
	order_owner=owner;
}
Order::Order(Customer* owner,std::vector<food_in_order*> _foods){
	order_owner=owner;
	for (int i = 0; i < _foods.size(); ++i)
	{
		foods.push_back(_foods[i]);
	}

}
void Order::add_food(food_in_order* food){
	foods.push_back(food);
}
void Order::calculate_cost(){
	order_cost=0;
	for (int i = 0; i < foods.size(); ++i)
	{
		int food_cost=(foods[i]->food)->get_cost();
		int number=foods[i]->number_of_food;
		order_cost+=food_cost*number;
	}

}
