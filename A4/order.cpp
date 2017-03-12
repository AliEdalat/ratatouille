#include "order.h"
#include "customer.h"
#include "food.h"
#include <iostream>
#include <vector>

#define RESTAURANT_PHONE_LENGTH 8
#define MINIMUM_PRICE 100000
#define FREE_DELIVERY 0
#define DELIVERY_COST 5000

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
int find_restaurant(vector<Restaurant*>& restaurants,string phone){
	for (int i = 0; i < restaurants.size(); ++i)
	{
		if(restaurants[i]->get_phone() == phone){
			return i;
		}
	}
	return -1;
}
void Order::calculate_delivery_cost(std::vector<Restaurant*> restaurants){
	bool is_delivery_cost_zero=true;
	for (int i = 0; i < foods.size(); ++i)
	{
		string owner_location=this->get_owner_location();
		string food_phone=(foods[i]->food)->get_code();
		string restaurant_phone;
		for (int i = 0; i < RESTAURANT_PHONE_LENGTH; ++i)
		{
			restaurant_phone.push_back(food_phone[i]);
		}
		int index=find_restaurant(restaurants,restaurant_phone);
		if(index == -1){
			cout<<"food code is not correct!"<<endl;
			return;
		}
		string restaurant_location=restaurants[index]->get_location();
		if( owner_location.compare(restaurant_location) !=0){
			is_delivery_cost_zero=false;
			break;
		}
	}
	if(this->get_cost() > MINIMUM_PRICE && is_delivery_cost_zero != true){
		is_delivery_cost_zero=true;
	}
	if(!is_delivery_cost_zero){
		delivery_cost=DELIVERY_COST;
	}
	else{
		delivery_cost=FREE_DELIVERY;
	}
}
