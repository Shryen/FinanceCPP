#include "Entry/EntryManager.h"
#include "Currency/CurrencyManager.h"
#include "FileController.h"


EntryManager::EntryManager(FileController* FileController)
{
	this->FileControllerPtr = FileController;

	FileControllerPtr->ReadEntriesFromFile(Entries);
}

void EntryManager::WriteNewEntryToFile()
{
	int id{ 1 };
	Currency EuroAmount{ "0" };
	std::string Person{ "" };
	type TransactionType{};

	PrintEntries();
	std::cout << '\n';

	//TryToGetAmount(EuroAmount, "Amount has to be a number and greater than zero.");

	char Response{'0'};
	TransactionType = GetTypeFromUser(Response);

	if (!Entries.empty())
		id = Entries.back().id + 1;

	Entry NewEntry;
	NewEntry.id = id;
	NewEntry.amount = EuroAmount;
	NewEntry.Person = Person;
	NewEntry.TypeOfEntry = TransactionType;
	NewEntry.OldValue = 0;

	Entries.push_back(NewEntry);
	FileControllerPtr->WriteEntriesToFile(Entries);
	std::cout << "\nNew list: \n";
	PrintEntries();
	std::cout << "\n";
}

type EntryManager::GetTypeFromUser(char Response) {
	std::cout << "\nYou put money or take out?\n";
	std::cout << "[1] Put in\n";
	std::cout << "[2] Take out\n";
	std::vector<char> ValidOptions = { '1', '2' };
	Response = ReadOption(ValidOptions);
	switch (Response) {
	case'1':
		return type::payin;
	case '2':
		return type::withdraw;
	default:
		std::cout << "Invalid option, defaulting to payin.\n";
		return type::payin;
	}
}

/*
Currency EntryManager::TryToGetAmount(Currency& Amount, std::string ErrorMessage)
{
	int Tries = 0;
	do {
		if (Tries > 0)
			std::cout << ErrorMessage << "\n\n";

		std::cout << "Enter amount: ";
		std::cin >> Amount;
		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard input
			Amount = -1;
		}
		Tries++;
	} while (!CurrencyMgr->IsValidAmount(Amount));

	return Amount;
}
*/


void EntryManager::PrintEntries()
{
	if (Entries.size() == 0) std::cout << "No records found yet, create new one!\n";
	else {
		std::cout << '\n';
		std::cout << "ID\t| Date\t\t| Amount\t| Person\t| Type\n";
		std::cout << std::string(65, '-') << '\n';
		for (int i = 0; i < Entries.size(); ++i) {
			Currency EuroAmount = Entries[i].amount.ToEuros();
			Currency OldEuroAmount = Entries[i].OldValue.ToEuros();
			
			if (Entries[i].OldValue == 0)
				std::cout << "[" << Entries[i].id << "]\t| "
				<< Entries[i].DateofRecord << "\t| "
				<< "€" << EuroAmount << "\t\t| "
				<< Entries[i].Person << "\t\t| "
				<< FileControllerPtr->TypeToString(Entries[i].TypeOfEntry) << '\n';
			else
				std::cout << "[" << Entries[i].id << "]\t| "
				<< Entries[i].DateofRecord << "\t| "
				<< "€" << EuroAmount << "\t\t| "
				<< Entries[i].Person << "\t\t| "
				<< FileControllerPtr->TypeToString(Entries[i].TypeOfEntry) << "\t | "
				<< "[Edited from €" << OldEuroAmount << "]" << '\n';
		}
		std::cout << '\n';
	}
}

void EntryManager::PrintEntry(int index)
{
	std::cout << '\n';
	std::cout << "ID\t| Date\t\t| Amount\t| Person\t| Type\n";
	std::cout << std::string(65, '-') << '\n';
	for(int i=0; i<Entries.size(); ++i){
		Currency EuroAmount = Entries[i].amount.ToEuros();
		Currency OldEuroAmount = Entries[i].OldValue.ToEuros();
		if (Entries[i].id == index && Entries[i].OldValue != 0)
			std::cout << "[" << Entries[i].id << "]\t| "
			<< Entries[i].DateofRecord << "\t| "
			<< "€" << EuroAmount << "\t| "
			<< Entries[i].Person << "\t\t| "
			<< FileControllerPtr->TypeToString(Entries[i].TypeOfEntry) << '\n';
		else if(Entries[i].id == index)
			std::cout << "[" << Entries[i].id << "] "
			<< Entries[i].DateofRecord << " | "
			<< "€" << EuroAmount << " | "
			<< Entries[i].Person << " | "
			<< FileControllerPtr->TypeToString(Entries[i].TypeOfEntry) << " | "
			<< "[Edited from €" << OldEuroAmount << "]" << '\n';
	}
}

void EntryManager::EditEntry()
{
	PrintEntries();
	std::cout << "Enter the ID of the entry you want to edit.\n";
	int Response;
	int Tries{ 0 };

	do {
		if (Tries > 0)
			std::cout << "Invalid ID. Try another one!\n";

		std::cout << "> ";
		std::cin >> Response;

		Tries++;
	} while (Response < 0 || Response >= Entries.size());

	int index = Response;
	std::cout << "\nSelected: ";
	PrintEntry(index);

	std::cout << "\nAre you sure you want to edit this entry? (y / n)\n";
	char CharResponse;
	CharResponse = ReadOption(ValidYesNo);
	if (CharResponse == 'y' || CharResponse == 'Y') {
		std::cout << "\nWhich field do you want to edit?\n";
		std::cout << "[1] Amount\n";
		std::cout << "[2] Person\n";
		std::vector<char> ValidChars = { '1','2' };

		CharResponse = ReadOption(ValidChars);

		switch (CharResponse) {
		case '1':
		{
			std::cout << "Enter new amount: ";
			Entries[index].OldValue = Entries[index].amount;
			Currency EuroAmount{ "0" };
			std::cin >> EuroAmount;
			Entries[index].amount = EuroAmount;
			std::cout << "Amount changed: \n";
			PrintEntry(index);
		}
			break;
		case '2':
		{
			std::cout << "Enter new person: ";
			std::cin >> Entries[index].Person;
			std::cout << "Person changed: \n";
			PrintEntry(index);
		}
			break;
		default:
			std::cout << "Invalid option!\n";
		}

		FileControllerPtr->WriteEntriesToFile(Entries);
	}
	else {
		PrintMenu();
	}
}

void EntryManager::PrintMenu()
{
	std::cout << "\tMenu \n";
	std::cout << "[1] List transactions" << std::endl;
	std::cout << "[2] Write new entry" << std::endl;
	std::cout << "[3] Edit an entry" << std::endl;
	std::cout << "[4] Delete an entry" << std::endl;
	std::cout << "[5] Exit the program" << std::endl;
	std::cout << "[6] Summary" << std::endl;
	std::cout << "[7] Help" << std::endl;
}

/*
void EntryManager::PrintSummary()
{
	std::cout << "\nSummary of all transactions: \n";
	std::cout << "Withdrawals:\t " << CurrencyMgr->GetWithdrawnAmount(Entries) << std::endl;
	std::cout << "Pay-ins:\t " << CurrencyMgr->GetPayedInAmount(Entries) << std::endl;
	std::cout << "Total balance:\t " << CurrencyMgr->Summarize(Entries) << std::endl << std::endl;
}
*/

bool EntryManager::CheckInput(char Response, std::vector<char> Characters)
{
	for (int i = 0; i<Characters.size(); ++i)
		if (Response == Characters[i])
			return true;

	return false;
}

char EntryManager::ReadOption(std::vector<char> ValidChars)
{
	int Tries = 0;
	char Response{};
	do {
		if (Tries > 0)
			std::cout << "Invalid response. Try again.\n";
		std::cout << "> ";
		std::cin >> Response;
		Tries++;
	} while (!CheckInput(Response, ValidChars));

	return Response;
}


void EntryManager::DeleteChoice()
{
	int Index{};
	//	- Write options
	PrintEntries();
	//	- Prompt user to choose line to delete
	std::cout << "Enter the ID of the line you want to delete.\n";
	std::cout << "> ";
	std::cin >> Index;
	std::cout << '\n';
	std::cout << "User choice: " << Index;
	char Response;
	PrintEntry(Index);
	std::cout << "\nAre you sure you want to delete this line? (y/n)\n";

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
	
	FileControllerPtr->WriteEntriesToFile(Entries);
}

bool EntryManager::IsEmpty() const
{
	return Entries.empty();
}

void EntryManager::SetUserName(const QString& Name)
{
	this->Name = Name;
}
