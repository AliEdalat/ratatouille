#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <iostream>


class Customer
{
public:
	Customer(std::string name,std::string location,std::string phone_number);
	std::string get_phone_number(){return customer_phone;}
	std::string get_name(){return customer_name;}
	std::string get_location(){return customer_location;}
	~Customer();
private:
	std::string customer_name;
	std::string customer_phone;
	std::string customer_location;
	
	
};

#endif