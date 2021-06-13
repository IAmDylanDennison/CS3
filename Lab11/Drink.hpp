//drink header file
//dylan dennison
#ifndef DRINK_H
#define DRINK_H

#include <iostream>
#include <string>
#include <vector>

//decorator 
using std::string; using std::cin; using std::cout; using std::endl;

enum class DrinkType { small, medium, large };

class Drink {
public:
	Drink(DrinkType type = DrinkType::small, double price = 0) :
		type_(type), price_(price) {}

	virtual double getPrice() const { //returns price
		return price_;
	}

	virtual string getName() const { //returns name 
		return name_;
	}

	int getTopppings() { return toppings_; } //returns number of toppings

	void addTopping() { ++toppings_; } //increment topping 
	void setDrinkName(const string name) { name_ = name; } //sets drink name
	void setPrice(const double price) { price_ = price; } //sets price
	//string getOrderName() { return name_; }
	//double getOrderPrice() { return price_; }
	string getSize() { return size_; } // getter for size

	void setSize(const char size) { //sets size with case switch
		switch (size)
		{
		case 's':
			type_ = DrinkType::small;
			size_ = "small";
			price_ = 1.00;
			name_ = size_ + " coffee";
			break;

		case 'm':
			type_ = DrinkType::medium;
			size_ = "medium";
			price_ = 2.00;
			name_ = size_ + " coffee";
			break;

		case 'l':
			type_ = DrinkType::large;
			size_ = "large";
			price_ = 3.00;
			name_ = size_ + " coffee";
			break;
		}
	}




private:
	double price_; //price
	DrinkType type_; //type
	string name_; //for name of drink
	string size_; //size
	int toppings_ = 0; //number of toppings
};

//classes for each topping for decorator 

class Sprinkles : public Drink {
public:
	Sprinkles(Drink* drink) : drink_(drink) {} //ctor

	double getPrice() const override { return 0.5; } //returns price of sprinkles

	//returns first statement if the coffee already had toppings, the else if it has no toppings
	string getName() const override {
		if (drink_->getTopppings() > 0) {
			drink_->addTopping();
			return ", sprinkles";

		}
		else {
			drink_->addTopping();
			return " with sprinkles";
		}
	}

private:
	Drink* drink_;
};

//same for the rest of the topping classes
class Caramel : public Drink {
public:
	Caramel(Drink* drink) : drink_(drink) {}

	double getPrice() const override { return 0.2; }

	string getName() const override {
		if (drink_->getTopppings() > 0) {
			drink_->addTopping();
			return ", caramel";

		}
		else {
			drink_->addTopping();
			return " with caramel";
		}
	}

private:
	Drink* drink_;
};


class Foam : public Drink {
public:
	Foam(Drink* drink) : drink_(drink) {}

	double getPrice()const override { return 0.4; }

	string getName() const override {
		if (drink_->getTopppings() > 0) {
			drink_->addTopping();
			return ", foam";

		}
		else {
			drink_->addTopping();
			return " with foam";
		}
	}


private:
	Drink* drink_;
};


class Ice : public Drink {
public:
	Ice(Drink* drink) : drink_(drink) {}

	double getPrice() const override { return 0.1; }

	string getName() const override {
		if (drink_->getTopppings() > 0) {
			drink_->addTopping();
			return ", ice";

		}
		else {
			drink_->addTopping();
			return " with ice";
		}
	}

private:
	Drink* drink_;
};

#endif


