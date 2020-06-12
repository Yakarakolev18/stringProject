#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <vector>
#include "Structures.h"
#include "Data.h"
#include "Presentation (menus).h"
using namespace std;

//main function
int main() {

	srand(time(0));
	bool showMainMenu = 0;

	//calls the greetings message
	greetingsMessage();

	//shows the main menu
	do {

		showMainMenu = mainMenu();

	} while (showMainMenu); 
}