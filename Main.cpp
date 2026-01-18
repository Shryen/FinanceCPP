#include "EntryManager.h"

int main() {

	EntryManager Vault{ "vault.data" };
	char response;
	if (Vault.ReadEntriesFromFile().empty()) {
		cout << "Would you like to create a new transaction ? (y / n)\n";
		cin >> response;
		if(response == 'y' || response == 'Y')
			Vault.WriteNewEntryToFile();
		else if(response == 'n' || response == 'N')
			exit(1);
	}
	cout << "What would you like to do?\n";
	cout << "[0] List transactions\n";
	cout << "[1] Add new transaction\n";
	cout << "[2] Exit application\n";
	cout << "> ";
	cin >> response;
	cout << '\n';
	switch (response) {
	case '0':
		Vault.PrintEntries();
		break;
	case '1':
		Vault.WriteNewEntryToFile();
		break;
	case '2':
		exit(1);
	}
	cout << '\n';
	system("pause");
	return 0;
}