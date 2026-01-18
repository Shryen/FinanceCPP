#include "EntryManager.h"

int main() {

	EntryManager Vault{ "vault.data" };
	char response;
	if (Vault.ReadEntriesFromFile().empty()) {
		cout << "Would you like to create a new transaction ? (y / n)\n";
		cin >> response;
		if (response == 'y' || response == 'Y')
			Vault.WriteNewEntryToFile();
		else if (response == 'n' || response == 'N')
			exit(0);
		else {
			cout << "Invalid response. Try again.\n";
			cin.putback(response);
		}
	}
	Vault.PrintOptions();
	while (true) {
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
			exit(0);
		case '3':
			Vault.PrintOptions();
			break;
		default:
			cout << "Invalid option. Please try again.\n";
			Vault.PrintOptions(); 
			break;
		}
		
		cout << "> ";
	}
	
	return 0;
}