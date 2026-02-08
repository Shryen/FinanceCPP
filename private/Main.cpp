#include "Entry/EntryManager.h"
#include "Currency/CurrencyManager.h"
#include "FileController.h"
#include <QApplication>
#include <QWidget>
#include <QHBoxLayout>
#include <QPushButton>
#include <QStackedWidget>
#include <QLabel>
#include <QLineEdit>
#include <QString>

int main(int argc, char* argv[]) {
	QApplication App(argc, argv);
	CurrencyManager CurrencyMgr;
	FileController Filecontroller{ "vault.data" };
	EntryManager Vault{ &Filecontroller, &CurrencyMgr };

	QWidget Window;
	int WindowWidth = 400;
	int WindowHeight = 400;
	Window.resize(QSize{ WindowWidth,WindowHeight });
	Window.setWindowTitle(QApplication::translate("finances", "Finances"));

	QVBoxLayout* Layout = new QVBoxLayout(&Window);

	QLabel* NameLabel = new QLabel{ "Enter your name: ", &Window };
	Layout->addWidget(NameLabel);

	QLineEdit* NameInputBox = new QLineEdit{};
	QPushButton* SaveNameButton = new QPushButton{ "Save" };

	Layout->addWidget(NameInputBox);
	Layout->addWidget(SaveNameButton);

	QString SavedName;
	QObject::connect(SaveNameButton, &QPushButton::clicked, [&]() {
		SavedName = NameInputBox->text();
		NameLabel->setText("Saved name: " + SavedName);
		NameInputBox->clear();
	});

	Window.show();


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
	return App.exec();
}