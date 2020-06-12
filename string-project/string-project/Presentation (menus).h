#pragma once
#include "Structures.h"
#include <iostream>
#include <vector>
using namespace std;

void processWord(string, int, char, string&, vector<char>&);

bool playAgain();

bool gameHangman();

void wordCountMenu(int);

void sentenceCountMenu(string);

void isWordInTextMenu(WORD*, int);

void howManyTimesIsWordInTextMenu(WORD*, int);

void eachWordCountMenu(WORD*, int);

void mostCommonWordsMenu(WORD*, int);

bool riddlesMenu();

void gamesMenu();

bool mainMenu();

void textMenu();

void greetingsMessage();
