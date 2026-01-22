#pragma once
#include <string>
#include "Date.h"
#include <vector>
#include <fstream>
using namespace std;

enum class type {
	payin,
	withdraw
};

struct Entry {
	int id{0};
	Date DateofRecord = Date();
	int amount{ 0 };
	string Person{ "" };
	type TypeOfEntry{ type::payin };
	double OldValue{ 0.0 };
};

class EntryManager
{
public:
	EntryManager(const string& FilePath);

	/*
	 Reads entries from file and stores them in the Entries vector
	*/
	vector<Entry>& ReadEntriesFromFile();
	string GetFileName() const { return FileName; }

	/*
	 Writes a new entry to the file and updates the vector
	 Input: Amount, Person as string
	 Type choosable between payin and withdraw
	 ID increments automatically
	*/
	void WriteNewEntryToFile();
	void PrintEntries();
	void PrintEntry(int Index);
	void PrintEntriesToFile();
	void EditEntry();

	/* Prints options available to the user.
		1. Print all entries
		2. Write a new entry
		3. Edit an entry
		4. Delete an entry
		5. Exit the program
		6. Print options again
	*/
	void PrintOptions();

	/* 
		Checks if the user put the right input
	*/
	bool CheckInput(char Response, vector<char> Characters);

	/* 
		Checks for input until a valid character is given then returns it
	*/
	char ReadOption(vector<char> ValidChars);

	vector<char> GetValidYesNo() const { return ValidYesNo; }
	bool IsValidAmount(const string& input);

	void DeleteChoice();
	void DeleteEntry(int index);

private:
	vector<Entry> Entries;
	string FileName{ "" };

	// convert type enum to string for representation
	string TypeToString(type t);
	// convert string to type enum from user input
	type StringToType(const string& s);

	vector<char> ValidYesNo{ 'y', 'Y', 'n', 'N' };

};

