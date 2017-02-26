// Journal program
// Made by Nishir Shelat

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <iomanip>
#include <sstream>

using namespace std;

// Returns false if the entered password matches the given password
bool checkPassword(string givenPassword) {
	// Ask the user for the password
	cout << "Please enter the password (case-sensitive): ";
	// Store and compare tha passwords
	string inputPassword;
	getline(cin,inputPassword);
	if(inputPassword == givenPassword) {
		return false;
	}
	return true;
}

// Prints the menu
void printMenu() {
	system("cls");
	cout << "Welcome to the C++ Journal" << endl;
	cout << "Created by Nishir Shelat" << endl << endl;
	cout << "Please select an option:" << endl;
	cout << "1) Write a new entry." << endl;
	cout << "2) Read an existing entry." << endl;
	cout << "3) Quit the program." << endl << endl;
	cout << ">> ";
}

// Takes an int and returns the string form
string int_to_string(int i) {
	// Open a string stream
	stringstream int_to_string;
	int_to_string << i;
	// Return the converted value
	return int_to_string.str();
}

// Reads all the current files and returns the next free int
int findInt() {
	int i = 1;
	// Loop until testStream fails
	while(1) {
		string name = int_to_string(i) + ".txt";
		fstream testStream;
		testStream.open(name.c_str());
		if(!testStream) {
			break;
		}
		i++;
	}
	return i;
}

// Creates a text file for the next available int
void createFile(int i) {
	string name = int_to_string(i) + ".txt";
	ofstream journal;
	journal.open(name.c_str());
	journal.close();
}

// Encrypts a string
string encryptString(string entry) {
	for(unsigned int i = 0; i < entry.length(); i++) {
		entry[i] += 1;
	}
	return entry;
}

// Decrypts a string
string decryptString(string entry) {
	for(unsigned int i = 0; i < entry.length(); i++) {
		entry[i] -= 1;
	}
	return entry;
}

// Decrypts a char
char decryptChar(char entry) {
	entry -= 1;
	return entry;
}

// Returns true if an entry meets the min requirements
bool checkEntry(int i) {
	// Open the file stream
	string name = int_to_string(i) + ".txt";
	ifstream journal;
	journal.open(name.c_str());
	// Check for a minimum of 15 chars
	char temp;
	int counter = 0;
	while(journal >> temp) {
		if(journal.fail()) {
			break;
		}
		counter++;
	}
	if(counter < 15) {
		return false;
	}
	else {
		return true;
	}
}

// Writes an entry
void writeEntry() {
	// Clear the screen
	system("cls");
	// Create the new file
	int i = findInt();
	createFile(i);
	// Open the file
	string name = int_to_string(i) + ".txt";
	ofstream journal;
	journal.open(name.c_str());
	// Prompt the user for the entry
	cout << "Please type in your journal entry (min 15 characters)." << endl;
	cout << "Enter \"EXIT\" when you are done." << endl;
	cout << "Note that any text entered after typing \"EXIT\" will not be saved." << endl << endl;
	string entry;
	while(entry.find(encryptString("EXIT")) == -1) {
		getline(cin,entry);
		if(entry.find("EXIT") != -1) {
			entry = entry.substr(0,entry.find("EXIT"));
			entry = encryptString(entry);
			journal << entry << " ";
			break;
		}
		entry = encryptString(entry);
		journal << entry << " ";
	}
	journal.close();
	if(!checkEntry(i)) {
		// Print an error message and delete the file
		system("cls");
		cout << "Error - An entry must have at least 15 characters. Your file has not been saved." << endl << endl;
		remove(name.c_str());
		system("pause");
	}
}

// Given an int, opens the corresponding file and returns it
string loadEntry(int i) {
	// Open the file
	string name = int_to_string(i) + ".txt";
	ifstream journal;
	journal.open(name.c_str());
	string entry;
	getline(journal,entry);
	return entry;
}

// Prints all the current entry previews
void printPreviews() {
	// Open each entry and print the first 15 chars
	for(unsigned int i = 1; i < findInt(); i++) {
		string name = int_to_string(i) + ".txt";
		ifstream journal;
		journal.open(name.c_str());
		cout << i << ") \"";
		for(int j = 0; j < 15; j++) {
			char entry;
			journal >> entry;
			cout << decryptChar(entry);
		}
		cout << "...\"" << endl;
	}
}

// Reads an entry
void readEntry() {
	// Clear the screen
	system("cls");
	// Display the current entries
	printPreviews();
	cout << endl;
	cout << "Please type in the number that corresponds to the entry you wish to read." << endl << endl;
	cout << ">> ";
	string choice;
	getline(cin,choice);
	int i = atoi(choice.c_str());
	if(!(i > 0 && i < findInt())) {
		// Error message and quit
		system("cls");
		cout << "Error - That is not a valid entry number." << endl << endl;
		system("pause");
		return;
	}
	system("cls");
	string entry = decryptString(loadEntry(i));
	entry = entry.substr(0,entry.length()-2);
	cout << entry;
	cout << endl << endl;
	system("pause");
}

int main() {
	// Clear the screen
	system("cls");
	// Ask for a password
	while(checkPassword("password")) {
		cout << endl << "Incorrect, try again." << endl << endl;
	}
	// Print the menu until a valid option is selected
	string response;
	do {
		printMenu();
		getline(cin, response);
		if(response == "1") {
			writeEntry();
		}
		else if(response == "2") {
			readEntry();
		}
		// Redirect here if the user enters invalid input
		else {
			// Do nothing
		}
	}
	while(response != "3");
	system("cls");
	return 0;
}