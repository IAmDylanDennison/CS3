//main file
//input command line for wordlist
//Dylan Dennison

#include "WordList.hpp"


int main(int argc, char* argv[]) {

	if (argc < 2) { // if user does not put in the correct amount of files
		std::cerr << "You do not have all the files. Please include all files." << std::endl;
		return 0;
	}
	WordList obj; //create object

	std::string file;
	file = argv[1];			//sets string to the file on the command line
	std::ifstream get(file);

		bool check = true;
		std::string word;
		while (get >> word) { //pulls all the words from the string I thought this was really cool!
			for (int i = 0; i < word.length(); i++) { //iterates through the string chars
				char c = word[i];
					if (isalpha(c)){ //checks if it is a character
						check = true;
					}
					else
					check = false;
			}

			if (check == true) {		//if its only chars it will add the word to the object
				obj.addWord(word);
			}

		}




	obj.print(); //prints 
	get.close(); //close file always

	return 0;
}
