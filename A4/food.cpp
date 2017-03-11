#include "food.h"
#include <iostream>
#include <cstdlib>
using namespace std;

Food::Food(string code,string name,string type,string cost){
	food_code=code;
	food_name=name;
	food_type=type;
	dish_cost=atoi(cost.c_str());
}
