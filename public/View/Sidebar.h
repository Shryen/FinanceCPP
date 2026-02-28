#ifndef SIDERBAR_H
#define SIDERBAR_H

#include <QWidget>
#include <QObject>
class MenuLabel;
class QLabel;
class MenuButton;
class QVBoxLayout;

class Sidebar : public QWidget {
	Q_OBJECT

public:
	Sidebar(QWidget* parent = nullptr);
	void SetCurrentUser(const QString& CurrentUser);
	void SetWithdrawalAmount(const QString& Amount);
	void SetDepositAmount(const QString& Amount);
	void SetTotalAmount(const QString& Amount);

	void ShowSidebarContent();
private:
	// Labels
	QLabel* TitleLabel;
	MenuLabel* CurrentUserLabel;
	MenuLabel* WithdrawalCurrencyLabel;
	MenuLabel* DepositCurrencyLabel;
	MenuLabel* TotalCurrencyLabel;

	// Buttons
	//MenuButton* ViewEntriesButton;
	MenuButton* AddEntryButton;
	MenuButton* EditEntryButton;
	MenuButton* DeleteEntryButton;

	QVBoxLayout* SideLayout;

	void SetupButtons();
	void SetupLabels();

	// Labels
	void SetupTitleLabel();
	void AddWidgetsToLayout();
	void SetupCurrentUserLabel();
	void SetupCurrencyLabels();

signals:
	void AddEntryClicked();

public slots:
	void OnAddEntryButtonClicked() { emit AddEntryClicked(); }
	void OnLoginButtonClicked(QString CurrentUser) { SetCurrentUser(CurrentUser); }
};

#endif