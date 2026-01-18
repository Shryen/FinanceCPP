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
	ifstream InputFile(FileName);
	if (!InputFile)
		throw::runtime_error("Couldn't open file: " + FileName);

	Entry ReadEntry;
	string TypeString;
	while (InputFile >> ReadEntry.id
		>> ReadEntry.DateofRecord
		>> ReadEntry.amount
		>> ReadEntry.Person
		>> TypeString)
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
	cout << "You put money or take out?\n";
	cout << "[0] Put in\n";
	cout << "[1] Take out\n";
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

	Entries.push_back(NewEntry);
	PrintEntriesToFile();
	cout << "New list: \n";
	PrintEntries();
}

void EntryManager::PrintEntries()
{
	for (int i = 0; i < Entries.size(); ++i) {
		if (Entries[i].OldValue == 0)
			cout << "[" << Entries[i].id << "] "
			<< Entries[i].DateofRecord << " | "
			<< Entries[i].amount << "€ | "
			<< Entries[i].Person << " | "
			<< TypeToString(Entries[i].TypeOfEntry) << '\n';
		else
			cout << "[" << Entries[i].id << "] "
			<< Entries[i].DateofRecord << " | "
			<< Entries[i].amount << "€ | "
			<< Entries[i].Person << " | "
			<< TypeToString(Entries[i].TypeOfEntry) << ' | '
			<< Entries[i].OldValue << '\n';
	}
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
				<< TypeToString(Entries[i].TypeOfEntry) << '\n';
		else
			FileOutput << Entries[i].id << " "
			<< Entries[i].DateofRecord << " "
			<< Entries[i].amount << " "
			<< Entries[i].Person << " "
			<< TypeToString(Entries[i].TypeOfEntry) << ' '
			<< Entries[i].OldValue << '\n';
	}
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
