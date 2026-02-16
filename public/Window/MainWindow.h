#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>

class Sidebar;
class QStackedWidget;
class LoginView;
class ChartView;

enum class ViewPage {
	ViewLogin,
	ViewEntries,
};

class MainWindow : public QWidget {
	Q_OBJECT  // Required for signals/slots

public:
	MainWindow( QString Title, int w, int h, QWidget * parent = nullptr );

	Sidebar* GetSidebar() const { return SidebarWidget; }
	QStackedWidget* GetContentStack() const { return MainContentStack; }
	LoginView* GetLoginView() const { return loginView; }
	//QHBoxLayout* GetMainLayout() const { return MainLayout; }
	ChartView* GetChartView() const { return chartView; }

	//void SetSideBarWidget(Sidebar* Sidebar);

private:
	// Base Widgets
	Sidebar* SidebarWidget;
	QStackedWidget* MainContentStack;
	QString Title;
	int width;
	int height;

	// Views
	LoginView* loginView;
	ChartView* chartView;
};

#endif