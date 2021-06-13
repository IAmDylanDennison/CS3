// sorting oranges
// converting vectors to multimaps
// Mikhail Nesterenko
// 2/17/2020
//Dylan Dennison


#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <deque>
#include <string>
#include <map>

using std::cin; using std::cout; using std::endl;
using std::string;
using std::vector;
using std::multimap;

enum class Variety { orange, pear, apple };
vector<string> colors = { "red", "green", "yellow" };

struct Fruit {
	Variety v;
	string color; // red, green or orange
};


int main() {

	//vector <Fruit> tree(rand() % 100 + 1);
	srand(time(nullptr));
	multimap<Variety, string> tree;
	int max = rand() % 100 + 1;
	for (int i = 1; i < max; ++i) {
		tree.emplace(make_pair(static_cast<Variety>(rand() % 3), colors[rand() % 3]));
	}

	/*for (auto f = tree.begin(); f != tree.end(); ++f) {
		f->v = static_cast<Variety>(rand() % 3);
		f->color = colors[rand() % 3];
	}

	cout << "Colors of the oranges: ";
	for (auto f = tree.begin(); f != tree.end(); ++f)
		if (f->v == Variety::orange) cout << f->color << ", ";
	cout << endl;
	*/

	cout << "Colors of the Oranges: ";
	for (auto it = tree.lower_bound(Variety::orange); it != tree.upper_bound(Variety::orange); ++it)
	 cout << it->second << ", ";
	cout << endl;


}
