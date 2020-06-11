#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <vector>
using namespace std;

struct WORD {
	string word = "";
	int count = 0;
	bool marked = false;
};

//returns random integer in a range
long int randomInt(int min, int max) {

	int r = rand();
	long int randNum = r % (max - min) + min;

	return randNum;
}

//generates a random word from a file by using the random number
string generatingWords() {

	int randomNumber;
	string generatedWord;

	//vector to store the words in
	vector <string> lines;
	int totalLines = 0;
	string line;

	//opens the file
	ifstream file("words.txt");
	if (!file.is_open()) {

		//if the file can't be opened
		return "Error opening file!";
	}

	//counts all the lines in the file
	while (getline(file, line)) {

		totalLines++;
		lines.push_back(line);
	}

	//generates the random number
	randomNumber = randomInt(0, lines.size());

	//puts the chosen word in a variable
	generatedWord = lines[randomNumber];

	//closes the file
	file.close();

	//returns the generated word
	return generatedWord;

}

//counts the left attempts and used letters and shows them
void processWord(string wantedWord, int numberOfLetters, char inputSymbol, string& wantedWordHidden, vector<char>& inputLetters) {

	for (int i = 1; i <= numberOfLetters - 2; i++) {

		if (wantedWord[i] == inputSymbol) {

			wantedWordHidden[i] = inputSymbol;
		}
	}

	//vector which contains the used letters
	inputLetters.push_back(inputSymbol);
	cout << "\nYour entered letters: ";

	//shows the used letters
	for (int i = 0; i < inputLetters.size(); i++) {

		cout << inputLetters[i] << " ";
	}
	cout << endl;

	//calculates the attempts needed for a word to be guessed
	int maximumNumberOfAttempts = numberOfLetters + 3 - inputLetters.size();

	//shows the number of left attempts
	if (maximumNumberOfAttempts > 0) {

		//if there are some available
		cout << "You have " << maximumNumberOfAttempts << " attempts left\n" << endl;
		cout << wantedWordHidden << endl;

	}
	else {
		//if there are none available
		cout << "You have 0 attempts left" << endl;
	}
}

//exchanges letters to dashes to hide the word
void processHiddenWord(string wantedWord, string& wantedWordHidden) {

	int numberOfLetters = wantedWord.length();

	for (int i = 1; i <= numberOfLetters - 2; i++) {

		wantedWordHidden[i] = '-';
	}

	//shows max number of attempts
	cout << "\nYou are entitled to " << numberOfLetters + 3 << " attempts\n" << endl;
	cout << wantedWordHidden << endl;
}

//hangman game
bool gameHangman() {

	string wantedWord, wantedWordHidden;
	vector<char> inputLetters;
	int again;
	
	//gets the word
	wantedWord = generatingWords();

	wantedWordHidden = wantedWord;
	int numberOfLetters = wantedWord.length();
	int maximumNumberOfAttempts = numberOfLetters + 3;
	char inputSymbol;

	//hides the letters
	processHiddenWord(wantedWord, wantedWordHidden);

	while (wantedWord.compare(wantedWordHidden) != 0 && maximumNumberOfAttempts > 0) {

		cout << "\nInput letter: ";
		cin >> inputSymbol;
		maximumNumberOfAttempts--;
		processWord(wantedWord, numberOfLetters, inputSymbol, wantedWordHidden, inputLetters);
		cout << endl;
	}

	//results
	if (maximumNumberOfAttempts > 0) {

		//if the word is guessed
		cout << endl;
		cout << "You win!" << endl;
		inputLetters.clear();
	}
	else {
		//if the word is not guessed
		cout << endl;
		cout << "You lost! The word was " << wantedWord << "." << endl;
		inputLetters.clear();
	}

	//asks if another round is wanted
	cout << endl;
	cout << "Would you like to play again?" << endl;
	cout << "1. Yes, let's go!" << endl;
	cout << "2. No, thanks." << endl;
	cout << endl;

	cout << "Your choice: ";
	cin >> again;

	switch (again) {

	case 1:
		//if it is wanted
		return true;
		break;

	case 2:
		//if it isn't wanted
		return false;
		break;

	default:
		cout << "There seems to be a problem with your input."
			"Please try again!" << endl;
		break;
	}

	return true;

}





int addWordsInArray(WORD* wordsInText, string fullText) {

	char symbols[] = { '.','!','?',',' };
	int wordIndex = 0;
	int firstLetter = 0;

	for (int i = 0; i < fullText.size(); i++) {
		if (fullText[i] == ' ') {

			int wordLength = i - firstLetter;
			wordsInText[wordIndex].word = fullText.substr(firstLetter, wordLength);
			wordIndex++;
			firstLetter = i + 1;
		}
	}

	if (fullText[fullText.size() - 1] != ' ') {

		wordsInText[wordIndex].word = fullText.substr(firstLetter);
		wordIndex++;
	}

	for (int i = 0; i < wordIndex; i++) {

		for (int j = 0; j < 4; j++) {

			if (wordsInText[i].word[wordsInText[i].word.size() - 1] == symbols[j]) {

				wordsInText[i].word.erase(wordsInText[i].word.size() - 1);
			}
		}
	}


	for (int i = 0; i < wordIndex; i++) {

		for (int j = 0; j < wordsInText[i].word.size(); j++) {

			wordsInText[i].word[j] = tolower(wordsInText[i].word[j]);
		}

	}

	return wordIndex;
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

void wordCountMenu(int wordCount) {
	cout << "The total amount of words in this text is: " << wordCount << endl;
	cout << endl;
}

void sentenceCountMenu(string fullText) {

	char symbols[] = { '.','!','?' };
	int sentenceCount = counting(fullText, symbols, 3);

	cout << "The total amount of sentences in this text is: " << sentenceCount << endl;
	cout << endl;
}

int specificWordCount(WORD *wordsInText, int wordCount, string wordForCheck) {
	int searchedWordCount = 0;

	for (int i = 0; i < wordCount; i++)
	{
		if (wordsInText[i].word == wordForCheck)
			searchedWordCount++;
	}
	
	return searchedWordCount;
}

void isWordInTextMenu(WORD *wordsInText, int wordCount) {
	string wordForCheck;
	cout << "Enter the word you want to search for: ";
	cin >> wordForCheck;
	cout << endl;

	if (specificWordCount(wordsInText, wordCount, wordForCheck) > 0)
		cout << "Yes, \"" << wordForCheck << "\" is present in the text!" << endl;
	else
		cout << "No, \"" << wordForCheck << "\" is not present in the text!" << endl;
	cout << endl;
}

void howManyTimesIsWordInTextMenu(WORD* wordsInText, int wordCount) {
	string wordForCount;
	cout << "Enter the word you want to know how many times is present in the text: ";
	cin >> wordForCount;
	cout << endl;

	cout << "The word \"" << wordForCount << "\" is present " << specificWordCount(wordsInText, wordCount, wordForCount) << " time/s in the text."<<endl;
	cout << endl;
}

void countEachWordInText(WORD* wordsInText, int wordCount) {

	for (int i = 0; i < wordCount; i++) {
		
		if (wordsInText[i].marked == false) {
			wordsInText[i].count++;
			for (int j = i+1; j < wordCount; j++) {
				if (wordsInText[j].marked == false) {
					if (wordsInText[i].word== wordsInText[j].word) {
						wordsInText[i].count++;
						wordsInText[j].marked = true;
					}
				}
			}
		}
	}

}

void eachWordCountMenu(WORD* wordsInText, int wordCount) {
	for (int i = 0; i < wordCount; i++) {
		if (wordsInText[i].marked == false) {
			cout << "\"" << wordsInText[i].word << "\" is used " << wordsInText[i].count << " time/s in the text" << endl;
		}
	}
	cout << endl;
}

void sortByCount(WORD* wordsInText, int wordCount) {
	for (int i = 0; i < wordCount - 1; i++) {
		for (int j = 0; j < wordCount - i - 1; j++) {
			if (wordsInText[j].count < wordsInText[j + 1].count) {
				swap(wordsInText[j], wordsInText[j + 1]);
			}
		}
	}
}

void mostCommonWordsMenu(WORD* wordsInText, int wordCount) {
	sortByCount(wordsInText, wordCount);
	cout << "The three most common words in the text are: "<<endl;
	for (int i = 0; i < 3; i++)
		cout << i + 1 << ". \"" << wordsInText[i].word << "\" (" << wordsInText[i].count << " time/s) " << endl;

	cout << endl;
}




void textMenu() {

	int option;
	string fullText;
	WORD wordsInText[100];

	cout << "(To quit entering text, press \"Enter\")" << endl;
	cout << endl;

	cin.ignore();
	getline(cin, fullText, '\n');
	cout << endl;

	int wordCount = addWordsInArray(wordsInText, fullText);

	countEachWordInText(wordsInText, wordCount);

	bool continueMenu = 0;

	while (continueMenu == 0) {
		cout << "What do you want to know about this text? " << endl;
		cout << endl;
		cout << "1. Number of words" << endl;
		cout << "2. Number of sentences" << endl;
		cout << "3. Does it contain a specific word" << endl;
		cout << "4. How many times is a specific word mentioned" << endl;
		cout << "5. How many times each word in the text is used" << endl;
		cout << "6. Most commonly used words" << endl;
		cout << "7. Return back to the main menu" << endl;
		cout << endl;


		cout << "Your choice: ";
		cin >> option;
		cout << endl;

		switch (option) {

		case 1:
			wordCountMenu(wordCount);
			break;

		case 2:
			sentenceCountMenu(fullText);
			break;
		case 3:
			isWordInTextMenu(wordsInText, wordCount);
			break;
		case 4:
			howManyTimesIsWordInTextMenu(wordsInText, wordCount);
			break;
		case 5:
			eachWordCountMenu(wordsInText, wordCount);
			break;
		case 6:
			mostCommonWordsMenu(wordsInText, wordCount);
			break;
		case 7:
			continueMenu = 1;
			break;
		};
	};
}


void gamesMenu() {

	int option;
	bool hangman = false;

	bool continueMenu = 0;

	while (continueMenu == 0) {
		cout << "Choose the game you want to play" << endl;
		cout << endl;
		cout << "1. Hangman" << endl;
		cout << "2. Riddles" << endl;
		cout << "3. Return to the main menu" << endl;
		cout << endl;

		cout << "Your choice: ";
		cin >> option;

		switch (option) {
		case 1: hangman = gameHangman();
			while (hangman)
			{
				hangman = gameHangman();
			}
			break;
		case 6:
			continueMenu = 1;
			break;
		}
	};
}

bool mainMenu() {

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