#pragma once
#include <string>
#include "Date.h"
#include <vector>
#include <fstream>
#include "Entry.h"

class CurrencyManager;
class FileController;

class EntryManager
{
public:
	EntryManager(FileController* FileController, CurrencyManager* CurrencyMgr);

	/*
	 Writes a new entry to the file and updates the vector
	 Input: Amount, Person as string
	 Type choosable between payin and withdraw
	 ID increments automatically
	*/
	void WriteNewEntryToFile();
	void PrintEntries();
	std::vector<Entry> GetEntries() { return Entries; }
	void PrintEntry(int Index);
	void EditEntry();

	/* Prints options available to the user.
		1. Print all entries
		2. Write a new entry
		3. Edit an entry
		4. Delete an entry
		5. Exit the program
		6. Print Summary
		7. Help (prints this menu again)
	*/
	void PrintMenu();
	void PrintSummary();
	/* 
		Checks if the user put the right input
	*/
	bool CheckInput(char Response, std::vector<char> Characters);

	/* 
		Checks for input until a valid character is given then returns it
	*/
	char ReadOption(std::vector<char> ValidChars);

	std::vector<char> GetValidYesNo() const { return ValidYesNo; }

	void DeleteChoice();
	void DeleteEntry(int index);

	bool IsEmpty() const;

private:
	std::vector<Entry> Entries;

	std::vector<char> ValidYesNo{ 'y', 'Y', 'n', 'N' };

	CurrencyManager* CurrencyMgr{ nullptr };
	FileController* FileControllerPtr{ nullptr };

	type GetTypeFromUser(char Response);
	std::string GetUserName(std::string& Name);

	Currency TryToGetAmount(Currency& Amount, std::string ErrorMessage);
};

