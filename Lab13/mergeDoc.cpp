//Dylan Dennison
//Merge command and memento & add history and redo
//why use microsoft word when you can make your own
//05/01/21

#include <iostream>
#include <vector>
#include <string>
#include <stack>

using std::vector; using std::string;
using std::cout; using std::cin; using std::endl;

// receiver
class Document {
public:

	Document(const vector <string>& lines = {}) : lines_(lines) {}

	// actions
	void insert(int line, const string& str) {
		const int index = line - 1;
		if (index <= lines_.size())
			lines_.insert(lines_.begin() + index, str);
		else
			cout << "line out of range" << endl;
	}

	string remove(int line) {
		const int index = line - 1;
		string deletedLine = "";
		if (index < lines_.size()) {
			deletedLine = lines_[index];
			lines_.erase(lines_.begin() + index);
		}
		else
			cout << "line out of range" << endl;
		return deletedLine;
	}

	void show() {
		for (int i = 0; i < lines_.size(); ++i)
			cout << i + 1 << ". " << lines_[i] << endl;
	}

private:
	vector<string> lines_;
};

// abstract command
class Command {
public:
	Command(Document* doc) : doc_(doc) {}
	virtual void execute() = 0;
	virtual void unexecute() = 0;
	virtual ~Command() {}
	virtual void show() = 0; //virual show
	virtual int getID() = 0;     //for redo
	virtual string getString() = 0;
protected:
	Document* doc_;
};

// two concrete commands
class InsertCommand : public Command {
public:
	InsertCommand(Document* doc, int line, const string& str) :
		Command(doc), line_(line), str_(str) {}
	void execute() override { doc_->insert(line_, str_); }
	void unexecute() override { doc_->remove(line_); }
	void show() override {
		cout << "insert " << str_ << " at line " << line_ << endl;  //adding show 
	}

	int getID() override {
		return line_;
	}
	string getString() override {
		return str_;
	}

private:
	int line_;
	string str_;
};


class EraseCommand : public Command {
public:
	EraseCommand(Document* doc, int line) :
		Command(doc), line_(line), str_("") {}
	void execute() override { str_ = doc_->remove(line_); }
	void unexecute() override { doc_->insert(line_, str_); }
	void show() override {
		cout << "erased line " << line_ << endl;    //adding show
	}

	int getID() override {
		return line_;
	}
	string getString() override {
		return str_;
	}
private:
	int line_;
	string str_;
};

class Memento; //forward dec

// client
class DocumentWithHistory {
public:
	DocumentWithHistory(const vector<string>& text = {}) : doc_(text) {}

	void insert(int line, string str) {
		Command* com = new InsertCommand(&doc_, line, str);
		com->execute();
		doneCommands_.push(com);
	}

	void erase(int line) {
		Command* com = new EraseCommand(&doc_, line);
		com->execute();
		doneCommands_.push(com);
	}

	void undo() {
		if (doneCommands_.size() != 0) {
			Command* com = doneCommands_.top();
			doneCommands_.pop();
			com->unexecute();
			delete com; // don't forget to delete command
		}
		else
			cout << "no commands to undo" << endl;
	}

	
	void history() {
		std::stack<Command*> tmp; //for after we print we still have the done commands

		cout << "HISTORY:" << endl;
		//printing the commands 
		for (int i = 0; !doneCommands_.empty(); i++) {
			cout << i + 1 << ": ";
			Command* com = doneCommands_.top();
			com->show();
			doneCommands_.pop();   // printing each command then storeing it into the temp stack
			tmp.push(com);
		}

		//putting the commandsfrom tmp stack back into done commands
		while (!tmp.empty()) {
			Command* com = tmp.top();
			tmp.pop();
			doneCommands_.push(com);
		}

	}

	void redo(int line) {
		std::stack<Command*> tmp = doneCommands_; //copy into tmp
		Command* com; //create a command pointer

		for (int i = 1; !tmp.empty(); i++) {
			if (i == line) {
				com = tmp.top(); //breaks when history line is found
				break;
			}
			tmp.pop(); //pops out of tmp stack
		}

		doneCommands_.push(com); //pushes command into stack
		com->execute(); //executes the redo command
	}

	void show() { doc_.show(); }

	Memento* createMemento() const; //merging into document with history
	void rollBack(Memento*);

private:
	Document doc_;
	std::stack<Command*> doneCommands_;
};

//adding memento class 
class Memento {
public:
	Memento(const DocumentWithHistory& doc) : doc_(doc) {}
	const DocumentWithHistory& getState() const { return doc_; }
private:
	const DocumentWithHistory doc_;
};

Memento* DocumentWithHistory::createMemento() const {
	// copying the Document itself
	return new Memento(*this);
}

void DocumentWithHistory::rollBack(Memento* mem) {
	*this = mem->getState();  // copying back
}

// invoker
int main() {
	DocumentWithHistory his({
	  "Lorem Ipsum is simply dummy text of the printing and typesetting",
	  "industry. Lorem Ipsum has been the industry's standard dummy text",
	  "ever since the 1500s, when an unknown printer took a galley of",
	  "type and scrambled it to make a type specimen book. It has",
	  "survived five centuries." });

	Memento* sHistory = nullptr;//instance of memento 
	char option;
	do {
		cout << endl;
		his.show();
		cout << endl;

		cout << "Enter option (i)nsert line (e)rase line (u)undo last command (c)heckpoint roll(b)ack (h)history (r)edo command: ";
		cin >> option;

		int line; string str;
		switch (option) {
		case 'i':
			cout << "line number to insert: ";
			cin >> line;
			cout << "line to insert: ";
			cin.get(); // removes end-of-line character so getline() works correctly
			getline(cin, str);
			his.insert(line, str);
			break;

		case 'e':
			cout << "line number to remove: ";
			cin >> line;
			his.erase(line);
			break;

		case 'u':
			his.undo();
			break;

		case 'c':
			sHistory = his.createMemento();
			break;

		case 'b':
			if (sHistory != nullptr) {
				his.rollBack(sHistory);
				delete sHistory; sHistory = nullptr;
			}
			break;

		case 'h':
			his.history();
			break;

		case 'r':
			int lineNum;
			cout << "Enter Line that you want to redo: ";
			cin >> lineNum;
			his.redo(lineNum);
			break;
		}

		
	} while (option == 'i' || option == 'e' || option == 'u' || option == 'c' || option == 'b' || option == 'h' || option == 'r');
}
