// vector and list algorithms
//roster lab 4
// Dylan Dennison
// 02/19/21

#include <fstream>
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <cstdlib>

using std::ifstream;
using std::string; using std::getline;
using std::list; using std::vector;
using std::cout; using std::endl;
using std::move;


// reading a list from a fileName
void readRoster(vector<list<string>>& roster, string fileName);

// printing a list out
void printRoster(const vector<list<string>>& roster);

int main(int argc, char* argv[]) {

	if (argc <= 1) {
		cout << "usage: " << argv[0]
			<< " list of courses, dropouts last"
			<< endl; exit(1);
	}

	// vector of courses of students
	vector <list<string>> courseStudents;

	for (int i = 1; i < argc-1; ++i) {
		readRoster(courseStudents, argv[i]);
	}
	printRoster(courseStudents);

	/*// master list of students
	list<string> allStudents;

	for (auto& lst : courseStudents)
		allStudents.splice(allStudents.end(), lst);


	// sorting master list
	allStudents.sort();

	// eliminating duplicates
	allStudents.unique();
	cout << "\n\n all students, duplicates removed \n";
	printRoster(allStudents);
	*/
}

// reading in a file of names into a list of strings
void readRoster(vector<list<string>>& roster, string fileName) {
	ifstream course(fileName);
	string csClass = fileName;
	csClass.erase(csClass.end() - 4, csClass.end());// creates a string of the class name without .txt
	string first, last;//strings for the name of student

	while (course >> first >> last) {
		bool flag = false;
		for (auto it = roster.begin(); it != roster.end(); ++it) {// iterates through container 

			if (it->front() == first && *(++(it->begin())) == last) { // checks if the first and last name are already pushed in the list
				flag = true;
				it->push_back(csClass);  //if true(list already exists) just push the course name
				break;
			}

		}
		if (!flag) {  //if not found  just create new list to add student info
			list<string> student;
			student.push_back(move(first));
			student.push_back(move(last));
			student.push_back(csClass);
			roster.push_back(move(student));
		}
	}
	course.close();
}

// printing a vector of lists containing strings 
void printRoster(const vector<list<string>>& roster) {
	for (auto it = roster.begin(); it != roster.end(); ++it) { // iterators the vector of lists
		for (auto& name : *it) {// prints the elements in the list
			cout << name << " ";
		}
		cout << endl;
	}

}
