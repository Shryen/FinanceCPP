#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include "Entry/EntryManager.h"
#include "Currency/CurrencyManager.h"
#include "FileController.h"

class MainWindow : public QWidget {
	//Q_OBJECT  // Required for signals/slots

public:
	MainWindow( QString Title, int w, int h, QWidget * parent = nullptr );

private:
	void SetupUI();
	void SetupConnections();
	
	QString Title{ "Finances" };
	int width{ 400 };
	int height{ 800 };

	FileController* Filecontroller{ nullptr };
	CurrencyManager* CurrencyMgr{ nullptr };
	EntryManager* Vault{ nullptr };

	QVBoxLayout* VLayout;
	QHBoxLayout* HLayout;
	QLabel* NameLabel;
	QLineEdit* NameInput;
	QPushButton* NameSaveButton;
	QWidget* SideBar;
};

#endif