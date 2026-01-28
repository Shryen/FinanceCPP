#include "EntryManager.h"
#include "CurrencyManager.h"


EntryManager::EntryManager(const string& FilePath, CurrencyManager* CurrencyMgr)
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

	Currency = CurrencyMgr;
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
	int id{ 1 };
	double EuroAmount{ 0 };
	string Person{ "" };
	type TransactionType{};
	int Tries = 0;

	PrintEntries();

	cout << '\n';

	do {
		if (Tries > 0)
			cout << "Amount has to be a number and greater than zero.\n\n";

		cout << "Enter amount: ";
		cin >> EuroAmount;
		if (cin.fail()) {
			cin.clear();     
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard input
			EuroAmount = -1;
		}
		Tries++;
	} while (!IsValidAmount(to_string(EuroAmount)));

	cout << '\n';
	cout << "Enter your name.\n";
	cout << "> ";
	cin >> Person;

	cout << "\nYou put money or take out?\n";
	cout << "[1] Put in\n";
	cout << "[2] Take out\n";
	char Response;

	vector<char> ValidOptions = { '1', '2' };
	Response = ReadOption(ValidOptions);

	switch (Response) {
	case '1':
		TransactionType = type::payin;
		break;
	case '2':
		TransactionType = type::withdraw;
		break;
	}

	if (!Entries.empty())
		id = Entries.back().id + 1;

	int CentAmount = Currency->ConvertToCents(EuroAmount);

	Entry NewEntry;
	NewEntry.id = id;
	NewEntry.amount = CentAmount;
	NewEntry.Person = Person;
	NewEntry.TypeOfEntry = TransactionType;
	NewEntry.OldValue = 0;

	Entries.push_back(NewEntry);
	PrintEntriesToFile();
	cout << "\nNew list: \n";
	PrintEntries();
	cout << "\n";
}

void EntryManager::PrintEntries()
{
	if (Entries.size() == 0) cout << "No records found yet, create new one!\n";
	else {
		cout << '\n';
		cout << "ID\t| Date\t\t| Amount\t| Person\t| Type\n";
		cout << string(65, '-') << '\n';
		for (int i = 0; i < Entries.size(); ++i) {
			double EuroAmount = Currency->ConvertToEuros(Entries[i].amount);
			double OldEuroAmount = Currency->ConvertToEuros(Entries[i].OldValue);
			if (Entries[i].OldValue == 0)
				cout << "[" << Entries[i].id << "]\t| "
				<< Entries[i].DateofRecord << "\t| "
				<< "€" << EuroAmount << "\t\t| "
				<< Entries[i].Person << "\t\t| "
				<< TypeToString(Entries[i].TypeOfEntry) << '\n';
			else
				cout << "[" << Entries[i].id << "]\t| "
				<< Entries[i].DateofRecord << "\t| "
				<< "€" << EuroAmount << "\t\t| "
				<< Entries[i].Person << "\t\t| "
				<< TypeToString(Entries[i].TypeOfEntry) << "\t | "
				<< "[Edited from €" << OldEuroAmount << "]" << '\n';
		}
		cout << '\n';
	}
}

void EntryManager::PrintEntry(int index)
{
	cout << '\n';
	cout << "ID\t| Date\t\t| Amount\t| Person\t| Type\n";
	cout << string(65, '-') << '\n';
	for(int i=0; i<Entries.size(); ++i){
		double EuroAmount = Currency->ConvertToEuros(Entries[i].amount);
		double OldEuroAmount = Currency->ConvertToEuros(Entries[i].OldValue);
		if (Entries[i].id == index && Entries[i].OldValue != 0)
			cout << "[" << Entries[i].id << "]\t| "
			<< Entries[i].DateofRecord << "\t| "
			<< "€" << EuroAmount << "\t\t| "
			<< Entries[i].Person << "\t\t| "
			<< TypeToString(Entries[i].TypeOfEntry) << '\n';
		else if(Entries[i].id == index)
			cout << "[" << Entries[i].id << "] "
			<< Entries[i].DateofRecord << " | "
			<< "€" << EuroAmount << " | "
			<< Entries[i].Person << " | "
			<< TypeToString(Entries[i].TypeOfEntry) << " | "
			<< "[Edited from €" << OldEuroAmount << "]" << '\n';
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
	cout << "Enter the ID of the entry you want to edit.\n";
	int Response;
	int Tries{ 0 };

	do {
		if (Tries > 0)
			cout << "Invalid ID. Try another one!\n";

		cout << "> ";
		cin >> Response;

		Tries++;
	} while (Response < 0 || Response >= Entries.size());

	int index = Response;
	cout << "\nSelected: ";
	PrintEntry(index);

	cout << "\nAre you sure you want to edit this entry? (y / n)\n";
	char CharResponse;
	CharResponse = ReadOption(ValidYesNo);
	if (CharResponse == 'y' || CharResponse == 'Y') {
		cout << "\nWhich field do you want to edit?\n";
		cout << "[1] Amount\n";
		cout << "[2] Person\n";
		vector<char> ValidChars = { '1','2' };

		CharResponse = ReadOption(ValidChars);

		switch (CharResponse) {
		case '1':
			cout << "Enter new amount: ";
			Entries[index].OldValue = Entries[index].amount;
			double EuroAmount;
			cin >> EuroAmount;
			Entries[index].amount = Currency->ConvertToCents(EuroAmount);
			cout << "Amount changed: \n";
			PrintEntry(index);
			break;
		case '2':
			cout << "Enter new person: ";
			cin >> Entries[index].Person;
			cout << "Person changed: \n";
			PrintEntry(index);
			break;
		default:
			cout << "Invalid option!\n";
		}

		PrintEntriesToFile();
	}
	else {
		PrintMenu();
	}
}

void EntryManager::PrintMenu()
{
	cout << "\tMenu \n";
	cout << "[1] List transactions" << endl;
	cout << "[2] Write new entry" << endl;
	cout << "[3] Edit an entry" << endl;
	cout << "[4] Delete an entry" << endl;
	cout << "[5] Exit the program" << endl;
	cout << "[6] Summary" << endl;
	cout << "[7] Help" << endl;
}

void EntryManager::PrintSummary()
{
	cout << "\nSummary of all transactions: \n";
	cout << "Withdrawals:\t " << Currency->GetWithdrawnAmount(Entries) << endl;
	cout << "Pay-ins:\t " << Currency->GetPayedInAmount(Entries) << endl;
	cout << "Total balance:\t " << Currency->Summarize(Entries) << endl << endl;
}

bool EntryManager::CheckInput(char Response, vector<char> Characters)
{
	for (int i = 0; i<Characters.size(); ++i)
		if (Response == Characters[i])
			return true;

	return false;
}

char EntryManager::ReadOption(vector<char> ValidChars)
{
	int Tries = 0;
	char Response{};
	do {
		if (Tries > 0)
			cout << "Invalid response. Try again.\n";
		cout << "> ";
		cin >> Response;
		Tries++;
	} while (!CheckInput(Response, ValidChars));

	return Response;
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

bool EntryManager::IsValidAmount(const string& input)
{
	if (input.empty()) return false;

	if (input.size() == 1 && input[0] == '0') return false;

	string newInput = input;

	for (int i = 0; i < newInput.length(); ++i){
		if(newInput[i] == ',' || newInput[i] == '.')
			newInput.erase(i, 1);
		if (!isdigit(newInput[i]))
			return false;
	}
	return true;
}

void EntryManager::DeleteChoice()
{
	int Index{};
	//	- Write options
	PrintEntries();
	//	- Prompt user to choose line to delete
	cout << "Enter the ID of the line you want to delete.\n";
	cout << "> ";
	cin >> Index;
	cout << '\n';
	cout << "User choice: " << Index;
	char Response;
	PrintEntry(Index);
	cout << "\nAre you sure you want to delete this line? (y/n)\n";

	Response = ReadOption(GetValidYesNo());
	if (Response == 'y' || Response == 'Y') {
		DeleteEntry(Index);
	}
	else {
		PrintMenu();
	}
}

void EntryManager::DeleteEntry(int index)
{
	//	- Get the whole vector rewrite ID's so there's no holes
	int StartingIndex = Entries[0].id;
	for (int i = 0; i < Entries.size(); ++i) {
		if (Entries[i].id == index) {
			Entries.erase(Entries.begin()+i);
			break;
		}
	}

	for (int i = 0; i < Entries.size(); ++i) 
		Entries[i].id = i;
	
	PrintEntriesToFile();
}
