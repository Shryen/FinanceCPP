#include "View/Sidebar.h"
#include <QLabel>
#include <QVBoxLayout>
#include "View/Components/Menu/MenuButton.h"
#include "View/Components/Menu/MenuLabel.h"

Sidebar::Sidebar(QWidget* parent) : QWidget(parent)
{
	setAttribute(Qt::WA_StyledBackground, true);
	this->setStyleSheet("background-color: #042A2B; color: white; min-width: 250px;");
	SideLayout = new QVBoxLayout(this);
	SetupLabels();
	SetupButtons();
	AddWidgetsToLayout();
	setLayout(SideLayout);
}

void Sidebar::SetCurrentUser(const QString& CurrentUser)
{
	CurrentUserLabel->setText("Hi " + CurrentUser + "!");
}

void Sidebar::SetWithdrawalAmount(const QString& Amount)
{
	WithdrawalCurrencyLabel->setText("Total Withdrawals: €" + Amount);
}

void Sidebar::SetDepositAmount(const QString& Amount)
{
	DepositCurrencyLabel->setText("Total Deposits: €" + Amount);
}

void Sidebar::SetTotalAmount(const QString& Amount)
{
	TotalCurrencyLabel->setText("Net Total: €" + Amount);
}

void Sidebar::ShowSidebarContent()
{
	WithdrawalCurrencyLabel->show();
	DepositCurrencyLabel->show();
	TotalCurrencyLabel->show();
	AddEntryButton->show();
	EditEntryButton->show();
	DeleteEntryButton->show();
}

void Sidebar::SetupButtons()
{
	AddEntryButton = new MenuButton("Add Entry", this);
	EditEntryButton = new MenuButton("Edit Entry", this);
	DeleteEntryButton = new MenuButton("Delete Entry", this);
	AddEntryButton->hide();
	EditEntryButton->hide();
	DeleteEntryButton->hide();

	//connect(ViewEntriesButton, &QPushButton::clicked, this, &Sidebar::OnViewEntriesClicked);
}

void Sidebar::SetupLabels()
{
	SetupTitleLabel();
	SetupCurrentUserLabel();
	SetupCurrencyLabels();
}

void Sidebar::SetupTitleLabel()
{
	TitleLabel = new QLabel("Finances", this);
	TitleLabel->setAlignment(Qt::AlignCenter);
	TitleLabel->setStyleSheet("font-size: 36px; font-weight: bold; margin-bottom: 20px;");
}

void Sidebar::SetupCurrentUserLabel()
{
	CurrentUserLabel = new MenuLabel("Please select your name!");
	CurrentUserLabel->setAlignment(Qt::AlignCenter);
	CurrentUserLabel->setStyleSheet("font-size: 24px; margin-bottom: 20px; font-weight: bold;");
}

void Sidebar::SetupCurrencyLabels()
{
	WithdrawalCurrencyLabel = new MenuLabel("Total Withdrawals: €0.00");
	DepositCurrencyLabel = new MenuLabel("Total Deposits: €0.00");
	TotalCurrencyLabel = new MenuLabel("Net Total: €0.00");
	WithdrawalCurrencyLabel->hide();
	DepositCurrencyLabel->hide();
	TotalCurrencyLabel->hide();
}

void Sidebar::AddWidgetsToLayout()
{
	SideLayout->addWidget(TitleLabel);
	SideLayout->addWidget(CurrentUserLabel);

	// Labels
	SideLayout->addWidget(WithdrawalCurrencyLabel);
	SideLayout->addWidget(DepositCurrencyLabel);
	SideLayout->addWidget(TotalCurrencyLabel);

	// Buttons
	SideLayout->addWidget(AddEntryButton);
	SideLayout->addWidget(EditEntryButton);
	SideLayout->addWidget(DeleteEntryButton);
	SideLayout->addStretch(); // Push buttons to the top
}
