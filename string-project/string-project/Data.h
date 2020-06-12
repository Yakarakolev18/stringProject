#pragma once
#include <iostream>
#include <string>
#include "Structures.h"
using namespace std;

long int randomInt(int, int);

int readInt(string);

string generatingWords();

void processHiddenWord(string, string&);

string generatingWords();

void processHiddenWord(string, string&);

int addWordsInArray(WORD*, string);

int counting(string, char[], int);

int specificWordCount(WORD*, int, string);

void countEachWordInText(WORD*, int);

void sortByCount(WORD*, int);

RIDDLE generateRiddles();

string generateRiddleAnswers(RIDDLE);

bool isCorrect(string, string);
