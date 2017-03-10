#ifndef ORDER_H
#define ORDER_H

#include <iostream>
#include "customer.h"
#include "food.h"
#include <vector>

typedef struct order_food food_in_order;
struct order_food
{
	Food* food;
	int number_of_food;
	std::string personalization;
};

class Order
{
public:
	Order(Customer* owner);
	Order(Customer* owner,std::vector<food_in_order*> _foods);
	int get_cost(){return order_cost;}
	int get_delivery_cost(){return delivery_cost;}
	void set_delivery_cost(int cost){delivery_cost=cost;}
	std::string get_owner_name(){return order_owner->get_name();}
	std::string get_owner_phone(){return order_owner->get_phone_number();}
	std::string get_owner_location(){return order_owner->get_location();}
	void calculate_cost();
	void add_food(food_in_order* food);
	std::vector<food_in_order*> get_foods(){return foods;}
	~Order();
private:
	Customer* order_owner;
	int order_cost=0;
	int delivery_cost;
	std::vector<food_in_order*> foods;
	
};

#endif