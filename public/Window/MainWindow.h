#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include "View/Entry/AddEntryView.h"

class Sidebar;
class QStackedWidget;
class LoginView;
class ChartView;
class EntryView;

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
	ChartView* GetChartView() const { return chartView; }
	EntryView* GetEntriesView() const { return entryView; }

	AddEntryView* GetEntryView() const { return EntryManagerView; }

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
	AddEntryView* EntryManagerView;
	EntryView* entryView;
};

#endif