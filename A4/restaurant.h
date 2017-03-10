#ifndef RESTAURANT_H
#define RESTAURANT_H

#include "food.h"
#include <iostream>
#include <vector>

class Restaurant
{
public:
	Restaurant(std::string name,std::string phone,std::string location);
	Restaurant(std::string name,std::string phone,std::string location,std::vector<Food*>& foods);
	std::string get_name(){return restaurant_name;}
	std::string get_phone(){return restaurant_phone;}
	std::string get_location(){return restaurant_location;}
	void add_food(Food* food);
	std::vector<Food*> get_foods();
	void show_menu();
	~Restaurant();
private:
	std::string restaurant_name;
	std::string restaurant_phone;
	std::string restaurant_location;
	std::vector<Food*> foods;
	
};

#endif