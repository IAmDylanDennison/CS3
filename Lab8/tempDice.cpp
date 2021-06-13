// Games, Template Method example
// Dylan Dennison
// 03/19/21

#include <ctime>
#include <cstdlib>
#include <iostream>
#include <vector>

using std::cout; using std::endl; using std::vector; using std::cin;

// template for any game where players take 
// turns to make moves
// and there is a winner
class Game {
public:
	Game() :playersCount_(0), movesCount_(0), playerWon_(noWinner) {}

	// template method
	void playGame(const int playersCount = 0) {
		playersCount_ = playersCount;
		movesCount_ = 0;

		initializeGame();

		for (int i = 0; !endOfGame(); i = (i + 1) % playersCount_) {
			makeMove(i);
			if (i == playersCount_ - 1)
				++movesCount_;
		}

		printWinner();
	}

	virtual ~Game() {}

protected:
	// primitive operations
	virtual void initializeGame() = 0;
	virtual void makeMove(int player) = 0;
	virtual void printWinner() = 0;
	virtual bool endOfGame() { return playerWon_ != noWinner; } // this is a hook
					// returns true if winner is decided
	static const int noWinner = -1;

	int playersCount_;
	int movesCount_;
	int playerWon_;
};



class Dice : public Game {
public:
	void initializeGame() {
		playersCount_ = numPlayers_; // initalize players
		for (int i = 0; i < numOfDice_; ++i) {  //initalize arrays
			
				rollCountCpu[i] = 0;	
		}
		for (int j = 0; j < numOfDice_; ++j) {

			rollCountPlayer[j] = 0;
		}
	}

	void makeMove(int player) {
		char choice;
		if (!endOfGame()) {

			for (int i = 0; i < numOfDice_; ++i) { //fills computer array
				rollCountCpu[i] = rand() % 6 + 1;
			}
			
			for (int j = 0; j < numOfDice_; ++j) { //fills user array
				rollCountPlayer[j] = rand() % 6 + 1;
			}
		
			//computer
			if (player == 0 && !stay) {
				cout << "Computer rolled: ";
				if (!stay) {
					int num = 0;
					for (int i = 0; i < numOfDice_; ++i) {  //prints and adds score of computer
						cout << rollCountCpu[i] << " ";
						 num += rollCountCpu[i];
					}
					if (num > cpuScore_) {
						cpuScore_ = num;
					}

					cout << "= " << num << ", computers's highest score = " << cpuScore_ << endl;
				}
			}
			else if(player == 0 && stay){  //if passed
				cout << "Computer rolled: passed, computers's highest score = " << cpuScore_ << endl;
			} 

			//user
			if (player == 1 && !pStay) {
				cout << "You rolled: ";
				if(!pStay) {
					int n = 0;
					for (int i = 0; i < numOfDice_; ++i) { //prints and adds score of user
						cout << rollCountPlayer[i] << " ";
						n += rollCountPlayer[i];
					}
					if (n > PScore_) {
						PScore_ = n;
					}

					cout << "= " << n << ", your highest score = " << PScore_ << endl;

					if (movesCount_ < maxMoves_ - 1) {  //choice to pass or stay
						cout << "Roll again? [y/n]";
						cin >> choice;
						if (choice == 'y') {
						pStay = false;
						}
						if (choice == 'n') {
						pStay = true;
						}
					}
				}
			}
			else if(pStay && player == 1) {  // if passed
				cout << "You rolled: passed, your highest score = " << PScore_ << endl;
			}
			//if computer rolls higher than a 19 it will stay and the current score is winning
			if (cpuScore_ > 19 && cpuScore_ >= PScore_) { 
				stay = true;
			}
			
		}

	}

	// prints winner
	void printWinner() {
		if (cpuScore_ < PScore_)
			cout << "you won";
		else
			cout << "you lost";

		cout << endl;
	}

	// mod to end game after 3 turns 
	bool endOfGame() {
		if (movesCount_ == 3)
			return true;
		else
			return false;
	}

private:
	static const int numPlayers_ = 2;
	static const int numOfDice_ = 5;
	static const int maxMoves_ = 3;
	int cpuScore_ = 0; //computer high score
	int PScore_ = 0; //user high score
	int rollCountCpu[numOfDice_];  //arrays for roll total
	int rollCountPlayer[numOfDice_];
	bool stay = false; //predicates for player staying
	bool pStay = false;

};

// Monopoly - a concrete game implementing primitive 
// operations for the template method
class Monopoly : public Game {
public:
	// implementing concrete methods
	void initializeGame() {
		playersCount_ = rand() % numPlayers_ + 1; // initialize players
	}

	void makeMove(int player) {
		if (movesCount_ > minMoves_) {
			const int chance = minMoves_ + rand() % (maxMoves_ - minMoves_);
			if (chance < movesCount_) playerWon_ = player;
		}
	}

	void printWinner() {
		cout << "Monopoly, player " << playerWon_ << " won in "
			<< movesCount_ << " moves." << endl;
	}

private:
	static const int numPlayers_ = 8; // max number of players
	static const int minMoves_ = 20; // nobody wins before minMoves_
	static const int maxMoves_ = 200; // somebody wins before maxMoves_
};

// Chess - another game implementing
// primitive operations
class Chess : public Game {
public:
	void initializeGame() {
		playersCount_ = numPlayers_; // initalize players
		for (int i = 0; i < numPlayers_; ++i)
			experience_[i] = rand() % maxExperience_ + 1;
	}

	void makeMove(int player) {
		if (movesCount_ > minMoves_) {
			const int chance = (rand() % maxMoves_) / experience_[player];
			if (chance < movesCount_) playerWon_ = player;
		}
	}

	void printWinner() {
		cout << "Chess, player " << playerWon_
			<< " with experience " << experience_[playerWon_]
			<< " won in " << movesCount_ << " moves over"
			<< " player with experience " << experience_[playerWon_ == 0 ? 1 : 0]
			<< endl;
	}

private:
	static const int numPlayers_ = 2;
	static const int minMoves_ = 2; // nobody wins before minMoves_
	static const int maxMoves_ = 100; // somebody wins before maxMoves_
	static const int maxExperience_ = 3; // player's experience
							   // the higher, the greater probability of winning
	int experience_[numPlayers_];
};

int main() {
	srand(time(nullptr));

	Game* gp = nullptr;

	gp = new Dice;
	gp->playGame();
	delete gp;
/*
	// play chess 10 times
	for (int i = 0; i < 10; ++i) {
		gp = new Chess;
		gp->playGame();
		delete gp;
	}


	// play monopoly 5 times
	for (int i = 0; i < 5; ++i) {
		gp = new Monopoly;
		gp->playGame();
		delete gp;
	}
*/
}
