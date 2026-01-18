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
	double amount{ 0.0 };
	string Person{ "" };
	type TypeOfEntry{ type::payin };
	double OldValue{ 0.0 };
};

class EntryManager
{
public:
	EntryManager(const string& FilePath);
	vector<Entry>& ReadEntriesFromFile();
	string GetFileName() const { return FileName; }
	void WriteNewEntryToFile();
	void PrintEntries();
	void PrintEntriesToFile();

private:
	vector<Entry> Entries;
	string FileName{ "" };

	string TypeToString(type t);
	type StringToType(const string& s);
};

