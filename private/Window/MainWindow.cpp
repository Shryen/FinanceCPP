#include "Window/MainWindow.h"
#include "View/Sidebar.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QStackedWidget>
#include "View/Login/Login.h"
#include "View/ChartView/ChartView.h"

MainWindow::MainWindow(QString Title, int w, int h, QWidget* parent) : Title(Title), width(w), height(h), QWidget(parent)
{
	resize(QSize{ width, height });
	setWindowTitle(Title);
    this->setStyleSheet("background-color: #ccc");
	
	// First widget
	SidebarWidget = new Sidebar();
	SidebarWidget->setFixedWidth(250);

	MainContentStack = new QStackedWidget();
	MainContentStack->setStyleSheet("background-color: #eee;"); // Just to see it

	loginView = new LoginView();
	chartView = new ChartView();

	MainContentStack->addWidget(loginView);
	MainContentStack->addWidget(chartView);

	// then layout
	QHBoxLayout* MainLayout = new QHBoxLayout(this);
	MainLayout->addWidget(SidebarWidget);
	MainLayout->addWidget(MainContentStack);
}
