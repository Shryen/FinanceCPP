#include "EntryManager.h"

int main() {

	EntryManager Vault{ "vault.data" };
	char response;
	if (Vault.ReadEntriesFromFile().empty()) {
		cout << "Would you like to create a new transaction ? (y / n)\n";
		int Tries = 0;
		
		response = Vault.ReadOption(Vault.GetValidYesNo());

		if (response == 'y' || response == 'Y')
			Vault.WriteNewEntryToFile();
		else if (response == 'n' || response == 'N')
			exit(0);
	}

	// Hovering over the function will show their description (case of visual studio)
	Vault.PrintOptions();

	while (true) {
		cin >> response;
		cout << '\n';
		switch (response) {
		case '1':
			Vault.PrintEntries();
			break;
		case '2':
			Vault.WriteNewEntryToFile();
			break;
		case '3':
			Vault.EditEntry();
			break;
		case '4':
			// DeleteEntry() - implement later
			cout << "DeleteEntry() not implemented yet.\n";
			break;
		case '5':
			exit(0);
			break;
		case '6':
			Vault.PrintOptions();
			break;
		default:
			cout << "Invalid option. Please try again.\n";
			Vault.PrintOptions();
			break;
		}
	}

	return 0;
}