// needed for lab
// Dylan Dennison
// 3/26/21

#include <iostream>
#include <vector>
#include <cstdlib>
#include "CarFactory.hpp"

using std::vector;
using std::cout; using std::endl;

class CarLot {
public:
	CarLot();

	// if a car is bought, requests a new one
	Car* buyCar() {
		Car* bought = &car4sale_[nextC_];
		car4sale_[nextC_] =
			*(factories_[rand() % factories_.size()]->requestCar());
		return bought;
	}

	Car* nextCar() {
		nextC_++;  // advances in array
		if (nextC_ == lotSize_) { // if at the end of the lot reset next car to 0
			nextC_ = 0;
		}
			Car* newCar = &car4sale_[nextC_];  // returns the car in the postion of next car
			return newCar;
	}

	int lotSize() {
		return lotSize_;  // returns size of lot
	}


private:
	static int nextC_;  //next car
	static const int lotSize_ = 10; //car lot size
	Car car4sale_[lotSize_]; // cars for sale
	vector<CarFactory*> factories_;
};

int CarLot::nextC_ = -1;// has to be -1 becaue lover functions call next car right away

//default ctor
CarLot::CarLot() {
	// creates 2 Ford factories and 2 Toyota factories
	factories_.push_back(new FordFactory());
	factories_.push_back(new ToyotaFactory());
	factories_.push_back(new FordFactory());
	factories_.push_back(new ToyotaFactory());

	// fills car lot
	for (int i = 0; i < lotSize_; ++i) {
		car4sale_[i] = *(factories_[rand() % factories_.size()]->requestCar());
	}
}



CarLot* carLotPtr = nullptr; // global pointer instantiation

// test-drives cars in the lot
// buys it if it finds the exact car wanted
void toyotaLover(int id) {
	bool bought = false;
	Car* wantedCar = new Toyota();
	cout << "Buyer wants " << wantedCar->getMake() << " " << wantedCar->getModel() << endl;
	if (carLotPtr == nullptr)
		carLotPtr = new CarLot();

	for (int i = 0; i < carLotPtr->lotSize(); ++i) {
		if(!bought) {
			Car* toBuy = carLotPtr->nextCar();
			cout << "Buyer " << id << endl;
			cout << "test driving "
				<< toBuy->getMake() << " "
				<< toBuy->getModel();


			if (toBuy->getModel() == wantedCar->getModel()) {
				cout << " love it! buying it!" << endl << endl;
				carLotPtr->buyCar();
				bought = true;
				delete wantedCar;
			}
			else
				cout << " did not like it!" << endl;
		}
	}

	if (!bought) {
		cout << endl << "I did not find a Car I like, I'm leaving" << endl << endl;
	}


}

// test-drives cares in the lot
// buys it if it finds the exact car wanted
void fordLover(int id) {

	bool bought = false;
	Car* wantedCar = new Ford();
	cout << "Buyer wants " << wantedCar->getMake() << " " << wantedCar->getModel() << endl;
	if (carLotPtr == nullptr)
		carLotPtr = new CarLot();

	for (int i = 0; i < carLotPtr->lotSize(); ++i) {

		if(!bought) {
			Car* toBuy = carLotPtr->nextCar();
			cout << "Buyer " << id << endl;
			cout << "test driving "
				<< toBuy->getMake() << " "
				<< toBuy->getModel();

			if (toBuy->getModel() == wantedCar->getModel()) {
				cout << " love it! buying it!" << endl << endl;
				carLotPtr->buyCar();
				bought = true;
				delete wantedCar;
			}
			else
				cout << " did not like it!" << endl;
		}
	}

	if (!bought) {
		cout << endl << "I did not find a Car I like, I'm leaving" << endl << endl;
	}
}



int main() {
	srand(time(nullptr));

	const int numBuyers = 10;
	for (int i = 1; i < numBuyers+1; ++i)
		if (rand() % 2 == 0)
			toyotaLover(i);
		else
			fordLover(i);

}
