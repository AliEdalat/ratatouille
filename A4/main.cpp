#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <algorithm>
#include "food.h"
#include "restaurant.h"
#include "order.h"
#include "customer.h"

#define RESTAURANT_PHONE_LENGTH 8


using namespace std;
int find_restaurant_with_phone(vector<Restaurant*>& restaurants,string phone);
string show_phone_number(string phone_number){
	string result;
	if(phone_number[0] == '0'){
		for (int i = 0; i < phone_number.size(); ++i)
		{
			if(phone_number[i] != '0'){
				result=phone_number.substr(i);
				break;
			}
		}
	}
	else{
		result=phone_number;
	}
	return result;
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
bool compare(Restaurant* restaurant1,Restaurant* restaurant2){
	return restaurant1->get_phone()<restaurant2->get_phone();
}
int read_restaurants_file(vector<Restaurant*>& restaurants){
	ifstream file("restaurants.txt");
	if(!file.is_open()){
		cout<<"i can not read \"restaurants.txt\"!"<<endl;
		return -1;
	}
	string temp;
	int line_counter=0;
	Restaurant* new_restaurant;
	while(getline(file,temp)){
		line_counter++;
		
		if(line_counter ==1 && temp.compare("\n") != -1){
			string name=find_first_item_file(temp,',');
			string phone=find_first_item_file(temp,',');
			string location=find_first_item_file(temp,',');
			new_restaurant=new Restaurant(name,phone,location);
		}
		if(line_counter !=1 && temp.compare("\n") != -1){
			string code=find_first_item_file(temp,',');

			string food_code_com=new_restaurant->get_phone();
			for (int i = 0; i < code.size(); ++i)
			{
				food_code_com.push_back(code[i]);
			}

			string name=find_first_item_file(temp,',');
			string type=find_first_item_file(temp,',');
			string cost=find_first_item_file(temp,',');
			new_restaurant->add_food(new Food(food_code_com,name,type,cost));
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
	sort(restaurants.begin(),restaurants.end(),compare);
	for (int i = 0; i < restaurants.size(); ++i)
	{
		restaurants[i]->sort_foods_in_menu();
	}
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
			
			restaurants[i]->show_foods_list();
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
	for (int i = 0; i < RESTAURANT_PHONE_LENGTH; ++i)
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
	cout<<"I can not find this phone number!"<<endl;
	return NULL;
}
bool find_personalization(string line){
	int found=line.find(' ');
	int last=line.find(' ',found+1);
	if(last == -1 || line[last+1] == '\n' || line[last+1] == ' '){
		return false;
	}
	return true;
}
void show_food_in_order(vector<food_in_order*>& foods){
	for (int i = 0; i < foods.size(); ++i)
	{
		if((foods[i]->personalization).compare(" ") != 0){
			cout<<(foods[i]->food)->get_code()<<' '<<(foods[i]->food)->get_name()<<' '<<(foods[i]->food)->get_type()<<' '<<(foods[i]->food)->get_cost()<<' '<<foods[i]->number_of_food<<' '<<(foods[i]->food)->get_cost()*foods[i]->number_of_food<<' '<<foods[i]->personalization<<endl;
		}
		else{
			cout<<(foods[i]->food)->get_code()<<' '<<(foods[i]->food)->get_name()<<' '<<(foods[i]->food)->get_type()<<' '<<(foods[i]->food)->get_cost()<<' '<<foods[i]->number_of_food<<' '<<(foods[i]->food)->get_cost()*foods[i]->number_of_food<<endl;	
		}
	}
}
void show_order(vector<Order*>& orders,Customer* order_owner){
	for (int i = orders.size()-1; i >= 0; i--)
	{
		if(orders[i]->get_owner_phone() == order_owner->get_phone_number()){
			cout<<orders[i]->get_owner_name()<<' '<<show_phone_number(orders[i]->get_owner_phone())<<endl;
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
				cout<<orders[i]->get_owner_name()<<' '<<show_phone_number(orders[i]->get_owner_phone())<<endl;
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
void bill_command(string line,vector<Order*>& orders,vector<Customer*>& customers){
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
void list_command(string line,vector<Restaurant*>& restaurants,vector<Customer*>& customers){
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
void menu_command(string line,vector<Restaurant*>& restaurants){
		string phone=find_first_item_file(line,' ');
		int index=find_restaurant_with_phone(restaurants, phone);
		if(index == -1){
			cout<<"I can not find your phone number!"<<endl;
			return;
		}
		restaurants[index]->show_menu();
		return;
}
void restaurants_command(string line,vector<Restaurant*>& restaurants,vector<Customer*>& customers){
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
void add_food_to_order(string temp,vector<Restaurant*>& restaurants,Order* new_order){
		bool have_personalization=find_personalization(temp);
		string food_code=find_first_item_file(temp,' ');
		Food* food=find_food_with_code(restaurants,food_code);
		if (food == NULL){
			throw 0;
		}
		string food_number=find_first_item_file(temp,' ');
		for (int i = 0; i < food_number.size(); ++i)
		{
			if(food_number[i] <48 || food_number[i]>57){
				cout<<"food number is not correct!"<<endl;
				throw -1;
			}
		}
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
void order_command(string line,vector<Restaurant*>& restaurants,vector<Customer*>& customers,vector<Order*>& orders){
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
				new_order->calculate_delivery_cost(restaurants);
				cout<<new_order->get_owner_name()<<' '<<show_phone_number(new_order->get_owner_phone())<<' '<<new_order->get_cost()+new_order->get_delivery_cost()<<endl;
				orders.push_back(new_order);
				break;
			}
			try{
				add_food_to_order(temp,restaurants,new_order);
			}catch(int error){
				if(error == 0){
					cout<<"correct your food code"<<endl;
					continue;
				}
			}catch(int error){
				if(error == -1){
					cout<<"correct your food number"<<endl;
					continue;
				}
			}

		}
}
bool valid_restaurant_number(string number){
	for (int i = 0; i < number.size(); ++i)
	{
		if(i >0 && (number[i] < 48 || number[i]>57) ){
			return false;
		}
		if(i == 0 && (number[i] <= 48 || number[i] > 57)){
			return false;
		}
	}
	if(number.size() == 8){
		return true;
	}
	else{
		return false;
	}
}
int find_spaces(string line){
	int spaces=0;
	for (int i = 0; i < line.size(); ++i)
	{
		if(line[i] == ' '){
			spaces++;
		}
	}
	return spaces;
}
bool valid_menu_command(string line){
	int spaces=find_spaces(line);
	if(spaces == 1){
		int found=line.find(' ');
		string s1=line.substr(0,found);
		string s2=line.substr(found+1);
		if(s1 == "menu" && valid_restaurant_number(s2)){
			return true;
		}
	}
	cout<<"phone_number is not correct!"<<endl;
	return false;
}
bool valid_customer_number(string number){
	for (int i = 0; i < number.size(); ++i)
	{
		if(number[i] < 48 || number[i]>57){
			return false;
		}
	}
	return true;
}
bool valid_restaurants_command(string line){
	int found=line.find("near");
	if(found == -1){
		if(line == "restaurants"){
			return true;
		}
		return false;
	}
	else{
		int spaces=find_spaces(line);
		if(spaces == 2){
			int first=line.find(' ');
			first=line.find(' ',first+1);
			string temp=line.substr(first+1);
			if(valid_customer_number(temp)){
				return true;
			}
			else{
				cout<<"phone_number is not correct!"<<endl;
				return false;
			}
		}
	}
}
string find_third_part(string line){
		int first=line.find(' ');
		first=line.find(' ',first+1);
		string temp=line.substr(first+1);
		return temp;
}
bool valid_list_command(string line){
	int spaces=find_spaces(line);
	if(spaces == 2){
		int find=line.find("near");
		if(find != -1){
			string temp=find_third_part(line);
			if(valid_customer_number(temp)){
				return true;
			}
			else{
				cout<<"phone_number is not correct!"<<endl;
				return false;
			}
		}
		find=line.find("type");
		if(find != -1){
			string temp=find_third_part(line);
			if (valid_type(temp))
			{
				return true;
			}
			else{
				cout<<" type is not correct!"<<endl;
				return false;
			}
		}
	}
	else{
		return false;
	}
}
bool valid_order_command(string line){
	int spaces=find_spaces(line);
	if(spaces == 1){
		int found=line.find(' ');
		string phone_number=line.substr(found+1);
		if(valid_customer_number(phone_number)){
			return true;
		}else{
			return false;
		}
	}
	return false;
}
bool valid_bill_command(string line){
	int spaces=find_spaces(line);
	if (spaces == 1)
	{
		int found=line.find(' ');
		string phone_number=line.substr(found+1);
		if(valid_customer_number(phone_number)){
			return true;
		}else{
			return false;
		}
	}
	if(spaces == 2){
		string phone_number=find_third_part(line);
		if(valid_customer_number(phone_number)){
			return true;
		}else{
			return false;
		}
	}
	return false;
}
void do_command(vector<Order*>& orders,vector<Restaurant*>& restaurants,vector<Customer*>& customers,string line){
	string temp=line;
	string command=find_first_item_file(line,' ');
	if(command == "menu"){
		if(valid_menu_command(temp)){
			menu_command(line,restaurants);
		}
		else{
			cout<<" menu command is not correct!"<<endl;
		}
		return;
	}
	if(command == "restaurants"){
		if(valid_restaurants_command(temp)){
			restaurants_command(line,restaurants,customers);

		}
		else{
			cout<<"restaurants command is not correct!"<<endl;
		}
		return;
	}
	if(command == "list"){
		if(valid_list_command(temp)){
			list_command(line,restaurants,customers);
		}
		else{
			cout<<" list command is not correct!"<<endl;
		}
		return;
	}
	if(command == "order"){
		if(valid_order_command(temp)){
			order_command(line,restaurants,customers,orders);
		}else{
			cout<<"order command is not correct!"<<endl;
		}
		return;
	}
	if(command == "bill"){
		if(valid_bill_command(temp)){
			bill_command(line,orders,customers);
		}else{
			cout<<"bill command is not correct!"<<endl;
		}
		return;
	}
	cout<<"your command is not valid!"<<endl;
	return;
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
	vector<Order*> orders;
	string line;
	while(getline(cin,line)){
		do_command(orders,restaurants,customers, line);
	}
}