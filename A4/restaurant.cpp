#include <iostream>
#include <vector>
#include <algorithm>
#include "restaurant.h"
#include "food.h"

using namespace std;
Restaurant::Restaurant(string name,string phone,string location){
	restaurant_name=name;
	restaurant_phone=phone;
	restaurant_location=location;
}
Restaurant::Restaurant(string name,string phone,string location,vector<Food*>& _foods){
	restaurant_name=name;
	restaurant_phone=phone;
	restaurant_location=location;
	for (int i = 0; i < _foods.size(); ++i)
	{
		foods.push_back(_foods[i]);
	}
}
void Restaurant::add_food(Food* _food){
	foods.push_back(_food);
}
void Restaurant::show_menu(){
	for (int i = 0; i < foods.size(); ++i)
	{
		cout<<foods[i]->get_code()<<' '<<foods[i]->get_name()<<' '<<foods[i]->get_type()<<' '<<foods[i]->get_cost()<<endl;
	}
}
vector<Food*> Restaurant::get_foods(){
	return foods; 
}
void Restaurant::show_foods_list(){
	for (int j = 0; j < foods.size(); ++j)
	{
		cout<<foods[j]->get_code()<<' '<<foods[j]->get_name()<<' '<<foods[j]->get_type()<<' '<<foods[j]->get_cost()<<' '<< this->get_name()<<' '<<this->get_location()<<endl;
	}
	return;
}
bool compare2(Food* food1,Food* food2){
	return food1->get_code()<food2->get_code();
}
void Restaurant::sort_foods_in_menu(){
	sort(foods.begin(),foods.end(),compare2);
}