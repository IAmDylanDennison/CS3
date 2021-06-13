//Dylan Dennison
// Lab 3 Templated list
// header file for node & collection
//02/14/21

#ifndef LIST_COLLECTION_HPP_
#define LIST_COLLECTION_HPP_

#include <iostream>
// the pointer part of every list is the same
// lists differ by data part
template <typename T>
class node {
public:

	node() : next_(nullptr) {};

	// functions can be inlined
	T getData()const { return data_; }
	void setData(const T& data) { data_ = data; }

	// or can be defined outside
	node<T>* getNext() const;
	void setNext(node<T>* const);

private:
	T data_;
	node<T>* next_;
};

//
// member functions for node
//
template <typename T>
node<T>* node<T>::getNext()const {
	return next_;
}

template<typename T>
void node<T>::setNext(node<T>* const next) {
	next_ = next;
}

//collection class
template <typename T>
class Collection {
public:
	Collection() : headNode_(nullptr) {}; //default constructor with initializer list
	void add(const T&); // takes an item as the argumentand adds it to the collection, does not check for duplicates.
	void remove(const T&); // takes an item as the argumentand removes all instances of this item from the collection.
	T last(); // returns the last item added to the collection.
	void print(); // prints all items in the collection.The printout does not have to be in order.

	template <typename U>
	friend bool equal(const Collection<U>&, const Collection<U>&); // compares two collections for equality.Implement as a

private:
	node<T>* headNode_;
};

template <typename T>
void Collection<T>::add(const T& data) {
	node<T>* next = new node<T>();   // create new node to add data in

	next->setData(data);
	next->setNext(headNode_);						// allocates a new node and adds data to the new node

	headNode_ = next;
}

template <typename T>
void Collection<T>::remove(const T& data) {
	//creating two nodes to transform the list
	node<T>* p; // prev
	node<T>* c; // current

	c = headNode_;
	while (headNode_->getData() == data) {

		headNode_ = headNode_->getNext();             // if headnodes pointing at a node with data to be rm it will repostion it
		//p = headNode_->getNext();
		//c->setNext(headNode_->getNext()->getNext());
		//delete p;
	}

	while (c->getNext() != nullptr) {  // iterating through the list to check

		if (c->getNext()->getData() ==  data) {   //seeing data is in the node
			p = c->getNext();					// if so p will take that nodes postion to be deleted
			c->setNext(c->getNext()->getNext());  // current skips over the node to get to the next postion
			delete p;                             // the node with the data selcted will be deleted
		}
		else {   //if not found in the if loop, it will check the next node. so previous and current need to be repostioned
			p = c;
			c = c->getNext();
		}
	}

}

template <typename T>
void Collection<T>::print() {
	node<T>* it = new node<T>(); //it being short for iterator
	std::cout << std::endl << "List Print:" << std::endl;
	it = headNode_;
	while (it != nullptr) { //iterating until the end with the value of nullptr
		std::cout << it->getData() << std::endl; //prints data inside node

		it = it->getNext(); // gets the next node
	}

}

template <typename T>
T Collection<T>::last() {
	return headNode_->getData();   //returns the data in the most recently added node
}

template <typename U>
bool equal(const Collection<U>& left, const Collection<U>& right) {  // friend that compares two linked lists
	node<U>* one;  // creating pointer to the heads of both collections
	node<U>* two;
	one = left.headNode_;
	two = right.headNode_;

	if (one == nullptr && two == nullptr) { //if both are empty return true
		return true;
	}

	if (one == nullptr && two != nullptr || one != nullptr && two == nullptr) { //if one is empty and the other is not, return false
		return false;
	}

	while (one != nullptr && two != nullptr) {  //while both are not at the end of the list.. check through

		if (one->getData() != two->getData()) { //compare the data inside the nodes
			return false;
		}
		one = one->getNext();  //if not different set to next for both
		two = two->getNext();
	}

	return true; //will return true if no data is diffrent and is the same size
}


#endif // LIST_COLLECTION_HPP_
