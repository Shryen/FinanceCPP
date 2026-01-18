#include "EntryManager.h"

EntryManager::EntryManager(const string& FilePath)
{
	if (FilePath.empty())
		throw::runtime_error("Invalid FilePath");

	FileName = FilePath;
	ifstream Readfile{ FileName };
	if (!Readfile) {
		ofstream OutFile(FileName);
		OutFile.open(FileName);
		OutFile.close();
	}
}

vector<Entry>& EntryManager::ReadEntriesFromFile()
{
	Entries.clear();
	ifstream InputFile(FileName);
	if (!InputFile)
		throw::runtime_error("Couldn't open file: " + FileName);

	Entry ReadEntry;
	string TypeString;
	while (InputFile >> ReadEntry.id
		>> ReadEntry.DateofRecord
		>> ReadEntry.amount
		>> ReadEntry.Person
		>> TypeString
		>> ReadEntry.OldValue)
	{
		ReadEntry.TypeOfEntry = StringToType(TypeString);
		Entries.push_back(ReadEntry);
	}

	if (Entries.empty())
		cout << "File is empty.\n";

	return Entries;
}

void EntryManager::WriteNewEntryToFile()
{
	int id{ 0 };
	double Amount{ 0.0 };
	string Person{ "" };
	type TransactionType{};

	PrintEntries();

	cout << '\n';
	cout << "Enter data with space between them. \n";
	cout << "Example: [Amount] [Person]\n";
	cout << "> ";
	cin >> Amount >> Person;
	cout << "\nYou put money or take out?\n";
	cout << "[0] Put in\n";
	cout << "[1] Take out\n";
	cout << "> ";
	char Response;
	cin >> Response;
	switch (Response) {
	case '0':
		TransactionType = type::payin;
		break;
	case '1':
		TransactionType = type::withdraw;
		break;
	}

	if (!Entries.empty())
		id = Entries.back().id + 1;

	Entry NewEntry;
	NewEntry.id = id;
	NewEntry.amount = Amount;
	NewEntry.Person = Person;
	NewEntry.TypeOfEntry = TransactionType;
	NewEntry.OldValue = 0;

	Entries.push_back(NewEntry);
	PrintEntriesToFile();
	cout << "\nNew list: \n";
	PrintEntries();
}

void EntryManager::PrintEntries()
{
	for (int i = 0; i < Entries.size(); ++i) {
		if (Entries[i].OldValue == 0)
			cout << "[" << Entries[i].id << "] "
			<< Entries[i].DateofRecord << " | "
			<< "€" << Entries[i].amount << " | "
			<< Entries[i].Person << " | "
			<< TypeToString(Entries[i].TypeOfEntry) << '\n';
		else
			cout << "[" << Entries[i].id << "] "
			<< Entries[i].DateofRecord << " | "
			<< "€" << Entries[i].amount << " | "
			<< Entries[i].Person << " | "
			<< TypeToString(Entries[i].TypeOfEntry) << " | "
			<< "[Edited from €" << Entries[i].OldValue << "]" << '\n';
	}
}

void EntryManager::PrintEntry(int index)
{
	if (Entries[index].OldValue == 0)
		cout << "[" << Entries[index].id << "] "
		<< Entries[index].DateofRecord << " | "
		<< Entries[index].amount << "€ | "
		<< Entries[index].Person << " | "
		<< TypeToString(Entries[index].TypeOfEntry) << '\n';
	else
		cout << "[" << Entries[index].id << "] "
		<< Entries[index].DateofRecord << " | "
		<< Entries[index].amount << "€ | "
		<< Entries[index].Person << " | "
		<< TypeToString(Entries[index].TypeOfEntry) << " | "
		<< Entries[index].OldValue << '\n';
}

void EntryManager::PrintEntriesToFile()
{
	ofstream FileOutput(FileName);
	for (int i = 0; i < Entries.size(); ++i) {
		if (Entries[i].OldValue == 0) 
			FileOutput << Entries[i].id << " "
				<< Entries[i].DateofRecord << " "
				<< Entries[i].amount << " "
				<< Entries[i].Person << " "
				<< TypeToString(Entries[i].TypeOfEntry) << " "
				<< Entries[i].OldValue << '\n';
		else
			FileOutput << Entries[i].id << " "
			<< Entries[i].DateofRecord << " "
			<< Entries[i].amount << " "
			<< Entries[i].Person << " "
			<< TypeToString(Entries[i].TypeOfEntry) << " "
			<< Entries[i].OldValue << '\n';
	}
}

void EntryManager::EditEntry()
{
	PrintEntries();
	cout << "Enter the ID of the entry you want to edit: ";
	int Response;
	cin >> Response;
	if (Response < 0 || Response >= Entries.size()) {
		throw::runtime_error("Invalid ID");
	}
	int index = Response;
	cout << "\nSelected : \n";
	PrintEntry(Response);

	cout << "Are you sure you want to edit this entry? (y / n)\n";
	char CharResponse;
	cin >> CharResponse;
	if (CharResponse == 'y' || CharResponse == 'Y') {
		cout << "\nWhich field do you want to edit?\n";
		cout << "[0] Amount\n";
		cout << "[1] Person\n";
		cout << "> ";
		cin >> Response;
		switch (Response) {
		case 0:
			cout << "Enter new amount: ";
			Entries[index].OldValue = Entries[index].amount;
			cin >> Entries[index].amount;
			cout << "Amount changed: \n";
			PrintEntry(index);
			break;
		case 1:
			cout << "Enter new person: ";
			cin >> Entries[index].Person;
			cout << "Person changed: \n";
			PrintEntry(index);
			break;
		default:
			throw::runtime_error("Invalid option");
		}

		PrintEntriesToFile();
	}
	else {
		PrintOptions();
	}
}

void EntryManager::PrintOptions()
{
	cout << "[1] List transactions" << endl;
	cout << "[2] Write new entry" << endl;
	cout << "[3] Edit an entry" << endl;
	cout << "[4] Delete an entry" << endl;
	cout << "[5] Exit the program" << endl;
	cout << "[6] Help" << endl;
	cout << "> ";
}


string EntryManager::TypeToString(type t)
{
	switch (t) {
	case type::payin: return "payin";
	case type::withdraw: return "withdraw";
	}
	throw logic_error("Invalid type");
}

type EntryManager::StringToType(const string& s)
{
	if (s == "payin") return type::payin;
	if (s == "withdraw") return type::withdraw;
	throw std::runtime_error("Invalid Type string: " + s);
}
