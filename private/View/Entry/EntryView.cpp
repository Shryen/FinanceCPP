#include "View/Entry/EntryView.h"
#include <QLabel>
#include <QHBoxLayout>

EntryView::EntryView(QWidget* parent) 
{
	this->setStyleSheet(
		"background-color: #ccc;"
		"border: 1px solid black;"
		"border-radius: 10px;"
	);
	IDLabel = new QLabel{ "ID" };
	DateLabel = new QLabel{ "Date" };
	AmountLabel = new QLabel{ "Amount" };
	PersonLabel = new QLabel{ "Person" };
	TypeOfTransactionLabel = new QLabel{ "Type" };

	QHBoxLayout* layout = new QHBoxLayout(this);
	layout->addWidget(IDLabel);
	layout->addWidget(DateLabel);
	layout->addWidget(AmountLabel);
	layout->addWidget(PersonLabel);
	layout->addWidget(TypeOfTransactionLabel);
}
