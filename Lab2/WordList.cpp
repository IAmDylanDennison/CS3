//Dylan Dennison
// implementation cpp file for the wordlist.hpp
// 1/28/21
#include "WordList.hpp"
// class WordOccurrence

WordOccurrence::WordOccurrence(const std::string& word, int num) 
	: word_(word), num_(num) {};									//construtor, sets both to default values with initializer list


bool WordOccurrence::matchWord(const std::string & nWord) {  //checks to see if word is the same. nword stands for new word
		return nWord == word_;
}

void WordOccurrence::increment() {  //increments num_ for word count
		num_++;
}

std::string WordOccurrence::getWord() const { //getter of word_
		return word_;
}

int WordOccurrence::getNum() const {  //getter of num_
		return num_;
}


// class WordList

WordList::WordList() {  //default constructor
size_ = 0;
wordArray_ = new WordOccurrence[size_];
}

WordList::WordList(const WordList& rhs) { //copy constructor
	size_ = rhs.size_;
	wordArray_ = size_ > 0 ? new WordOccurrence[size_] : nullptr;
	std::copy(rhs.wordArray_, rhs.wordArray_ + size_, wordArray_);
}

WordList& WordList::operator=(WordList rhs) { //overload assignment
	swap(*this, rhs);
		return *this;
}

void swap(WordList& x,WordList& y) { //swap for overload assignment
	std::swap(x.size_, y.size_);
	std::swap(x.wordArray_, y.wordArray_);
}

WordList::~WordList() { //destructor
	delete[] wordArray_;
}

bool equal(const WordList& one, const WordList& two) { // compares two objects to see if they are equal
	int size1 = one.size_;
	int size2 = two.size_;

	if (size1 != size2) {  // if both the same size it will return true
		return false;
	}
	else {

		for (int i = 0; i < size2; i++) { // if both the same size it will compare the words to see if the objects are the same
			if (one.wordArray_[i].getWord() != two.wordArray_[i].getWord()) {
				return false;
			}
			if(one.wordArray_[i].getNum() != two.wordArray_[i].getNum()) {
				return false;
			}
		}
	}
	return true;
}

void WordList::addWord(const std::string & word) { // adds word
	bool match = false;
	//check if word as already in array
	for (int i = 0; i < size_; i++) {
		if (wordArray_[i].matchWord(word)) {
			wordArray_[i].increment();
			match = true; // if it matches, match will turn to true
		}
	}

	if (match == false) { // if it does not match it will be added 
		WordOccurrence* tmp = wordArray_;
		wordArray_ = new WordOccurrence[size_ + 1];    //modify array by using a tmp
		for (int i = 0; i < size_; i++) {
			wordArray_[i] = tmp[i];
		}
		wordArray_[size_] = word;  // adds new word into new dynamically allocated space
		wordArray_[size_].increment();  //increments the word count after 
		delete[] tmp;
		size_++;
	}
}

void WordList::print() {

	std::cout << "Word Count Program" << std::endl;
	std::cout << "Word:" << "\t" << "\t" << "Count:" << std::endl;

	for (int i = 0; i < size_; i++) {  //using bubble sort method to sort words
		for(int j = i+1; j < size_; j++){
			if (wordArray_[j].getNum() < wordArray_[i].getNum()) {
				std::swap(wordArray_[j],wordArray_[i]);  //swaping for correct order
			}
		}
	}

	for (int i = 0; i < size_; i++) { //printing array

		std::cout << wordArray_[i].getWord() << "\t" << "\t" << wordArray_[i].getNum() << std::endl;
	}
}





