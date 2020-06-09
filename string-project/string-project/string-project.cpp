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

int main() {

	srand(time(0));
}