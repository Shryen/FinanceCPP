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
    this->setStyleSheet("background-color: #F0EFF4");
	
	// First widget
	SidebarWidget = new Sidebar();
	SidebarWidget->setMinimumWidth(250);

	MainContentStack = new QStackedWidget();

	loginView = new LoginView();
	chartView = new ChartView();

	MainContentStack->addWidget(loginView);
	MainContentStack->addWidget(chartView);

	// then layout
	QHBoxLayout* MainLayout = new QHBoxLayout(this);
	MainLayout->setContentsMargins(0, 0, 0, 0);
	MainLayout->addWidget(SidebarWidget);
	MainLayout->addWidget(MainContentStack);
}
