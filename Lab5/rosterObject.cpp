// Dylan Dennison
// lab 5 maps
//02/26/21

#include <fstream>
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <cstdlib>
#include <map>
#include <utility>

using std::ifstream;
using std::string; using std::getline;
using std::list; using std::vector;
using std::cout; using std::endl;
using std::move; using std::map;


class Student {
public:
	Student(string firstName, string lastName) :
		firstName_(firstName), lastName_(lastName) {}

	// move constructor, not really needed, generated automatically
	/*Student(Student&& org) :
		firstName_(move(org.firstName_)),
		lastName_(move(org.lastName_))
	{}
	*/

	// force generation of default copy constructor
	Student(const Student& org) = default;

	string print() const { return firstName_ + ' ' + lastName_; }

	// needed for unique() and for remove()
	friend bool operator== (Student left, Student right) {
		return left.lastName_ == right.lastName_ &&
			left.firstName_ == right.firstName_;
	}

	// needed for sort()
	friend bool operator< (Student left, Student right) {
		return left.lastName_ < right.lastName_ ||
			(left.lastName_ == right.lastName_ &&
				left.firstName_ < right.firstName_);
	}
	/*
	string getFirstName() const { //getter for first name
		return firstName_;
	}

	string getLastName() const { //getter for last name
		return lastName_;
	}

	void printList() {
		for (auto list : roster_) {
			cout << list << " ";
		}
	}

	void pushCourse(const string fileName) {
		roster_.push_back(fileName);
	}
	*/
private:
	string firstName_;
	string lastName_;
};




// reading a list from a fileName
void readRoster(map<Student, list<string>>& roster, string fileName);
// printing a list out
void printRoster(const map<Student,list<string>>& roster);

int main(int argc, char* argv[]) {

	if (argc <= 1) {
		cout << "usage: " << argv[0]
			<< " list of courses, dropouts last" << endl; exit(1);
	}

	// vector of courses of students
	map<Student, list<string>> roster;

	for (int i = 1; i < argc-1 ; ++i) {

		readRoster(roster, argv[i]);
	}
		printRoster(roster);


	/*
		// reading in dropouts
		list<Student> dropouts;
		readRoster(dropouts, argv[argc - 1]);
		cout << "\n\n dropouts \n"; printRoster(dropouts);

		list<Student> allStudents;  // master list of students

		for (auto& lst : courseStudents)
			allStudents.splice(allStudents.end(), lst);

		cout << "\n\n all students unsorted \n";
		printRoster(allStudents);

		allStudents.sort(); // sorting master list
		cout << "\n\n all students sorted \n"; printRoster(allStudents);

		allStudents.unique(); // eliminating duplicates
		cout << "\n\n all students, duplicates removed \n"; printRoster(allStudents);

		for (const auto& str : dropouts)  // removing individual dropouts
			allStudents.remove(str);
		cout << "\n\n all students, dropouts removed \n"; printRoster(allStudents);
		*/
}


void readRoster(map<Student, list<string>>& roster, string fileName){
	ifstream course(fileName);
	string csClass = fileName;
	csClass.erase(csClass.end() - 4, csClass.end());
	string first, last;
	list<string> courseList;
	courseList.push_back(csClass);  //creat a list with the cs course to be placed as the element in the map

	while (course >> first >> last) {
		bool flag = false;
		for (auto& it : roster) {
			if (it.first == Student(first, last)) {  //if the key is already in the map it will just push back the course
				it.second.push_back(csClass);
				flag = true;
			}

		}
		if (!flag) {
			roster.emplace(Student(first, last), courseList); // if not it will emplace a new map element 
		}

	}
	course.close();
}

// printing a map out
void printRoster(const map<Student, list<string>>& roster) {
	for (const auto& it : roster) {   //simple nested loop to print the key and element of the map 
		cout << it.first.print() << ": ";
		for (auto courses : it.second) {
			cout << courses << " ";
		}
		cout << endl;

	}
}
