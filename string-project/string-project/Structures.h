#pragma once
#include <string>
#include <iostream>
using namespace std;

//for the text analysis functions
struct WORD {

	string word = " ";
	int count = 0;
	bool marked = false;
};

//for the riddles game
struct RIDDLE {

	int index = 0;
	string sentence = " ";
};