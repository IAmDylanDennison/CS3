// implementation basic hashmap (unordered container)
// Dylan Dennison: adapted from Proc C++
// 03/12/21

#include <cstddef>
#include <utility>
#include <functional>
#include <vector>
#include <list>
#include <iterator>
#include <iostream>


using std::vector;
using std::list;
using std::pair;
using std::make_pair;

//////////////////////////////////////////
// hash function implemented as a class
//////////////////////////////////////////

// any Hash Class must provide 
// two methods: hash() and numBuckets().
template <typename T>
class DefaultHash {
public:
	DefaultHash(size_t numBuckets = defaultNumBuckets); 
		size_t hash(const T & key) const;
	size_t numBuckets() const { return numBuckets_; }

private:
	// default number of buckets in the hash
	static const size_t defaultNumBuckets = 101;
	size_t numBuckets_;
};

template <typename T>
DefaultHash<T>::DefaultHash(size_t numBuckets) : numBuckets_(numBuckets) {}


// uses the division method for hashing.
// treats the key as a sequence of bytes, sums the ASCII
// values of the bytes, and mods the total by the number
// of buckets.
// note, this function does not work for C++ strings
template <typename T>
size_t DefaultHash<T>::hash(const T& key) const {
	size_t res = 0;
	for (size_t i = 0; i < sizeof(key); ++i) {
		const unsigned char b =
			*(reinterpret_cast<const unsigned char*>(&key) + i);
		res += b;
	}
	return res % numBuckets_;
}


////////////////////////////////////////////////
// container class
////////////////////////////////////////////////

template <typename Key, typename Value,
	typename Compare = std::equal_to<Key>,
	typename Hash = DefaultHash<Key>>
	class hashmap {

	public:
		typedef pair<const Key, Value> Element;

		// constructor
		// invokes constructors for comparison and hash objects
		hashmap(const Compare& comp = Compare(),
			const Hash& hash = Hash());

		Element* find(const Key& x);      // returns pointer to element with key x,
										  // nullptr if not found
		pair<Element*, bool> insert(const Element& x);    // inserts the key/value pair 
		pair<Element*, bool> erase(const Key& x);         // erases element with key x, if exists
		Value& operator[] (const Key& x); // returns reference on value of
										  // element with key, inserts if does not exist

		void rehash(size_t n);
	private:

		// helper function for various searches
		typename list<Element>::iterator findElement(const Key& x, const size_t bucket);

		size_t size_;   // number of elements in the container
		Compare comp_;  // comparison functor, equal_to by default
		Hash hash_;     // hash functor 

		// hash contents: vector of buckets
		// each bucket is a list containing key->value pairs
		vector<list<Element>> elems_;
};


////////////////////////////////////////////////
// container member functions
////////////////////////////////////////////////

// Construct elems_ with the number of buckets.
template <typename Key, typename Value, typename Compare, typename Hash>
hashmap<Key, Value, Compare, Hash>::hashmap(
	const Compare& comp, const Hash& hash) :
	size_(0), comp_(comp), hash_(hash) {
	elems_ = vector<list<Element>>(hash_.numBuckets());
}


// helper function
template <typename Key, typename Value,
	typename Compare, typename Hash>
	typename list<pair<const Key, Value>>::iterator // return type
	hashmap<Key, Value, Compare, Hash>::findElement(const Key& x, size_t bucket) {

	// look for the key in the bucket
	for (auto it = elems_[bucket].begin(); it != elems_[bucket].end(); ++it)
		if (comp_(it->first, x))
			return it;

	return elems_[bucket].end(); // element not found
}


// returns a pointer to the element with key x
// returns nullptr if no element with this key
template <typename Key, typename Value, typename Compare, typename Hash>
typename hashmap<Key, Value, Compare, Hash>::Element* // return value type
hashmap<Key, Value, Compare, Hash>::find(const Key& x) {

	size_t bucket = hash_.hash(x);
	auto it = findElement(x, bucket);    // use the findElement() helper   

	if (it != elems_[bucket].end())
		// found the element. Return a pointer to it.
		return &(*it); // dereference the iterator to list 
					   // then take the address of list element

	else // didn't find the element -- return nullptr
		return nullptr;
}


// finds the element with key x, inserts an
// element with that key if none exists yet. Returns a reference to
// the value corresponding to that key.
template <typename Key, typename Value, typename Compare, typename Hash>
std::pair<typename hashmap< Key, Value, Compare, Hash>::Element*, bool> 
hashmap<Key, Value, Compare, Hash>::insert(const Element& x) {

	pair<typename hashmap< Key, Value, Compare, Hash>::Element*, bool> safeInsert;  // declared a pair
	size_t bucket = hash_.hash(x.first);
	auto it = findElement(x.first, bucket);    // try to find the element

	// if not found, insert a new one.
	if (it == elems_[bucket].end()) {
		++size_;
		elems_[bucket].push_back(x);
		it = findElement(x.first,bucket);
		safeInsert.first = &(*it);
		safeInsert.second = true;
		return safeInsert;    // returns true if safely inserted 
	}
	else {
		safeInsert.first = &(*it);
		safeInsert.second = false;
		return safeInsert; // returns false if not inserted and already in the hash
	} 
}


// removes the Element with key x, if it exists
template <typename Key, typename Value, typename Compare, typename Hash>
std::pair<typename hashmap< Key, Value, Compare, Hash>::Element*, bool>
hashmap<Key, Value, Compare, Hash>::erase(const Key& x) {
	bool flag = true;
	pair<typename hashmap< Key, Value, Compare, Hash>::Element*, bool> safeErase;
	size_t size = elems_.size(); //way to access the last bucket
	size_t bucket = hash_.hash(x);
	auto it = findElement(x, bucket);    // try to find the element
	if (it != elems_[bucket].end()) { // the element exists, erase it
		std::advance(it, 1);  //advance the iterator for erase return purposes
		auto incr = it;  //storing it new postion
		size_t next = bucket + 1; //way to next bucket
		if (incr == elems_[bucket].end()) {
			auto nextB = elems_.begin() + bucket + 1; //iterator to the next bucket
			for (; nextB != elems_.end(); ++nextB) {
				if (!nextB->empty()) {  // the break will help find the next not empty bucket
					break;
				}
				++next;  //increment till found
			}
			if (nextB == elems_.end()) {  // if at the end of vector sets to nullptr because it is not specified
				safeErase.first = nullptr;
				safeErase.second = true;
				flag = false;
			}
			else {  //set to begining to the next non-empty bucket
				safeErase.first = &(*elems_[next].begin());
				safeErase.second = true;
				flag = false;
			}

		}
		if (it == elems_[size - 1].end()) { //if at the end of the bucket
			safeErase.first = nullptr;
			safeErase.second = true;
			flag = false;
		}
		if (flag) { //if all else just return the itertor to the postion next to the bucket value deleted(normal erase)
			safeErase.first = &(*incr);
			safeErase.second = true;
		}
		elems_[bucket].erase(--it);
		--size_;
	}
	else //if not found
	{
		safeErase.first = nullptr;
		safeErase.second = false;
	}

	return safeErase;
}


// returns reference to value of element with key x,
// inserts if does not exist
template <typename Key, typename Value, typename Compare, typename Hash>
Value& hashmap<Key, Value, Compare, Hash>::operator[] (const Key& x) {

	auto it = insert(make_pair(x, Value()));  //will insert key with the default constructor of value
	return it.first->second;                  //after moding insert it will return the boolean value depending on if it was inserted or not
}

//creating a new hash using default hasf to contruct ir
template <typename Key, typename Value, typename Compare, typename Hash>
void hashmap<Key, Value, Compare, Hash>::rehash(size_t n) {
	vector<list<Element>> hash(n);

	if (n > size_) {
		DefaultHash<Key> newHash(n);
		for (auto it = elems_.begin(); it != elems_.end(); ++it) {
			for (auto L = it->begin(); L != it->end(); L++) {
				size_t position = newHash.hash(L->first);
				hash[position].push_back(*L);
			}
		}
		elems_ = std::move(hash);
	}
	else if (n < size_) {
		std::cout << "Sorry, new size is smaller than orignal" << std::endl;
	}
}
