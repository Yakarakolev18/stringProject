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



int counting(string fullText, char symbols[], int size) {
	int count = 0;
	for (int i = 0; i < fullText.size(); i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (fullText[i] == symbols[j])
			{
				count++;
			}
		}
	}

	return count;
}

void wordCountMenu(string fullText) {
	char symbols[] = {' '};
	int wordCount = counting(fullText,symbols,1);

	cout << "The total amount of words in this text is: " << wordCount + 1 <<endl;
	cout << endl;
}

void sentenceCountMenu(string fullText) {
	char symbols[] = { '.','!','?' };
	int sentenceCount = counting(fullText, symbols,3);

	cout << "The total amount of sentences in this text is: " << sentenceCount<< endl;
	cout << endl;
}

void isWordInTextMenu() {

}

void howManyTimesIsWordInTextMenu() {

}

void mostCommonWordsMenu() {

}



void textMenu() {

	int option;
	string fullText;

	cout << "(To quit entering text, press \"Enter\")"<<endl;
	cout << endl;

	cin.ignore();
	getline(cin, fullText,'\n');
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
	cout << endl;

	switch (option) {
	case 1:wordCountMenu(fullText); break;
	case 2:sentenceCountMenu(fullText); break;
	/*case 3:isWordInTextMenu(); break;
	case 4:howManyTimesIsWordInTextMenu(); break;
	case 5:mostCommonWordsMenu(); break;*/
	}
}

void gamesMenu() {
	int option;

	cout << "1. Hangman" << endl;
	cout << "2. Riddles" << endl;
	cout << endl;

	cout << "Enter the number of the game you would like to play: ";
	cin >> option;

	/*switch (option) {
		
	}*/
}

void mainMenu(){
	cout << "\t\t\t    HELLO!" << endl;
	cout << endl;
	cout << "--------------------------------------------------------------" << endl;
	cout << "Welcome to our newly developed program connected with strings.\nBelow, as you can see, is located our main menu from which you \ncan select and try out one or more of our program's features. \nWe hope you like it!" << endl;
	cout << "--------------------------------------------------------------" << endl;
	cout << endl;
	cout << "\t\t       --------------" << endl;
	cout << "\t\t ---  |  MAIN  MENU  |  ---" << endl;
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