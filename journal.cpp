// Journal program

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <iomanip>
#include <sstream>

using namespace std;

int main()
{
	// Main menu
	bool quit = true;
	while (quit)
	{
	cout << endl << "Welcome to the C++ Journal!" << endl << "Please select an option:" << endl << "1. Read a past entry" << endl << "2. Write a new entry" << endl << "3. Quit the program" << endl  << endl << ">> ";
	int choice;
	cin >> choice;
	while(choice != 1 && choice != 2 && choice != 3)
	{
		cout << endl << "Please select a valid option." << endl << ">> ";
	}
	system("cls");
	if (choice == 1)
	{
		// Read a past entry
		// Open the text file
		fstream journal;
		journal.open("journal.txt");
		// Identify the date
		cout << endl << "Please enter the year of the entry you wish to find (yyyy)." << endl << "YEAR: ";
		string entry_year;
		cin >> entry_year;
		string line;
		bool check_year = true;
		string valid_dates[30];
		int entry_counter = 0;
		string entry_date;
		cout << endl;
		while (getline(journal, line))
		{
			if (line.substr(12, 4) == entry_year)
			{
				system("cls");
				check_year = false;
				cout << endl << "Please enter the month of the entry you wish to find (mm)." << endl << "MONTH: ";
				
			}
		}
		if (check_year)
		{
			cout << "Sorry, there is no entry listed under that year." << endl;
			cout << endl << "Enter any value to return to the main menu." << endl;
		string exit;
		if (cin >> exit)
		{
			system("cls");
			continue;
		}
		}
		bool check_month = true;
		string entry_month;
		cin >> entry_month;
		journal.close();
		journal.open("journal.txt");
		cout << endl;
		while(getline(journal, line))
		{
			if(line.substr(0, 8) == "DATE: " + entry_month && line.substr(12, 4) == entry_year)
			{
				check_month = false;
				cout << line.substr(0, 16) << endl;
			}
		}
		if (check_month)
		{
			cout << "Sorry, there is no entry listed under that month." << endl;
			cout << endl << "Enter any value to return to the main menu." << endl;
		string exit;
		if (cin >> exit)
		{
			system("cls");
			continue;
		}
		}
		string final_entry_date;
		if(!check_month)
		{
			cout << endl << "Please type in one of the dates above, exactly as you see it." << endl << endl << ">> ";
			cin >> final_entry_date;
		}
		journal.close();
		journal.open("journal.txt");
		while(getline(journal, line))
		{
			if(line.substr(0,16) == "DATE: " + final_entry_date)
			{
				cout << endl << line.substr(17) << endl;
			}
		}
		cout << endl << "Enter any value to return to the main menu." << endl;
		string exit;
		if (cin >> exit)
		{
			system("cls");
			continue;
		}
	}
	else if (choice == 2)
	{
		// Write a new entry
		// Open the text file
		fstream journal;
		journal.open("journal.txt", ios::in | ios::out | ios::ate);
	
		// Insert the date
		cout << endl << "Please enter the date of your new entry (mm-dd-yyyy)." << endl << "DATE: ";
		string entry_date;
		cin >> entry_date;
		entry_date = "DATE: " + entry_date + " ";
		journal << entry_date;
	
		// Insert the new entry
		cout << endl << "Enter your new journal entry below." << endl << "Type \"EXIT\" to quit." << endl << endl;
		string entry;
		while (entry != "EXIT")
		{
			cin >> entry;
			if (entry == "EXIT")
			{
				break;
			}
			journal << entry << " ";
		}
		journal << endl;
	}
	else if (choice == 3)
	{
		quit = false;
		break;
	}
	}
	return 0;
}