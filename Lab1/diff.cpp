//Dylan Dennison
//Lab 1
//1/22/21
//CS3

#include <iostream>
#include <fstream>
#include <cstring>
#include <string>


int main(int argc, char* argv[]) {

	// implementing the two files in the program
	std::ifstream fileOne(argv[1]);
	std::ifstream fileTwo(argv[2]);


	if (argc < 3) { // if user does not put in the correct amount of files
		std::cerr << "You do not have all the files. Please include all files." << std::endl;
		return 0;
	}

	int line = 1;  //line counter

	// loops while not at the end of both files not just one
	while (!fileOne.eof() && !fileTwo.eof()) {

		std::string fLine1;
		std::string fLine2; //creating strings for getline

		if (!fileOne.eof()) {
			getline(fileOne, fLine1); //grabs string from the files line
			}
		else {
			fLine1 = ""; // creates an empty string in case one of the files is longer than the other
		}

		if (!fileTwo.eof()) { //same as file 1
			getline(fileTwo,fLine2);
		}
		else {
			fLine2 = "";
			//std::cout << "end of file" << std::endl;
		}


		if (fLine1 != fLine2) {
			std::cout << argv[1] << ": " << line << ": " << fLine1 << std::endl; // prints line one
			std::cout << argv[2] << ": " << line << ": " << fLine2 << std::endl; // prints line two

			// +2 is to account for the ": "
			int lengthOfFile = strlen(argv[2]) + 2; //finds char length of the C style string (the file name)
			int lengthOfLineNumber = std::to_string(line).length() + 2; //Turns # line into a string then fines its length

		 // fines the number a chars before the diffrence
                        int cSpace = 0;
                        while (fLine1[cSpace] == fLine2[cSpace]) {
                                cSpace++;
                        }


			int length = lengthOfFile + lengthOfLineNumber + cSpace; //adds all the spaces together

			std::string spaceString(length, ' '); //creats a string of the spaces needed

			std::cout << spaceString << "^" << std::endl; //prints ^ on the difference

		}

		line++; // Increments the line number if there is no differnce found in the string 
	}

	fileOne.close();
	fileTwo.close();//always close the files at the end

	return 0;
}
