#include "View/Sidebar.h"

class MainWindow;
class LoginView;
class EntryManager;
class CurrencyManager;

class MainPresenter : public QObject {
    Q_OBJECT

public:
	MainPresenter(MainWindow* MainWindow, EntryManager* EntryManager, CurrencyManager* CurrencyManager, QObject* parent = nullptr);
private slots:
    void OnAddEntryButtonClicked(const QString& Amount);
private:
    MainWindow* mainWindow;

    CurrencyManager* currencyManager;
    EntryManager* entryManager;

    QString CurrentUser;

    void RefreshChart();
	void HandleLogin(const QString& CurrentUser);
    void HandleAddEntry();
};