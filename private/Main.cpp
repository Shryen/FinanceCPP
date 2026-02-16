#include <QApplication>
#include "Window/MainWindow.h"
#include "Presenter/MainPresenter.h"
#include "Entry/EntryManager.h"
#include "Currency/CurrencyManager.h";
#include "FileController.h"

int main(int argc, char* argv[]) {
	QApplication App(argc, argv);
	MainWindow Window{"Finances", 1200, 800};
	FileController fileController{ "vault.data" };
	CurrencyManager currencyManager{};
	EntryManager Vault{ &fileController };
	MainPresenter Presenter{ &Window, &Vault, &currencyManager};
	Window.show();

	return App.exec();


	// The code below is the console version, Gonna implement GUI from now on
	/*

	char response;
	if (Filecontroller.IsFileEmpty()) {
		std::cout << "Would you like to create a new transaction ? (y / n)\n";
		int Tries = 0;
		
		response = Vault.ReadOption(Vault.GetValidYesNo());

		if (response == 'y' || response == 'Y')
			Vault.WriteNewEntryToFile();
		else if (response == 'n' || response == 'N')
			exit(0);
	}

	// Hovering over the function will show their description (case of visual studio)
	Vault.PrintMenu();

	while (true) {
		std::cout << "> ";
		std::cin >> response;
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
			Vault.DeleteChoice();
			break;
		case '5':
			exit(0);
			break;
		case '6':
			Vault.PrintSummary();
			break;
		case '7':
			Vault.PrintMenu();
			break;
		default:
			std::cout << "Invalid option. Please try again.\n";
			Vault.PrintMenu();
			break;
		}
	}
	*/
}