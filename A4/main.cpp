#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "food.h"
#include "restaurant.h"
#include "order.h"
#include "customer.h"

using namespace std;
int find_restaurant_with_phone(vector<Restaurant*>& restaurants,string phone);
string find_restaurant_of_food_location(Food* food,vector<Restaurant*>& restaurants){
	string food_code=food->get_code();
	string food_phone;
	for (int i = 0; i < 8; ++i)
	{
		food_phone.push_back(food_code[i]);
	}
	for (int i = 0; i < restaurants.size(); ++i)
	{
		
		string restaurants_phone =(restaurants[i])->get_phone();
		cout<<restaurants_phone<<' '<<food_phone<<endl; 
		if( restaurants_phone == food_phone){
			return restaurants[i]->get_location();
		}
		
	}
	
	return " ";
}
void calculate_delivery_cost(vector<Restaurant*>& restaurants,Order* order){
	bool is_delivery_cost_zero=true;
	vector<food_in_order*> foods=order->get_foods();
	for (int i = 0; i < foods.size(); ++i)
	{
		string owner_location=order->get_owner_location();
		string food_phone=(foods[i]->food)->get_code();
		string restaurant_phone;
		for (int i = 0; i < 8; ++i)
		{
			restaurant_phone.push_back(food_phone[i]);
		}
		int index=find_restaurant_with_phone(restaurants,restaurant_phone);
		string restaurant_location=restaurants[index]->get_location();
		if( owner_location.compare(restaurant_location) !=0){
			is_delivery_cost_zero=false;
			break;
		}
	}
	if(order->get_cost() > 100000 && is_delivery_cost_zero != true){
		is_delivery_cost_zero=true;
	}
	if(!is_delivery_cost_zero){
		order->set_delivery_cost(5000);
	}
	else{
		order->set_delivery_cost(0);
	}
}
string find_first_item_file(string& line,char character){
	string result;
	int index=line.find(character);
	if(index != -1){
		result=line.substr(0,index);
		line=line.substr(index+1);
	}
	else{
		result=line;
	}
	return result;
}
int read_restaurants_file(vector<Restaurant*>& restaurants){
	ifstream file("restaurant.txt");
	if(!file.is_open()){
		cout<<"i can not read \"restaurants.txt\"!"<<endl;
		return -1;
	}
	string temp;
	int line_counter=0;
	Restaurant* new_restaurant;
	while(getline(file,temp)){
		line_counter++;
		cout<<temp<<endl;
		if(line_counter ==1 && temp.compare("\n") != -1){
			string name=find_first_item_file(temp,',');
			string phone=find_first_item_file(temp,',');
			string location=find_first_item_file(temp,',');
			new_restaurant=new Restaurant(name,phone,location);
		}
		if(line_counter !=1 && temp.compare("\n") != -1){
			string code=find_first_item_file(temp,',');
			string name=find_first_item_file(temp,',');
			string type=find_first_item_file(temp,',');
			string cost=find_first_item_file(temp,',');
			new_restaurant->add_food(new Food(code,name,type,cost));
		}
		if( temp.compare("\n") == -1){
			line_counter=0;
			restaurants.push_back(new_restaurant);
		}
		
	}
	if(!getline(file,temp)){
		restaurants.push_back(new_restaurant);
	}
	file.close();
	return 0;
}	
int read_customers_file(vector<Customer*>& customers){
	ifstream file("customers.txt");
	if(!file.is_open()){
		cout<<"i can not read \"customers.txt\"!"<<endl;
		return -1;
	}
	string temp;
	while(getline(file,temp)){
		if(temp.compare("\n") != -1){
			string name=find_first_item_file(temp,',');
			string phone=find_first_item_file(temp,',');
			string location=find_first_item_file(temp,',');
			customers.push_back(new Customer(name,location,phone));
		}
	}
	file.close();
	return 0;
}
void show_restaurants_list(vector<Restaurant*>& restaurants){
	for (int i = 0; i < restaurants.size(); ++i)
	{
		cout<<restaurants[i]->get_name()<<' '<<restaurants[i]->get_location()<<' '<<restaurants[i]->get_phone()<<endl;
	}
}
void show_restaurants_list_near(vector<Restaurant*>& restaurants,string location){
	for (int i = 0; i < restaurants.size(); ++i)
	{
		if (restaurants[i]->get_location() == location)
		{
			cout<<restaurants[i]->get_name()<<' '<<restaurants[i]->get_location()<<' '<<restaurants[i]->get_phone()<<endl;		
		}
	}
}
string find_customer_location_with_phone(vector<Customer*>& customers,string phone){
	for (int i = 0; i < customers.size(); ++i)
	{
		if(customers[i]->get_phone_number() == phone){
			return customers[i]->get_location();
		}
	}
	return " ";

}
int find_restaurant_with_phone(vector<Restaurant*>& restaurants,string phone){
	for (int i = 0; i < restaurants.size(); ++i)
	{
		if(restaurants[i]->get_phone() == phone){
			return i;
		}
	}
	return -1;
}
void show_near_restaurants_foods(vector<Restaurant*>& restaurants,string customer_location){
	for (int i = 0; i < restaurants.size(); ++i)
	{
		if(restaurants[i]->get_location() == customer_location){
			vector<Food*> foods=restaurants[i]->get_foods();
			for (int j = 0; j < foods.size(); ++j)
			{
				cout<<foods[j]->get_code()<<' '<<foods[j]->get_name()<<' '<<foods[j]->get_type()<<' '<<foods[j]->get_cost()<<' '<< restaurants[i]->get_name()<<' '<<restaurants[i]->get_location()<<endl;
			}
			continue;
		}
	}
}
void show_same_type_food(vector<Restaurant*>& restaurants,string type){
	for (int i = 0; i < restaurants.size(); ++i)
	{
		vector<Food*> foods=restaurants[i]->get_foods();
		for (int j = 0; j < foods.size(); ++j)
		{
			if(foods[j]->get_type() == type){
				cout<<foods[j]->get_code()<<' '<<foods[j]->get_name()<<' '<<foods[j]->get_type()<<' '<<foods[j]->get_cost()<<' '<< restaurants[i]->get_name()<<' '<<restaurants[i]->get_location()<<endl;	
			}
		}
		continue;
	}
}
bool valid_type(string type){
	if(type == "Iranian" || type =="European" || type == "Eastern"){
		return true;
	}
	return false;
}
Food* find_food_with_code(vector<Restaurant*>& restaurants,string food_code){
	string restaurant_phone;
	for (int i = 0; i < 8; ++i)
	{
		restaurant_phone.push_back(food_code[i]);
	}
	int index=find_restaurant_with_phone(restaurants,restaurant_phone);
	vector<Food*> foods=restaurants[index]->get_foods();
	for (int i = 0; i < foods.size(); ++i)
	{
		if(foods[i]->get_code() == food_code){
			return foods[i];
		}
	}
	cout<<"your food code is not correct!"<<endl;
	return NULL;
}
Customer* find_customer_with_phone(vector<Customer*>& customers,string customer_phone){
	for (int i = 0; i < customers.size(); ++i)
	{
		if(customers[i]->get_phone_number() == customer_phone){
			return customers[i];
		}
	}
	cout<<"I can not this phone number!"<<endl;
	return NULL;
}
bool find_personalization(string line){
	int found=line.find(' ');
	int last=line.find(' ',found+1);
	if(last == -1 || line[last+1] == '\n' || line[last+1] == ' '){
		return false;
	}
}
void show_food_in_order(vector<food_in_order*>& foods){
	for (int i = 0; i < foods.size(); ++i)
	{
		cout<<(foods[i]->food)->get_code()<<' '<<(foods[i]->food)->get_name()<<' '<<(foods[i]->food)->get_type()<<' '<<(foods[i]->food)->get_cost()<<' '<<foods[i]->number_of_food<<' '<<(foods[i]->food)->get_cost()*foods[i]->number_of_food<<' '<<foods[i]->personalization<<endl;
	}
}
void show_order(vector<Order*>& orders,Customer* order_owner){
	for (int i = orders.size()-1; i >= 0; i--)
	{
		if(orders[i]->get_owner_phone() == order_owner->get_phone_number()){
			cout<<orders[i]->get_owner_name()<<' '<<orders[i]->get_owner_phone()<<endl;
			vector<food_in_order*> foods=orders[i]->get_foods();
			show_food_in_order(foods);
			cout<<"delivery cost "<<orders[i]->get_delivery_cost()<<endl;
			cout<<"total cost "<<orders[i]->get_cost()+orders[i]->get_delivery_cost()<<endl;
			return;
		}
	}
}
void show_orders(vector<Order*>& orders,Customer* order_owner){
	bool first_order=true;
	int purchase=0;
	for (int i = 0; i < orders.size(); ++i)
	{
		if(orders[i]->get_owner_phone() == order_owner->get_phone_number()){
			if(first_order){
				cout<<orders[i]->get_owner_name()<<' '<<orders[i]->get_owner_phone()<<endl;
				vector<food_in_order*> foods=orders[i]->get_foods();
				show_food_in_order(foods);
				cout<<"delivery cost "<<orders[i]->get_delivery_cost()<<endl;
				cout<<"total cost "<<orders[i]->get_cost()+orders[i]->get_delivery_cost()<<endl;
				purchase+=orders[i]->get_cost()+orders[i]->get_delivery_cost();
				cout<<"#"<<endl;
				first_order=false;
			}
			else{
				vector<food_in_order*> foods=orders[i]->get_foods();
				show_food_in_order(foods);
				cout<<"delivery cost "<<orders[i]->get_delivery_cost()<<endl;
				cout<<"total cost "<<orders[i]->get_cost()+orders[i]->get_delivery_cost()<<endl;
				purchase+=orders[i]->get_cost()+orders[i]->get_delivery_cost();
				cout<<"#"<<endl;
			}
		}
	}
	cout<<"total purchase "<<purchase<<endl;
}
void do_command(vector<Order*>& orders,vector<Restaurant*>& restaurants,vector<Customer*>& customers,string line){
	string command=find_first_item_file(line,' ');
	if(command == "menu"){
		string phone=find_first_item_file(line,' ');
		int index=find_restaurant_with_phone(restaurants, phone);
		if(index == -1){
			cout<<"I can not find your phone number!"<<endl;
			return;
		}
		restaurants[index]->show_menu();
		return;
	}
	if(command == "restaurants"){
		string next_part=find_first_item_file(line,' ');
		if(next_part == "near"){
			string customer_phone=find_first_item_file(line,' ');
			string customer_location=find_customer_location_with_phone(customers,customer_phone);
			if(customer_location == " "){
				cout<<"I can not find your phone number!"<<endl;
				return;		
			}
			show_restaurants_list_near(restaurants,customer_location);
			return;
		}
		else{
			show_restaurants_list(restaurants);
			return;
		}
	}
	if(command == "list"){
		string next_part=find_first_item_file(line,' ');
		if(next_part == "near"){
			string customer_phone=find_first_item_file(line,' ');
			string customer_location=find_customer_location_with_phone(customers,customer_phone);
			if(customer_location == " "){
				cout<<"I can not find your phone number!"<<endl;
				return;		
			}
			show_near_restaurants_foods(restaurants,customer_location);
			return;
		}
		if(next_part =="type"){
			string type=find_first_item_file(line,' ');
			if(!valid_type(type)){
				cout<<"your type is invalid!"<<endl;
				return;
			}
			show_same_type_food(restaurants,type);
			return;

		}
	}
	if(command == "order"){
		string customer_phone=find_first_item_file(line,' ');
		Customer* order_owner=find_customer_with_phone(customers,customer_phone);
		if(order_owner == NULL){
			return;
		}
		Order* new_order=new Order(order_owner);
		string temp;
		while(getline(cin,temp)){
			if(temp == "$"){
				new_order->calculate_cost();
				calculate_delivery_cost(restaurants,new_order);
				cout<<new_order->get_owner_name()<<' '<<new_order->get_owner_phone()<<' '<<new_order->get_cost()+new_order->get_delivery_cost()<<endl;
				orders.push_back(new_order);
				break;
			}
			bool have_personalization=find_personalization(temp);
			string food_code=find_first_item_file(temp,' ');
			Food* food=find_food_with_code(restaurants,food_code);
			if (food == NULL){
				return;
			}
			string food_number=find_first_item_file(temp,' ');
			string personalization=" ";
			if(have_personalization){
				personalization=temp;
			}
			food_in_order* new_food_order=new food_in_order();
			new_food_order->food=food;
			new_food_order->number_of_food=atoi(food_number.c_str());
			new_food_order->personalization=personalization;
			new_order->add_food(new_food_order);

		}
	}
	if(command == "bill"){
		string next_part=find_first_item_file(line,' ');
		if(next_part == "all"){
			string customer_phone=find_first_item_file(line,' ');
			Customer* order_owner=find_customer_with_phone(customers,customer_phone);
			if(order_owner == NULL){
				return;
			}
			show_orders(orders,order_owner);
			return;
		}
		Customer* order_owner=find_customer_with_phone(customers,next_part);
		if(order_owner == NULL){
				return;
		}
		show_order(orders,order_owner);
		return;

	}
}
int main(){
	vector<Customer*> customers;
	if(read_customers_file(customers)==-1){
		return 0;
	}
	vector<Restaurant*> restaurants;
	if(read_restaurants_file(restaurants)== -1){
		return 0;
	}
	for (int i = 0; i < restaurants.size(); ++i)
	{
		cout<<i<<endl;
		cout<<restaurants[i]->get_name()<<' '<<restaurants[i]->get_phone()<<' '<<restaurants[i]->get_location()<<endl;
		restaurants[i]->show_menu();
	}
	vector<Order*> orders;
	string line;
	while(getline(cin,line)){
		do_command(orders,restaurants,customers, line);
	}
	/*
	vector<int> nums;
	vector<Restaurant*> restaurants;
	if(read_restaurants_file(restaurants)== -1){
		return 0;
	}
	for (int i = 0; i < restaurants.size(); ++i)
	{
		cout<<i<<endl;
		cout<<restaurants[i]->get_name()<<' '<<restaurants[i]->get_phone()<<' '<<restaurants[i]->get_location()<<endl;
		restaurants[i]->show_menu();
	}
	nums.push_back(1);
	std::vector<Food*> foods;
	foods.push_back((new Food("22038055001","Kabab","Iranian","10000")));
	Order* order=new Order(customers[0],foods,nums);
	order->calculate_cost();
	calculate_delivery_cost(restaurants,order);
	cout<<"delivery_cost :"<<order->get_delivery_cost()<<endl;
	cout<<order->get_owner_name()<<' '<<order->get_owner_phone()<<' '<<order->get_cost()<<endl;
	*/
}