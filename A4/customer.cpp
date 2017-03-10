#include <iostream>
#include "customer.h"

using namespace std;


Customer::Customer(string name,string location,string phone_number){
	customer_phone=phone_number;
	customer_location=location;
	customer_name=name;

}