// Journal program 
// Created by Nishir Shelat

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <iomanip>
#include <sstream>

using namespace std;

// Prints the main menu
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

// Return true if the given title already exists or is invalid
bool checkTitle(string inputTitle) {
	// Check if the title is valid
	if(inputTitle.length() == 0 || inputTitle.length() > 40) {
		cout << endl << "Error: either that title already exists or it is invalid" << endl;
		return true;
	}
	// Open an input stream for the journal file
	ifstream journal;
	journal.open("journal.txt");
	// Scan through the file and return true if the title is found
	string currentTitle;
	int len = inputTitle.length();
	while(getline(journal,currentTitle)) {
		if(currentTitle.substr(0,len) == inputTitle) {
			cout << endl << "Error: either that title already exists or it is invalid" << endl << endl;
			// Close the stream
			journal.close();
			return true;
		}
	}
	// Close the stream
	journal.close();
	return false;
}

// Searches through the lexicon file for a word and returns true if it exists
bool wordCheck(string word) {
	// Open a stream
	fstream lexicon;
	lexicon.open("lexicon.txt");
	string temp;
	while(getline(lexicon,temp)) {
		if(temp == word) {
			lexicon.close();
			return true;
		}
	}
	lexicon.close();
	return false;
}

// Checks if a given word is in the English language
string spellCheck(string word) {
	cin.ignore();
	// Check if length is 1
	if(word.length() < 2) {
		return word;
	}
	// Check for a lowercase, English character in the beginning
	if(!(word[0] >= 97 && word[0] <= 122)) {
		return word;
	}
	if(word[word.length() - 1] == '.' || word[word.length() - 1] == ',' || word[word.length() - 1] == '?' || word[word.length() - 1] == '!') {
		word = word.substr(0,word.length() - 1);
	}
	if(wordCheck(word)) {
		return word;
	}
	cout << "The following word is spelled wrong: " << word << endl;
	return word;
}

// Write a new entry to the journal file
void writeEntry() {
	// Create a stream for the journal file
	ofstream journal;
	journal.open("journal.txt", ios::app);
	// Prompt the user for a title
	string title;
	system("cls");
	// Check if the title is valid or already exists
	do {
		cout << "Please enter title for your new entry (max 40 characters): ";
		cin.clear();
		getline(cin,title);
	}
	while(checkTitle(title));
	// Create the new entry in the file
	journal << title;
	journal << " -entryStart ";
	// Prompt the user to enter their entry
	string entry;
	system("cls");
	cout << title << endl << endl;
	cout << "Please type in your entry. When you are done, type \"EXIT\" to quit." << endl << endl;
	while(cin >> entry) {
		if(entry == "EXIT") {
			break;
		}
		journal << entry << " ";
	}
	journal << "-entryEnd" << endl;
	// Close the stream
	journal.close();
}

// Print all the existing titles
void printTitles() {
	// Create a stream for the file
	fstream journal;
	journal.open("journal.txt");
	// Display a full list of titles for the user
	system("cls");
	cout << "Here is a list of all the current entries:" << endl << endl;
	string title;
	while(journal >> title) {
		if(title != "-entryStart") {
			cout << title << " ";
		}
		else {
			cout << endl;
			while(journal >> title) {
				if(title == "-entryEnd") {
					break;
				}
			}
		}
	}
	cout << endl;
	journal.close();
}

// Prints an entry with the given title and returns false if the entry doesn't exist
bool printEntry(string title) {
	// Create a stream
	fstream journal;
	journal.open("journal.txt");
	// Find the entry the user wants
	int len = title.length();
	string content;
	while(getline(journal,content)) {
		if(content.substr(0,len) == title) {
			cout << endl;
			cout << content.substr(len + 13, content.length() - 10 - (len + 13)) << endl << endl;
			system("pause");
			return true;
		}
	}
	return false;
	// Close the stream
	journal.close();
}

// Read an entry from the journal file
void readEntry() {
	printTitles();
	// Ask the user to enter the title they want to see
	cout << "Please enter the title of the entry you wish to read: ";
	string title;
	getline(cin,title);
	// Print the entry or an error message
	if(!printEntry(title)) {
		cout << "Sorry, that title doesn't match any entry." << endl << endl;
		system("pause");
	}
}

int main() {
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
	return 0;
}