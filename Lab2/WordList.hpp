//Dylan Dennison
// WordList.hpp file
// 1/28/21

#ifndef CS44001_WORDLIST_HPP
#define CS44001_WORDLIST_HPP

#include <iostream>
#include <cstring>
#include <string>
#include <algorithm>
#include <sstream>
#include <fstream>

class WordOccurrence {
public:
    WordOccurrence(const std::string& word="", int num=0);
    bool matchWord(const std::string &); // returns true if word matches stored
    void increment(); // increments number of occurrences
    std::string getWord() const;
    int getNum() const;

private:
    std::string word_;
    int num_;
};

class WordList{
public:
    // add copy constructor, destructor, overloaded assignment
	WordList();
	WordList(const WordList&);             //copy constructor
	WordList& operator=(WordList);  //overload assignment
	friend void swap(WordList&, WordList&); //swap for overload
	~WordList();                           //destructor

    // implement comparison as friend
    friend bool equal(const WordList&, const WordList&);

    void addWord(const std::string &);
    void print();
private:
    WordOccurrence *wordArray_; // a dynamically allocated array of WordOccurrences
                                // may or may not be sorted
    int size_;
};

#endif
