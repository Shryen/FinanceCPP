#include "View/Login/Login.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>

LoginView::LoginView(QWidget* parent) : QWidget(parent)
{
	QVBoxLayout* mainLayout = new QVBoxLayout(this);
	mainLayout->setContentsMargins(0, 0, 0, 0);
	
	LoginWidget = new QWidget();
	LoginWidget->setAttribute(Qt::WA_StyledBackground, true);
	LoginWidget->setStyleSheet(
		"background-color: #FCFCFC;"
		"color: #042A2B;"
		"font-size: 24px;"
	);
	SetupButtons();
	LoginLayout = new QVBoxLayout(LoginWidget);
	LoginLayout->setAlignment(Qt::AlignCenter);
	LoginLayout->addWidget(new QLabel{ "Who are you?" });
	LoginLayout->addWidget(AnaButton);
	LoginLayout->addWidget(KriszButton);
	LoginLayout->setSpacing(20);
	LoginLayout->setContentsMargins(0, 0, 0, 0);
	
	mainLayout->addWidget(LoginWidget);
}

void LoginView::SetupButtons()
{
	AnaButton = new QPushButton("Ana");
	KriszButton = new QPushButton("Krisz");
	
	QString buttonStylesheet =
		"QPushButton {"
		"	background-color: #1D4249;"
		"	color: white;"
		"	border: none;"
		"	border-radius: 8px;"
		"	padding: 12px 30px;"
		"	font-size: 18px;"
		"	font-weight: bold;"
		"}"
		"QPushButton:hover {"
		"	background-color: #075F5F;"
		"}"
		"QPushButton:pressed {"
		"	background-color: #075F5F;"
		"}";
	
	AnaButton->setStyleSheet(buttonStylesheet);
	KriszButton->setStyleSheet(buttonStylesheet);

	connect(AnaButton, &QPushButton::clicked, this, &LoginView::OnAnaButtonClicked);
	connect(KriszButton, &QPushButton::clicked, this, &LoginView::OnKriszButtonClicked);
}
