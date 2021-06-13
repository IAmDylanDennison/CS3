// sorting apples
// non STL-algorithm code to be replaced by algorthms
//Dylan Dennison
//03/05/21


#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <deque>
#include <string>
#include <algorithm>
#include <iterator>
#include <functional>


using std::cin; using std::cout; using std::endl;
using std::string;
using std::vector; using std::deque;

struct Apples {
	Apples() {
		weight = 0;
		color = " ";
	}
	double weight; // oz
	string color;  // red or green
	void print() const { cout << color << ", " << weight << endl; }
};


int main() {

	srand(time(nullptr));
	const double minWeight = 3.;
	const double maxWeight = 8.;

	cout << "Input crate size: ";
	int size;
	cin >> size;

	vector <Apples> crate(size);

	// assign random weight and color to apples in the crate
	// replace with generate()

	std::generate(crate.begin(), crate.end(), [minWeight, maxWeight]() {
		Apples a;
		a.weight = minWeight +
			static_cast<double>(rand()) / RAND_MAX * (maxWeight - minWeight);
		a.color = rand() % 2 == 1 ? "green" : "red";
		return a;
		}); //used a fp for practice

	cout << "Enter weight to find: ";
	double toFind;
	cin >> toFind;

	// count_if()
	int cnt = std::count_if(crate.begin(), crate.end(), [toFind](Apples a) {return a.weight > toFind; });

	cout << "There are " << cnt << " apples heavier than "
		<< toFind << " oz" << endl;
	cout << endl;


	// find_if()
	auto it = std::find_if(crate.begin(), crate.end(), [toFind](Apples a) {return a.weight > toFind; }); 
		if (it != crate.end()) {
			cout << "At positions ";
			while(it != crate.end()) {
				cout << it - crate.begin() << ", ";
				it = std::find_if(++it, crate.end(), [toFind](Apples a) {return a.weight > toFind; });
			}
		}
		cout << endl;


	// max_element()
	it = std::max_element(crate.begin(), crate.end(), [](Apples x, Apples y) {return x.weight < y.weight;});
	cout << "Heaviest apple weighs: " << it->weight << " oz" << endl;
	cout << endl;


	// for_each() or accumulate()
	double totalW = 0;
	std::for_each(crate.begin(), crate.end(), [&totalW](Apples a) { return totalW += a.weight; });
	cout << "Total apple weight is: " << totalW << " oz" << endl;
	cout << endl;


	// transform();
	cout << "How much should they grow: ";
	double toGrow;
	cin >> toGrow;
	std::transform(crate.begin(), crate.end(), crate.begin(), [toGrow](Apples a) -> Apples{
		Apples t;
		t.color = a.color;
		t.weight = a.weight + toGrow;
		return t; });
	cout << endl;


	// remove_if()
	cout << "Input minimum acceptable weight: ";
	double minAccept;
	cin >> minAccept;

	crate.erase(std::remove_if(crate.begin(), crate.end(), [minAccept](Apples &a) {return a.weight < minAccept;}), crate.end());
	cout << "removed " << size - crate.size() << " elements" << endl;
	cout << endl;


	// bubble sort, replace with sort()
	std::sort(crate.begin(), crate.end(), [](Apples x, Apples y) {return x.weight < y.weight;});


	// moving all red apples from crate to peck
	// remove_copy_if() with back_inserter()/front_inserter() or equivalents
	deque<Apples> peck(size);
	std::remove_copy_if(crate.begin(), crate.end(), std::front_inserter(peck), [=](Apples a) {return a.color != "red"; });
	crate.erase(std::remove_if(crate.begin(), crate.end(), [=](Apples a) {return a.color == "red"; }), crate.end());



	// for_each() possibly
	cout << "apples in the create" << endl;
	std::for_each(crate.begin(), crate.end(), [=](Apples &a) {a.print();});
	cout << endl;

	// for_each() possibly
	cout << "apples in the peck" << endl;
	std::for_each(peck.begin(), peck.end(), [=](Apples &a) {if(a.weight != 0) a.print();});
	cout << endl;



	// prints every "space" apple in the peck
	//
	const int space = 3;
	cout << "\nevery " << space << "\'d apple in the peck" << endl;

	// replace with advance()/next()/distance()
	// no iterator arithmetic

	int x = 1;
	auto e = peck.begin();
	//bool flag = false;
	while (e != peck.end()) {
		if (x % space == 0 && e->weight != 0)
			e->print();

		std::advance(e, 1);
		x++;
	}

	cout << endl;
	// putting all small green apples in a jam
	// use a binder to create a functor with configurable max weight
	// accumulate() or count_if() then remove_if()

	class functor {
	public:
		functor() { jamWeight = 0; };
		double operator() (vector<Apples> a, double maxJamWeight) {
			for (auto &jam : a) {
				if (jam.weight < maxJamWeight) {
					jamWeight += jam.weight;
				}
			}
			return jamWeight;
		}

	private:
		double jamWeight;
	};
	const double weightToJam = 10.0;

	functor jam;
	auto bindJam = std::bind(jam, crate, weightToJam);

	cout << "Weight of jam is: " << bindJam() << endl;

}

