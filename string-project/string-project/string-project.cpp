#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <vector>
using namespace std;

long int randomInt(int min, int max) {

	int r = rand();
	long int randNum = r % ( max - min ) + min;
	return randNum;
}

bool generatingWords() {

	int randomNumber;

	string line;
	string myText;

	vector <string> lines;
	int totalLines = 0;

	int again;

	randomNumber = randomInt(0, 9);

	ifstream file("words.txt");
	if (!file.is_open()) {

		cout << "Error opening file!";
		return false;
	}

	while (getline(file, line)) {

		totalLines++;
		lines.push_back(line);
	}

	cout << lines[randomNumber] << endl;

	file.close();

	cin >> again;

	switch (again) {

		case 1: return true;
			break;

		case 2:
			return false;
			break;
	}

}

void textMenu() {
	int option;
	string fullText;
	getline(cin, fullText);
	cout << endl;

	cout << "What do you want to know about this text? " << endl;
	cout << endl;

	cout << "1. How many words in total it consists of"<<endl;
	cout << "2. How many sentences in total it contains" << endl;
	cout << "3. If a specific word is present in the text"<<endl;
	cout << "4. How many times a specific word is mentioned"<<endl;
	cout << "5. Which are the most commonly used words" << endl;
	cout << endl;

	cout << "Enter an option: ";
	cin >> option;
}

void gamesMenu() {
	
	cout << "1. Hangman" << endl;
	cout << "2. Riddles" << endl;
}

void mainMenu(){
	cout << "\t\t\t    HELLO!" << endl;
	cout << "--------------------------------------------------------------" << endl;
	cout << "Welcome to our newly developed program connected with strings.\nBelow, as you can see, is located our main menu from which you \ncan select and try out one or more of our program's features. \nWe hope you like it!" << endl;
	cout << "--------------------------------------------------------------" << endl;
	cout << "\t\t       --------------" << endl;
	cout << "\t\t ---  |   MAIN MENU  |  ---" << endl;
	cout << "\t\t       --------------" << endl;
	cout << endl;

	int option;

	cout << "1. Input a text and get analysis about it" << endl;
	cout << "2. Play games" << endl;
	cout << "3. Exit" << endl;

	cout << endl;
	cout << "Enter an option: ";
	cin >> option;
	cout << endl;

	switch (option) {
	case 1:textMenu(); break;
	case 2:gamesMenu(); break;
	case 3:exit(0); break;
	}
}

int main() {
	srand(time(0));

	mainMenu();
	system("PAUSE");
}