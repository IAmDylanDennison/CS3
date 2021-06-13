// filled/hollow figures demonstrates Bridge Design Pattern,
// square is either hollow or square and is painted with a particular character,
// it is bridged over Figure --> Fill abstract body/handle
// Dylan Dennison
// 03/26/21

#include <iostream>

using std::cout; using std::endl; using std::cin;

// abstract body
class Fill {
public:
	Fill(char fillChar, char borderChar ) :fillChar_(fillChar), borderChar_(borderChar) {}  // change for it takes fill and border
	virtual char getBorder() = 0;
	virtual char getInternal() = 0;
	virtual ~Fill() {}
protected:
	char fillChar_;
	char borderChar_;
};

// concrete body
class Hollow : public Fill {
public:
	Hollow(char fillChar) :Fill(fillChar, ' ') {}
	char getBorder() override { return fillChar_; }
	char getInternal() override { return ' '; }
	~Hollow() {}
};


// another concrete body
class Filled : public Fill {
public:
	Filled(char fillChar) :Fill(fillChar, fillChar) {}
	char getBorder() override { return fillChar_; }
	char getInternal() override { return fillChar_; }
	~Filled() {}
};

// abstract handle
class Figure {
public:
	Figure(int size, Fill* fill) : size_(size), fill_(fill) {}
	virtual void draw() = 0;
	virtual ~Figure() {}

	void changeFill(Fill* c) {  // changes fill
		delete fill_;  //deletes
		fill_ = c;	   //then changes
	}

protected:
	int size_;
	Fill* fill_;
};

// concrete handle
class Square : public Figure {
public:
	Square(int size, Fill* fill) : Figure(size, fill) {}
	void draw() override;

};


void Square::draw() {
	for (int i = 0; i < size_; ++i) {
		for (int j = 0; j < size_; ++j)
			if (i == 0 || j == 0 || i == size_ - 1 || j == size_ - 1)
				cout << fill_->getBorder();
			else
				cout << fill_->getInternal();
		cout << endl;
	}
}

//new class for for border and fill being different 
class EnhancedFilled : public Fill {
public:
	EnhancedFilled(char fillChar, char borderChar) :Fill(fillChar, borderChar) {}
	char getBorder() override { return borderChar_; }
	char getInternal() override { return fillChar_; }
	~EnhancedFilled() {}
};


int main() {
	/*
	Fill* hollowPaintY = new Hollow('^');
	Fill* filledPaintStar = new Filled('*');


	Figure *smallBox = new Square(5, filledPaintStar);
	Figure *bigBox = new Square(10, hollowPaintY);

	smallBox->draw();
	cout << endl;
	bigBox -> draw();
	*/

	// ask user for figure parameters
	cout << "Enter fill character: ";
	char fchar; cin >> fchar;
	cout << "Filled or hollow? [f/h] ";
	char ifFilled; cin >> ifFilled;
	cout << "Enter size: "; int size; cin >> size;

	Figure* userBox = new Square(size, ifFilled == 'f' ?
		static_cast<Fill*>(new Filled(fchar)) :
		static_cast<Fill*>(new Hollow(fchar))
	);
	

	userBox->draw();
	cout << endl;

	

	delete userBox;

	cout << "*****ENHANCED FILL*****" << endl;
	cout << "Enter border: ";
	char enhanceBorder; cin >> enhanceBorder;
	cout << "Enter fill: ";
	char enhanceFill; cin >> enhanceFill;
	cout << endl;

	userBox = new Square(size, static_cast<Fill*>(new EnhancedFilled(enhanceFill, enhanceBorder)));
	userBox->draw();
	cout << endl;

	//changes fill of the enhanced fill
	cout << "Want to change fill?[y/n]";
	char changeFill; cin >> changeFill;
	if (changeFill == 'y') {
		cout << "Enter fill character: ";
		char newFill; cin >> newFill;
		userBox->changeFill(new EnhancedFilled(newFill,enhanceBorder));  // new changefill function 
		userBox->draw();
		cout << endl;
	}
	delete userBox;

	cout << endl;

}
