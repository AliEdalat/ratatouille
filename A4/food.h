#ifndef FOOD_H
#define FOOD_H

#include <iostream>


class Food
 {
 public:
 	Food(std::string code,std::string name,std::string type,std::string cost);
 	int get_cost(){return dish_cost;}
 	std::string get_type(){return food_type;}
 	std::string get_name(){return food_name;}
 	std::string get_code(){return food_code;}
 	~Food();
 private:
 	std::string food_code;
 	std::string food_name;
 	std::string food_type;
 	int dish_cost;
 	
 }; 

 #endif
