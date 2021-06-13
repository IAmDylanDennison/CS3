// demoes hashmap implementation
// Mikhail Nesterenko
// 4/15/2014

#include "hashmap.hpp" //change to hpp
#include <iostream>
#include <string>

using std::cin; using std::cout; using std::endl;
using std::string;

int main() {
	hashmap<int, int> myHash;
	myHash.insert(pair<int, int>(4, 40));
	myHash.insert(pair<int, int>(7, 25));
	myHash.insert(pair<int, int>(6, 77));
	myHash.insert(pair<int, int>(1, 10));

	auto safe = myHash.insert(pair<int, int>(3, 45));
	auto safe2 = myHash.insert(pair<int, int>(11, 88));

	// testing safe insert
	if (safe.second) {
		cout << "Pair(3,45) inserted safely" << endl;
	}
	else {
		cout << "Pair(3,45) not inserted safely" << endl;
	}

	//tesing insert again
	if (safe2.second) {
		cout << "Pair(11,88) inserted safely" << endl;
	}
	else {
		cout << "Pair(11,88) not inserted safely" << endl;
	}

	// tesing deleting an element that is already in the hash
	auto safeD = myHash.erase(7);

	if (safeD.second) {
		cout << "key 7 deleted safely" << endl;
	}
	else {
		cout << "Key 7 not found and not deleted" << endl;
	}

	// testing deleting an element that is not in the hash table 

	auto safeD2 = myHash.erase(9);
	if (safeD2.second) {
		cout << "key 9 deleted safely" << endl;
	}
	else {
		cout << "Key 9 not found and not deleted" << endl;
	}

	//tesing rehash
	myHash.rehash(15);

}
