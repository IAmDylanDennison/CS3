// vector and list algorithms with objects in containers
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


class Student {
public:			//default construtor
	Student(string firstName, string lastName, string csCourse) :
		firstName_(firstName), lastName_(lastName) {
		roster_.push_back(csCourse);
	}
/*
	// move constructor, not really needed, generated automatically
	Student(Student&& org) :
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

	string getFirstName() const { //getter for first name
		return firstName_;
	}

	string getLastName() const { //getter for last name
		return lastName_;
	}

	void printList() {  //prints list
		for (auto list : roster_) {
			cout << list << " ";
		}
	}

	void pushCourse(const string fileName) { //add course name to list
		roster_.push_back(fileName);
	}

private:
	string firstName_;
	string lastName_;
	list<string> roster_;
};




// reading a list from a fileName
void readRoster(list<Student>& roster, string fileName);
// printing a list out
void printRoster(const list<Student>& roster);

int main(int argc, char* argv[]) {

	if (argc <= 1) {
		cout << "usage: " << argv[0]
			<< " list of courses, dropouts last" << endl; exit(1);
	}

	list<Student> roster;
	for (int i = 1; i < argc - 1; ++i) {
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


void readRoster(list<Student>& roster, string fileName) {
	ifstream course(fileName);
	string first, last;  //string for student name
	string csClass = fileName; 
	csClass.erase(csClass.end() - 4, csClass.end());//creates string for course name without .txt
	while (course >> first >> last) {
		bool flag = false;
		for (auto& name : roster) {  //iterates through list

			if (name.getFirstName() == first && name.getLastName() == last) { //if the students name is found it will just add the course name
				name.pushCourse(csClass);
				flag = true; //if flag is true will skip the push back of the full student name
				break;
			}
		}
		if (flag == false) {
			roster.push_back(Student(first, last, csClass)); //will push back new student if flag isn't set to true
		}

	}
	course.close();
}

// printing a list out
void printRoster(const list<Student>& roster) { //iteratres through roster of students with course names added
	for (auto student : roster) {
		cout << student.print() << " ";
		student.printList();
		cout << endl;
	}
}
