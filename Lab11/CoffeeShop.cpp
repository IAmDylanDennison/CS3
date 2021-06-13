//Dylan Dennison
//Lab 11
//04/09/21

#include "CoffeeShop.hpp"
#include "Drink.hpp"


int main() {

	std::vector<concreteCustomer> customerList; //for customers 
	std::vector<string> orderList; //for order count
	double price = 0;
	concreteBarista* baristaChoice = new juniorBarista(new seniorBarista(new Manager)); //for chain of command
	int i = 0; //index
	string name;
	string order = "";
	

	bool flag = true;
	while (flag) {
		
		
		
		Drink* drink = new Drink; //new drink for the customer 

		bool flag2 = true;

		if (flag2) {
			
			char size;
			char topping;
			//getting size
			cout << "Welcome to Coffee Shack, can I get you [l]arge, [m]edium, or [s]mall coffee?" << endl;
			cin >> size;
			drink->setSize(size);
			price = drink->getPrice();
			order = drink->getName();

			do { //getting toppings
				cout << "Would you like to add [s]prinkles, [c]aramel, milk [f]oam, [i]ce or [n]ot?" << endl;
				cin >> topping;
				switch (topping) { //decorator adding
					case 's': {
						Sprinkles s(drink);
						price += drink->getPrice();
						order += drink->getName();
						break;
					}
					case 'c': {
						Caramel c(drink);
						price += drink->getPrice();
						order += drink->getName();
						break;
				
					}
					case 'f': {
						Foam f(drink);
						price += drink->getPrice();
						order += drink->getName();
						break;
					
					}
					case 'i': {
						Ice ice(drink);
						price += drink->getPrice();
						order += drink->getName();
						break;	
					}

				}

			} while (topping != 'n');

			drink->setDrinkName(order);
			drink->setPrice(price); //setting for drink obj

			cout << "Can I get your name?" << endl;
			cin >> name;
			
			concreteCustomer c;
			c.setName(name);
			c.setBarista(baristaChoice);
			c.setDrink(drink);
			customerList.push_back(c);//push back into deque of customers
			baristaChoice->regCustomer(&c); //putting customer into set for handlers
			
			orderList.push_back(order); //putting into deque for orders
			order = ""; //reseting the string
			++i;
			if (i == 1) {
				flag2 = false;
			}
			
		}
		if (!flag2) {
				baristaChoice->handleRequest(orderList.front());
				baristaChoice->drinkMade(orderList.front(), customerList.front().getName()); // I cant get this to work correctly for some reason!!!
				baristaChoice->dRegCustomer(&customerList.front());

			

				customerList.erase(customerList.begin()); //removes from container of customers

			
			flag2 = true;
			flag = false;
		}
		delete drink;

	}
	
	delete baristaChoice;
}
