// traversing genealogical tree using Composite and Visitors
// showing womens maiden name from father
// Dylan Dennison
// 04/23/21

#include <iostream>
#include <string>
#include <vector>

using std::cout; using std::endl;
using std::string;
using std::vector;

class Person { // component
public:
	Person(string firstName, Person* spouse, Person* father, Person* mother) :
		firstName_(firstName), spouse_(spouse), father_(father), mother_(mother) {}
	const string& getFirstName() { return firstName_; }
	Person* getSpouse() { return spouse_; }
	void setSpouse(Person* spouse) { spouse_ = spouse; }
	Person* getFather() { return father_; }
	Person* getMother() { return mother_; } // added this getter for Marriage advice

	virtual string getFullName() = 0;  //Had to add this to both man and woman because I had a lot of warnings without it
	virtual void accept(class PersonVisitor*) = 0;
	virtual ~Person() {}
private:
	const string firstName_;
	Person* spouse_;
	Person* father_;
	Person* mother_;
};


// leaf
// man has a last name 
class Man : public Person {
public:
	Man(string lastName, string firstName, Person* spouse,
		Person* father, Person* mother) :
		lastName_(lastName),
		Person(firstName, spouse, father, mother) {}
	const string& getLastName() { return lastName_; }
	void accept(class PersonVisitor* visitor) override;

	string getFullName() override {
		return getFirstName() + " " + getLastName();  //getting full name of man I had a bunch of warnings before I made this funciton
	}

private:
	const string lastName_;
};

// composite
// woman has a list of children
class Woman : public Person {
public:
	Woman(vector<Person*> children,
		string firstName,
		Person* spouse,
		Person* father, Person* mother) :
		children_(children),
		Person(firstName, spouse, father, mother) {}
	const vector<Person*>& getChildren() { return children_; }
	void setChildren(const vector<Person*>& children) { children_ = children; }
	void accept(class PersonVisitor* visitor) override;

	string getFullName() override {
		string wName;
		if (getSpouse() != nullptr) {
			wName = getFirstName() + " " + static_cast<Man*>(getSpouse())->getLastName();
		}																								 //getting name full name of woman
		else {
			wName = getFirstName() + " " + static_cast<Man*>(getFather())->getLastName();
		}
		return wName;
	}


	const vector<Person*>& getKids() { // added to return children of a mother/women for marriage advice
		return children_;
	}

private:
	vector<Person*> children_;
};

// abstract visitor
class PersonVisitor {
public:
	virtual void visit(Man*) = 0;
	virtual void visit(Woman*) = 0;
	virtual ~PersonVisitor() {}
};

// composite methods that define traversal
void Man::accept(PersonVisitor* visitor) {
	visitor->visit(this);
}

void Woman::accept(PersonVisitor* visitor) {
	// children traversal through mother only
	// father's children are not traversed so as not 
	// to traverse them twice: for mother and father

	visitor->visit(this);
	// traversing descendants
	for (auto child : children_)
		child->accept(visitor);


}

// concrete visitors
// the last name for a man is stored in object
// the last name a woman is determined by her 
// spouse if she is married
// or by her father if she is not


class NamePrinter : public PersonVisitor {
public:
	void visit(Man* m) override {
		cout << m->getFirstName() << " " << m->getLastName() << endl;
	}
	void visit(Woman* w) override {
		cout << w->getFirstName() << " ";
		if (w->getSpouse() != nullptr)
			cout << static_cast<Man*> (w->getSpouse())->getLastName();
		else if (w->getFather() != nullptr)
			cout << static_cast<Man*> (w->getFather())->getLastName();
		else
			cout << "Doe";
		cout << endl;
	}
};

//visitor class to allow marriage or not
class MarriageAdvice : public PersonVisitor {
public:
	MarriageAdvice(string personOne, string personTwo): name1_(personOne), name2_(personTwo) {} // constructor 
	
	bool getDecison() { return marryAllowed_; } //returns the predicate of whether the two people can get married or not

	//I do not check for children because both man and woman have to be married already to have children

	void visit(Man* man) override {
		bool flag = true;
		string mName = man->getFullName();

		//tried to do a while loop but it kept infinite looping so I just returned after each condition 
		
			if ((mName == name1_ || mName == name2_)&& man->getSpouse() != nullptr) { //check if married already
				marryAllowed_ = false;
				return;
			}

			//checks mothers side mother
			if (mName == name1_ && man->getMother() != nullptr && man->getMother()->getMother() != nullptr) {  // check uncles or aunts 
				
				for (auto f : static_cast<Woman*>(man->getMother()->getMother())->getKids()) { //gets grandmas children 
					string fName = f->getFullName(); 

					/*
					if (f->getSpouse() != nullptr) {
						 fName = f->getFirstName() + " " + static_cast<Man*>(f->getSpouse())->getLastName();
					}																								 //getting name of grandmas child(aunts and uncles)
					else {
						 fName = f->getFirstName() + " " + static_cast<Man*>(f->getFather())->getLastName();
					}
					*/

					if (fName == name2_) { //if person two is a uncle or aunt they can not marry
						marryAllowed_ = false;
						return;
					}
				}
			}
			//checks father side mother
			if (mName == name1_ && man->getFather() != nullptr && man->getFather()->getMother() != nullptr) {  // check uncles or aunts 
				
				for (auto f : static_cast<Woman*>(man->getFather()->getMother())->getKids()) { //gets grandmas children 
					string fName = f->getFullName();
					/*
					if (f->getSpouse() != nullptr) {
						fName = f->getFirstName() + " " + static_cast<Man*>(f->getSpouse())->getLastName();
					}																								 //getting name of grandmas child(aunts and uncles)
					else {
						fName = f->getFirstName() + " " + static_cast<Man*>(f->getFather())->getLastName();
					}
					*/

					if (fName == name2_) { //if person two is a uncle or aunt they can not marry
						marryAllowed_ = false;
						return;
					}
				}
			}

			//checks for other name entered 
			//checks mothers side mother
			if (mName == name2_ && man->getMother() != nullptr && man->getMother()->getMother() != nullptr) {  // check uncles or aunts 
				
				for (auto f : static_cast<Woman*>(man->getMother()->getMother())->getKids()) { //gets grandmas children 
					string fName = f->getFullName();
					/*
					if (f->getSpouse() != nullptr) {
						fName = f->getFirstName() + " " + static_cast<Man*>(f->getSpouse())->getLastName();
					}																								 //getting name of grandmas child(aunts and uncles)
					else {
						fName = f->getFirstName() + " " + static_cast<Man*>(f->getFather())->getLastName();
					}
					*/
					if (fName == name1_) { //if person two is a uncle or aunt they can not marry
						marryAllowed_ = false;
						return;
					}
				}
			}
			//checks father side mother
			if (mName == name2_ && man->getFather() != nullptr && man->getFather()->getMother() != nullptr) {  // check uncles or aunts 
				
				for (auto f : static_cast<Woman*>(man->getFather()->getMother())->getKids()) { //gets grandmas children 
					string fName = f->getFullName();
					/*
					if (f->getSpouse() != nullptr) {
						fName = f->getFirstName() + " " + static_cast<Man*>(f->getSpouse())->getLastName();
					}																								 //getting name of grandmas child(aunts and uncles)
					else {
						fName = f->getFirstName() + " " + static_cast<Man*>(f->getFather())->getLastName();
					}
					*/
					if (fName == name1_) { //if person two is a uncle or aunt they can not marry
						marryAllowed_ = false;
						return;
					}
				}
			}

			//check for brothers and sisters

			if (mName == name1_ && man->getMother() != nullptr) {
				
				for (auto f : static_cast<Woman*>(man->getMother())->getKids()) { //gets siblings 
					string fName = f->getFullName();
					/*
					if (f->getSpouse() != nullptr) {
						fName = f->getFirstName() + " " + static_cast<Man*>(f->getSpouse())->getLastName();
					}																								 //getting name of brother or sister
					else {
						fName = f->getFirstName() + " " + static_cast<Man*>(f->getFather())->getLastName();
					}
					*/
					if (fName == name2_) { //if person two is a sister or brother they can not marry
						marryAllowed_ = false;
						return;
					}
				}
			}

			if (mName == name2_ && man->getMother() != nullptr) {
				
				for (auto f : static_cast<Woman*>(man->getMother())->getKids()) { //gets siblings 
					string fName = f->getFullName();
					/*
					if (f->getSpouse() != nullptr) {
						fName = f->getFirstName() + " " + static_cast<Man*>(f->getSpouse())->getLastName();
					}																								 //getting name of brother or sister
					else {
						fName = f->getFirstName() + " " + static_cast<Man*>(f->getFather())->getLastName();
					}
					*/
					if (fName == name1_) { //if person two is a sister or brother they can not marry
						marryAllowed_ = false;
						return;
					}
				}
			}

		
	}

	void visit(Woman* woman) override {
		bool flag = true;
		string wName = woman->getFullName();
		/*
		if (woman->getSpouse() != nullptr) {
			wName = woman->getFirstName() + " " + static_cast<Man*>(woman->getSpouse())->getLastName();
		}																								 //getting name of person visited
		else {
			wName = woman->getFirstName() + " " + static_cast<Man*>(woman->getFather())->getLastName();
		}
		*/

		if ((wName == name1_ || wName == name2_) && woman->getSpouse() != nullptr) { //check if married already
			marryAllowed_ = false;
			return;
		}
			//checks mothers side mother
			if (wName == name1_ && woman->getMother() != nullptr && woman->getMother()->getMother() != nullptr) {  // check uncles or aunts 

				for (auto f : static_cast<Woman*>(woman->getMother()->getMother())->getKids()) { //gets grandmas children 
					string fName = f->getFullName();
					/*
					if (f->getSpouse() != nullptr) {
						fName = f->getFirstName() + " " + static_cast<Man*>(f->getSpouse())->getLastName();
					}																								 //getting name of grandmas child(aunts and uncles)
					else {
						fName = f->getFirstName() + " " + static_cast<Man*>(f->getFather())->getLastName();
					}
					*/
					if (fName == name2_) { //if person two is a uncle or aunt they can not marry
						marryAllowed_ = false;
						return;
					}
				}
			}
			//checks father side mother
			if (wName == name1_ && woman->getFather() != nullptr && woman->getFather()->getMother() != nullptr) {  // check uncles or aunts 

				for (auto f : static_cast<Woman*>(woman->getFather()->getMother())->getKids()) { //gets grandmas children 
					string fName = f->getFullName();
					/*
					if (f->getSpouse() != nullptr) {
						fName = f->getFirstName() + " " + static_cast<Man*>(f->getSpouse())->getLastName();
					}																								 //getting name of grandmas child(aunts and uncles)
					else {
						fName = f->getFirstName() + " " + static_cast<Man*>(f->getFather())->getLastName();
					}
					*/
					if (fName == name2_) { //if person two is a uncle or aunt they can not marry
						marryAllowed_ = false;
						return;
					}
				}
			}

			//checks for other name entered 
			//checks mothers side mother
			if (wName == name2_ && woman->getMother() != nullptr && woman->getMother()->getMother() != nullptr) {  // check uncles or aunts 

				for (auto f : static_cast<Woman*>(woman->getMother()->getMother())->getKids()) { //gets grandmas children 
					string fName = f->getFullName();
					/*
					if (f->getSpouse() != nullptr) {
						fName = f->getFirstName() + " " + static_cast<Man*>(f->getSpouse())->getLastName();
					}																								 //getting name of grandmas child(aunts and uncles)
					else {
						fName = f->getFirstName() + " " + static_cast<Man*>(f->getFather())->getLastName();
					}
					*/
					if (fName == name1_) { //if person two is a uncle or aunt they can not marry
						marryAllowed_ = false;
						return;
					}
				}
			}
			//checks father side mother
			if (wName == name2_ && woman->getFather() != nullptr && woman->getFather()->getMother() != nullptr) {  // check uncles or aunts 

				for (auto f : static_cast<Woman*>(woman->getFather()->getMother())->getKids()) { //gets grandmas children 
					string fName = f->getFullName();
					/*
					if (f->getSpouse() != nullptr) {
						fName = f->getFirstName() + " " + static_cast<Man*>(f->getSpouse())->getLastName();
					}																								 //getting name of grandmas child(aunts and uncles)
					else {
						fName = f->getFirstName() + " " + static_cast<Man*>(f->getFather())->getLastName();
					}
					*/
					if (fName == name1_) { //if person two is a uncle or aunt they can not marry
						marryAllowed_ = false;
						return;
					}
				}
			}

			//check for brothers and sisters

			if (wName == name1_ && woman->getMother() != nullptr) {

				for (auto f : static_cast<Woman*>(woman->getMother())->getKids()) { //gets siblings 
					string fName = f->getFullName();
					/*
					if (f->getSpouse() != nullptr) {
						fName = f->getFirstName() + " " + static_cast<Man*>(f->getSpouse())->getLastName();
					}																								 //getting name of brother or sister
					else {
						fName = f->getFirstName() + " " + static_cast<Man*>(f->getFather())->getLastName();
					}
					*/
					if (fName == name2_) { //if person two is a sister or brother they can not marry
						marryAllowed_ = false;
						return;
					}
				}
			}

			if (wName == name2_ && woman->getMother() != nullptr) {

				for (auto f : static_cast<Woman*>(woman->getMother())->getKids()) { //gets siblings 
					string fName = f->getFullName();
					/*
					if (f->getSpouse() != nullptr) {
						fName = f->getFirstName() + " " + static_cast<Man*>(f->getSpouse())->getLastName();
					}																								 //getting name of brother or sister
					else {
						fName = f->getFirstName() + " " + static_cast<Man*>(f->getFather())->getLastName();
					}
					*/
					if (fName == name1_) { //if person two is a sister or brother they can not marry
						marryAllowed_ = false;
						return;
					}
				}
			}
	}

private:
	string name1_;
	string name2_;
	bool marryAllowed_ = true;;

};

//visitor class for maiden names for the women
class MadienName : public PersonVisitor {
public:
	void visit(Man* man) override { //prints men names for comparison 
		cout << man->getFirstName() << " " << man->getLastName();
		cout << endl;
	}
	void visit(Woman* woman) override {
		cout << woman->getFirstName();
		if (woman->getFather() != nullptr) { // if has father it will print maiden name
			cout << " (Maiden Name)" << static_cast<Man*>(woman->getFather())->getLastName();
		}
		else {
			cout << " (Maiden Name)N/A"; //prints blank if no father
		}
		if (woman->getSpouse() != nullptr) { // if has spouse it will print that as well
			cout << " (Spouse Lastname)" << static_cast<Man*> (woman->getSpouse())->getLastName();
		}
		else {
			cout << " (Spouse LastName)N/A"; // prints blank if not married 
		}

		cout << endl;
	}
};

class ChildrenPrinter : public PersonVisitor {
public:
	void visit(Man* m) override {
		cout << m->getFirstName() << ": ";
		Woman* spouse = static_cast<Woman*>(m->getSpouse());
		if (spouse != nullptr)
			printNames(spouse->getChildren());
		cout << endl;
	}
	void visit(Woman* w) override {
		cout << w->getFirstName() << ": ";
		printNames(w->getChildren());
		cout << endl;
	}
private:
	void printNames(const vector<Person*>& children) {
		for (const auto c : children)
			cout << c->getFirstName() << ", ";
	}
};


// demonstrating the operation
int main() {

	// setting up the genealogical tree      
	// the tree is as follows
	//    
	//
	//       James Smith  <--spouse-->   Mary 
	//	                                  |
	//	                                 children -------------------------
	//	                                  |              |                |
	//	                                  |              |                |
	//	   William Johnson <--spouse-> Patricia      Robert Smith       Linda
	//	                                  |
	//	                                 children------------
	//	                                  |                 |
	//                                     |                 |
	//	   Jennifer  <--spouse-->  Michael Johnson      Barbara
	//	       |
	//	     children
	//	       |
	//          |
	//	     Susan


	// first generation
	Man* js = new Man("Smith", "James", nullptr, nullptr, nullptr);
	Woman* ms = new Woman({}, "Mary", nullptr, nullptr, nullptr);
	ms->setSpouse(js); js->setSpouse(ms);

	// second generation
	Woman* ps = new Woman({}, "Patricia", nullptr, js, ms);
	Man* wj = new Man("Johnson", "William", nullptr, nullptr, nullptr);
	ps->setSpouse(wj); wj->setSpouse(ps);

	vector<Person*> marysKids = { ps,
					   new Man("Smith", "Robert", nullptr, js, ms),
					   new Woman({}, "Linda", nullptr, js, ms) };
	ms->setChildren(marysKids);

	// third generation
	Man* mj = new Man("Johnson", "Michael", nullptr, wj, ps);
	vector<Person*> patsKids = { mj, new Woman({}, "Barbara", nullptr, wj, ps) };
	ps->setChildren(patsKids);

	Woman* jj = new Woman({}, "Jennifer", nullptr, nullptr, nullptr);
	vector<Person*> jensKids = { new Woman({}, "Susan", nullptr, mj ,jj) };

	jj->setSpouse(mj); mj->setSpouse(jj);
	jj->setChildren(jensKids);

	/*
	// defining two visitors
	ChildrenPrinter* cp = new ChildrenPrinter;
	NamePrinter* np = new NamePrinter;

	MadienName* mn = new MadienName;

	// executing the traversal with the composite
	// and the specific visitor



	cout << "\nNAME LIST\n";
	ms->accept(np);

	cout << endl;
	cout << "        ^ " << endl;
	cout << "COMPARE |" << endl;
	cout << "        v" << endl;
	cout << "\nNAME LIST WITH MAIDEN NAMES\n";

	ms->accept(mn);
	
	cout << endl << endl;

	cout << "CHILDREN LIST\n";
	ms->accept(cp);

	cout << "\nJAMES' CHILDREN\n";
	js->accept(cp);
	*/

	string personOne;
	string personTwo;

	cout << "Enter first candidate: ";
	std::getline(std::cin, personOne);
											//getting user input

	cout << "Enter second candidate: ";
	std::getline(std::cin, personTwo);
	cout << endl;

	bool canMarry; //bool to check if the names are the same and to decided output

	MarriageAdvice* m = new MarriageAdvice(personOne,personTwo);

	ms->accept(m);

	canMarry = m->getDecison(); // gets the predicate from the vist class private bool
	if (personOne == personTwo) { canMarry = false; } //if the names are the same they can not marry

	if (!canMarry)
		cout << "They can not marry." << endl;
	else
		cout << "They can marry." << endl;
}
