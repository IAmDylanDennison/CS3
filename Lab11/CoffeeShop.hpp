//Dylan Dennison
//Lab 11
//04/09/21

#ifndef COFFEESHOP_H
#define COFFEESHOP_H

#include "Drink.hpp"
#include <set>

//observer and chain of command

//observer class for observer design pattern 
class Customer {
public:
	Customer() { cout << ""; } // default ctor had errors without
	Customer(class Barista* b); //ctor for customer and forward dec of Barista class

	virtual void notify() const = 0; //pure for notifing customers 

};

class Barista {
public:

	void regCustomer(Customer* c) { //inserts into set
		custormers_.insert(c);
	}

	void dRegCustomer(Customer* c) { //removes from set
		custormers_.erase(c);
	}

	void notifyCustomer() const { //notifies all customers in the set
		for (auto c : custormers_) {
			c->notify();
		}
	}

	int getCSize() { //returns size of the set
		return custormers_.size(); 
	}

private:
	std::set<Customer*> custormers_; //cant be modified and every value has to be unique

};

Customer::Customer(Barista* b) {
	b->regCustomer(this);
}

class concreteBarista; //forward dec

//concrete 
class concreteCustomer :public Customer {
public:
	concreteCustomer(const string& name, concreteBarista* barista, Drink* drink);  //ctor
	 

	concreteCustomer() : name_(""), order_(nullptr), b(nullptr) {} //default 

	void notify() const override; //notify customer
	

	string orderName() { //returns order name
		return order_->getName();
	}

	string getName() { return name_; } // getter
	void setName(const string& name) { name_ = name; } //setter
	void setDrink(Drink* d) { order_ = d; } //setter
	void setBarista(concreteBarista* barista) { b = barista; }//setter
private:
	string name_; //for customer name 
	Drink* order_; //for there order
	concreteBarista* b; // for chain of command 

};

//concrete subject
class concreteBarista : public Barista {
public: 
	concreteBarista(concreteBarista* b) : successor_(b) {} //ctor 

	void drinkMade(const string drink, const string name) { // notify customers that drink is made 
		drink_ = drink;
		customerName_ = name;
		notifyCustomer();
	}

	string getDrink() { return drink_; } //getter for drink name
	string getCustomerName() { return customerName_; } //getter for customer name 
	virtual void handleRequest(const string drink) { //handles request and passes it on for each handler 
		if (successor_ != nullptr) {
			successor_->handleRequest(drink);
		}
		else {
			cout << "no employee can make this drink. " << endl;
		}
	}

private:
	string customerName_; //name of customer 
	string drink_; //drink that is being made
	concreteBarista* successor_; //pointer to the barista successor 
};

concreteCustomer::concreteCustomer(const string& name, concreteBarista* barista, Drink* drink)  //ctor for some reason has to be after the concrete barista class
	: name_(name), b(barista), order_(drink), Customer(static_cast<Barista*>(b)) {}


class juniorBarista : public concreteBarista {
public:

	juniorBarista(concreteBarista* successor = nullptr) : concreteBarista(successor) {} //ctor

	void handleRequest(const string drink) override {
		size_t use = drink.find("with"); //this is pretty cool
		if (use == string::npos) { //npos means it was not found so the junior barista can make it 
			cout << "The Junior Barista will be preparing your drink. " << endl;
		}
		else {
			concreteBarista::handleRequest(drink); //will pass the handle request if with is found
		}
	}


};

class seniorBarista : public concreteBarista {
public:

	seniorBarista(concreteBarista* successor = nullptr) : concreteBarista(successor) {} //ctor

	void handleRequest(const string drink) override {
		size_t use = drink.find("foam"); //this is pretty cool
		if (use == string::npos) { //npos means it was not found so the senior barista can make it 
			cout << "The Senior Barista will be preparing your drink. " << endl;
		}
		else {
			concreteBarista::handleRequest(drink); //will pass the handle request if with is found
		}
	}


};

class Manager : public concreteBarista {
public:
	Manager(concreteBarista* successor = nullptr) : concreteBarista(successor) {} //ctor

	void handleRequest(const string drink) override { //last handler so it will just cout making the drink 
		cout << "The Manager will be preparing your drink. " << endl;
	}

};

void concreteCustomer::notify() const { //notify customer
	if (order_ != nullptr) {
		if (name_ == b->getCustomerName()) { // if barista drink made is the same as the customers it will print
			cout << name_ << " , your order of a " << order_->getName() << " is ready. That will be " << order_->getPrice()<< " Dollars." << endl << endl;
		}
	}
}

#endif
