// figures: class adapter pattern
// Dylan Dennison
// 03/26/21

#include <iostream>

using std::cout; using std::endl;

// base interface
class Figure {
public:
	virtual void draw() = 0;
	virtual ~Figure() {}
};

// adaptee/implementer
class LegacyRectangle {
public:
	LegacyRectangle(int topLeftX,
		int topLeftY,
		int bottomRightX,
		int bottomRightY) :
		topLeftX_(topLeftX),
		topLeftY_(topLeftY),
		bottomRightX_(bottomRightX),
		bottomRightY_(bottomRightY) {}

	//new move method 
	void move(int topLeftX, int topLeftY, int bottomRightX, int bottomRightY) {
			topLeftX_ = topLeftX;
			topLeftY_ = topLeftY;
			bottomRightX_ = bottomRightX;
			bottomRightY_ = bottomRightY;
	}

	void oldDraw() {
		for (int i = 0; i < bottomRightY_; ++i) {
			for (int j = 0; j < bottomRightX_; ++j)
				if (i >= topLeftY_ && j >= topLeftX_)
					cout << '*';
				else
					cout << ' ';
			cout << endl;
		}
	}

	//getters
	int getTopLeftX() { 
		return topLeftX_; 
	}

	int getTopLeftY() {
		return topLeftY_; 
	}

	int getBottomRightX() { 
		return bottomRightX_; 
	}

	int getBottomRightY() { 
		return bottomRightY_; 
	}

	// defining top/left and bottom/right coordinates 
private:
	int topLeftX_;
	int topLeftY_;
	int bottomRightX_;
	int bottomRightY_;
};

// adapter uses multiple inheritance to inherit
// interface and implementation
class SquareAdapter : public Figure,
	private LegacyRectangle {
public:
	SquareAdapter(int size) :
		LegacyRectangle(0, 0, size, size), size_(size) {};
	void draw() override {
		oldDraw();
	}

	//returns the size
	int size() {
		return size_;
	}

	void resize(int size) {
		size_ = size;
		
		//using move to resize
		move(getTopLeftX(), getTopLeftY(),size, size);
	}

private:
	int size_; //new private var for size

};


int main() {
	cout << "Enter size: ";
	int size;
	std::cin >> size;
	cout << endl;

	SquareAdapter* square = new SquareAdapter(size);
	square->draw();

	cout << endl;

	cout << "Enter Size for resize: ";
		int newSize;
		std::cin >> newSize;
		square->resize(newSize);
		square->draw();

}
