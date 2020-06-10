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
void processWord(string wantedWord, int n, char inputSymbol, string& wantedWord1, vector<char>& inputLetters) {

	for (int i = 1; i <= n - 2; i++) {

		if (wantedWord[i] == inputSymbol) {

			wantedWord1[i] = inputSymbol;
		}
	}

	inputLetters.push_back(inputSymbol);
	cout << "\nYour entered letters: ";

	for (int i = 0; i < inputLetters.size(); i++) {

		cout << inputLetters[i] << " ";
	}
	cout << endl;

	int maximumNumberOfAttempts = n + 3 - inputLetters.size();

	if (maximumNumberOfAttempts > 0) {

		cout << "You have " << maximumNumberOfAttempts << " attempts left\n" << endl;
		cout << wantedWord1 << endl;

	}
	else {

		cout << "You have 0 attempts left" << endl;
	}
}

void processWordOne(string wantedWord, string& wantedWord1) {

	int n = wantedWord.length();

	for (int i = 1; i <= n - 2; i++) {

		wantedWord1[i] = '-';
	}
	cout << "\nYou are entitled to " << n + 3 << " attempts\n" << endl;
	cout << wantedWord1 << endl;
}

int counting(string fullText, char symbols[], int size) {

	int count = 0, check = 0;

	for (int i = 0; i < fullText.size(); i++) {

		for (int j = 0; j < size; j++) {

			if (fullText[i] == symbols[j]) {

				count++;
			}
		}
	}

	for (int j = 0; j < size; j++) {

		if (fullText[fullText.size() - 1] != symbols[j]) {

			check++;
		}
	}

	if (check == size) {

		count++;
	}

	return count;
}

void wordCountMenu(string fullText) {

	char symbols[] = {' '};
	int wordCount = counting(fullText, symbols, 1);

	cout << "The total amount of words in this text is: " << wordCount + 1 << endl;
	cout << endl;
}

void sentenceCountMenu(string fullText) {

	char symbols[] = { '.','!','?'};
	int sentenceCount = counting(fullText, symbols, 3);

	cout << "The total amount of sentences in this text is: " << sentenceCount << endl;
	cout << endl;
}

void isWordInTextMenu() {

}

void howManyTimesIsWordInTextMenu() {

}

void mostCommonWordsMenu() {

}

void addWordsInArray(string *wordsInText, string fullText) {

	char symbols[] = { '.','!','?',',' };
	int wordIndex = 0;
	int firstLetter = 0;

	for (int i = 0; i < fullText.size(); i++) {
		if (fullText[i] == ' ') {

			int wordLength = i - firstLetter;
			wordsInText[wordIndex] = fullText.substr(firstLetter, wordLength);
			wordIndex++;
			firstLetter = i + 1;
		}
	}

	if (fullText[fullText.size() - 1] != ' ') {

		wordsInText[wordIndex] = fullText.substr(firstLetter);
	    wordIndex++;
	}

	for (int i = 0; i < wordIndex; i++){

		for (int j = 0; j < 4; j++) {

			if (wordsInText[i][wordsInText[i].size() - 1] == symbols[j]) {

				wordsInText[i].erase(wordsInText[i].size() - 1);
			}
		}
	}


	for (int i = 0; i < wordIndex; i++) {

		for (int j = 0; j < wordsInText[i].size(); j++) {

			wordsInText[i][j] = tolower(wordsInText[i][j]);
		}

	}
}

void textMenu() {

	int option;
	string fullText;
	string wordsInText[100];

	cout << "(To quit entering text, press \"Enter\")"<<endl;
	cout << endl;

	cin.ignore();
	getline(cin, fullText,'\n');
	cout << endl;

	addWordsInArray(wordsInText,fullText);

	cout << "What do you want to know about this text? " << endl;
	cout << endl;
	cout << "1. Number of words"<<endl;
	cout << "2. Number of sentences" << endl;
	cout << "3. Does it contain a specific word"<<endl;
	cout << "4. How many times is a specific word mentioned"<<endl;
	cout << "5. Most commonly used words" << endl;
	//cout << "6. Return back to the main menu" << endl;
	cout << endl;

	cout << "Your choice: ";
	cin >> option;
	cout << endl;

	switch (option) {

		case 1:
			wordCountMenu(fullText);
			break;

		case 2:
			sentenceCountMenu(fullText);
			break;
	/*case 3:isWordInTextMenu(); break;
	case 4:howManyTimesIsWordInTextMenu(); break;
	case 5:mostCommonWordsMenu(); break;
		case 6:
			break;*/
	}

}

void gamesMenu() {

	int option;

	cout << "Choose the game you want to play" << endl;
	cout << endl;
	cout << "1. Hangman" << endl;
	cout << "2. Riddles" << endl;
	cout << "3. Return to the main menu" << endl;
	cout << endl;

	cout << "Your choice: ";
	cin >> option;

	/*switch (option) {
		
	}*/
}

bool mainMenu(){

	int option;
	string dashes, lessDashes;

	dashes.assign(14, '-');

	lessDashes = dashes.substr(0, 3);

	cout << "\t\t       " << dashes << endl;
	cout << "\t\t " << lessDashes << "  |  MAIN  MENU  |  " << lessDashes << endl;
	cout << "\t\t       " << dashes << endl;
	cout << endl;

	cout << "1. Input a text and get analysis about it" << endl;
	cout << "2. Play games" << endl;
	cout << "3. Exit" << endl;
	cout << endl;

	cout << "Enter an option: ";
	cin >> option;
	cout << endl;

	switch (option) {

		case 1:
			textMenu();
			break;

		case 2:
			gamesMenu(); 
			break;

		case 3:
			cout << "Thanks for using our program. See you soon!" << endl;
			return false;
			break;

		default:
			cout << "There seems to be a problem with your input. "
				"Please try again." << endl;
			cout << endl;
			break;
	}

	return true;
}

void greetingsMessage() {


	string dashes;

	dashes.assign(62, '-');

	cout << endl;
	cout << "\t\t\t    HELLO!" << endl;
	cout << endl;
	cout << dashes << endl;
	cout << "Welcome to our newly developed program connected to strings."
		"\nBelow, as you can see, is located our main menu from which you \n"
		"can select and try out one or more of our program's features. \nWe hope you like it!" << endl;
	cout << dashes << endl;
	cout << endl;

}

int main() {

	srand(time(0));
	bool showMainMenu = 0;

	greetingsMessage();

	do {
		
		showMainMenu = mainMenu();

	} while (showMainMenu);
}