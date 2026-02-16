#include "Presenter/MainPresenter.h"
#include "Window/MainWindow.h"
#include "View/Sidebar.h"
#include "View/Login/Login.h"
#include "View/ChartView/ChartView.h"
#include "Entry/EntryManager.h"
#include "Currency/CurrencyManager.h"
#include <QStackedWidget>
#include <iostream>


MainPresenter::MainPresenter(MainWindow* MainWindow, EntryManager* EntryManager, CurrencyManager* CurrencyManager, QObject* parent) : QObject(parent), mainWindow(MainWindow), currencyManager(CurrencyManager), entryManager(EntryManager)
{
	LoginView* loginView = mainWindow->GetLoginView();
	connect(loginView, &LoginView::LoginButtonClicked, this, &MainPresenter::HandleLogin);
	Sidebar* sideBar = mainWindow->GetSidebar();
	sideBar->SetWithdrawalAmount(currencyManager->GetWithdrawnAmount(entryManager->GetEntries()).ToString());
	sideBar->SetDepositAmount(currencyManager->GetPayedInAmount(entryManager->GetEntries()).ToString());
	sideBar->SetTotalAmount(currencyManager->Summarize(entryManager->GetEntries()).ToString());
}

void MainPresenter::HandleLogin(const QString& CurrentUser)
{
	this->CurrentUser = CurrentUser;

    Sidebar* sideBar = mainWindow->GetSidebar();
    sideBar->SetCurrentUser(CurrentUser);
	QStackedWidget* contentStack = mainWindow->GetContentStack();
	contentStack->setCurrentWidget(mainWindow->GetChartView());
	RefreshChart();
}

void MainPresenter::RefreshChart()
{
	const std::vector<Entry>& stdEntries = entryManager->GetEntries();

	QVector<Entry> qEntries(stdEntries.begin(), stdEntries.end());
	mainWindow->GetChartView()->UpdateChartData(qEntries);
}


