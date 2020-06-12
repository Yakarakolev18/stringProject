#include "Structures.h"
#include "Presentation (menus).h"
#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <vector>
using namespace std;

//returns random integer in a range
long int randomInt(int min, int max) {

	int r = rand();
	long int randNum = r % ( max - min ) + min;

	return randNum;
}

//checks if the input is an integer
int readInt(string message) {

	int number;

	//while loop until the value entered is an integer
	while (!( cin >> number )) {

		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cout << endl;
		cout << "There seems to be a problem with your input. " << endl;
		cout << "Please keep in mind that you should enter a number." << endl;
		cout << endl;
		//shows different messages depending on the function it is used in
		cout << message;
	}

	return number;
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

/*extracts separate words from the text string and
puts them in the array of structures "wordsInText"*/
int addWordsInArray(WORD* wordsInText, string fullText) {

	char symbols[] = { '.','!','?',',' };
	int wordIndex = 0;
	int firstLetter = 0;

	//loop for putting words in the array
	for (int i = 0; i < fullText.size(); i++) {

		if (fullText[i] == ' ') {

			int wordLength = i - firstLetter;
			wordsInText[wordIndex].word = fullText.substr(firstLetter, wordLength);
			wordIndex++;
			firstLetter = i + 1;
		}
	}

	//adds one more word to the array if the text string does not end with " "
	if (fullText[fullText.size() - 1] != ' ') {

		wordsInText[wordIndex].word = fullText.substr(firstLetter);
		wordIndex++;
	}

	//checks if the words contain any symbols and if they do, it removes them
	for (int i = 0; i < wordIndex; i++) {

		for (int j = 0; j < 4; j++) {

			if (wordsInText[i].word[wordsInText[i].word.size() - 1] == symbols[j]) {

				wordsInText[i].word.erase(wordsInText[i].word.size() - 1);
			}
		}
	}

	//lowers all letters of all the words in the array
	for (int i = 0; i < wordIndex; i++) {

		for (int j = 0; j < wordsInText[i].word.size(); j++) {

			wordsInText[i].word[j] = tolower(wordsInText[i].word[j]);
		}
	}

	//returns the size of array "wordsInText"
	return wordIndex;
}

//counts something (e.g. sentences) by given characters
int counting(string fullText, char symbols[], int size) {

	int count = 0, check = 0;

	/*counts how many times the characters from the array symbols[]
	are present in the string*/
	for (int i = 0; i < fullText.size(); i++) {

		for (int j = 0; j < size; j++) {

			if (fullText[i] == symbols[j]) {

				count++;
			}
		}
	}

	/*checks if the last element of the string is equal to each of the characters
	//from the array symbols[] and if not, it adds 1 to "check" */
	for (int j = 0; j < size; j++) {

		if (fullText[fullText.size() - 1] != symbols[j]) {

			check++;
		}
	}

	/*checks if the last element from the string is different
	from all the symbols and if it is, it adds 1 to "count"*/
	if (check == size) {

		count++;
	}

	//returns the number of the thing we are counting
	return count;
}

//counts how many times a given  word is present in the text
int specificWordCount(WORD* wordsInText, int wordCount, string wordForCheck) {

	int searchedWordCount = 0;

	for (int i = 0; i < wordCount; i++) {

		if (wordsInText[i].word == wordForCheck)
			searchedWordCount++;
	}

	return searchedWordCount;
}

//counts how many times each word in the text is present
void countEachWordInText(WORD* wordsInText, int wordCount) {

	for (int i = 0; i < wordCount; i++) {

		if (wordsInText[i].marked == false) {

			wordsInText[i].count++;

			for (int j = i + 1; j < wordCount; j++) {

				if (wordsInText[j].marked == false) {

					if (wordsInText[i].word == wordsInText[j].word) {

						wordsInText[i].count++;
						wordsInText[j].marked = true;
					}
				}
			}
		}
	}
}

//sorts the elements in the array "wordsInText" from most to least common word in the text
void sortByCount(WORD* wordsInText, int wordCount) {

	for (int i = 0; i < wordCount - 1; i++) {

		for (int j = 0; j < wordCount - i - 1; j++) {

			if (wordsInText[j].count < wordsInText[j + 1].count) {

				swap(wordsInText[j], wordsInText[j + 1]);
			}
		}
	}
}

//generates random riddle from a file
RIDDLE generateRiddles() {

	RIDDLE riddle;

	vector <string> lines;
	int totalLinesRiddles = 0;
	string line;

	//checks if the file can be opened
	ifstream file("riddles.txt");
	if (!file.is_open()) {

		riddle.index = -1;
		riddle.sentence = "There was a problem with the file.";
	}

	//counts the lines and pushes the content into a vector
	while (getline(file, line)) {

		totalLinesRiddles++;
		lines.push_back(line);
	}

	//gets a random number
	riddle.index = randomInt(0, totalLinesRiddles);

	//gets the riddle on that index
	riddle.sentence = lines[riddle.index];

	file.close();

	//returns the riddle's index and text
	return riddle;
}

//generates the answer corresponding to the random chosen riddle
string generateRiddleAnswers(RIDDLE riddle) {

	vector <string> lines;
	int totalLinesAnswers = 0;
	string line;
	string generatedAnswer;

	//checks if the file can be opened
	ifstream file("answers.txt");
	if (!file.is_open()) {

		return "Error opening file!";
	}

	//counts the number of lines and pushes their content in a vector
	while (getline(file, line)) {

		totalLinesAnswers++;
		lines.push_back(line);
	}

	//gets the word on the same index as the riddle
	generatedAnswer = lines[riddle.index];

	file.close();

	//returns the answer
	return generatedAnswer;
}

//checks if the riddle answer is the same as the user's input
bool isCorrect(string answer, string userInput) {

	if (userInput.compare(answer) == 0) {

		//if it is
		return true;
	} else {

		//if it is not
		return false;
	}
}
