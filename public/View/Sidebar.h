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
private:
	QLabel* TitleLabel;
	MenuLabel* CurrentUserLabel;
	MenuLabel* WithdrawalCurrencyLabel;
	MenuLabel* DepositCurrencyLabel;
	MenuLabel* TotalCurrencyLabel;
	MenuButton* ViewEntriesButton;
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
	void ViewEntriesClicked();

public slots:
	void OnViewEntriesClicked() { emit ViewEntriesClicked(); }
	void OnLoginButtonClicked(QString CurrentUser) { SetCurrentUser(CurrentUser); }
};

#endif