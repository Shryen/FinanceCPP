#include <View/Entry/AddEntryView.h>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>

AddEntryView::AddEntryView(QWidget* parent) : QWidget(parent) {
	this->setStyleSheet("font-size: 24px; font-weight: bold; color: #042A2B;");

	AmountInput = new QLineEdit;
	AddEntryButton = new QPushButton;
	AddEntryButton->setText("Add");
    AddEntryButton->setCursor(Qt::PointingHandCursor);
    AmountInput->setStyleSheet(
        "background-color: #ccc;"
        "border-radius: 10px;"
        "padding: 6px;"
        "font-size: 24px;"
    );

    AddEntryButton->setStyleSheet(
        "background-color: #1D4249;"
        "color: #FCFCFC;"
        "border-radius: 10px;"
        "padding: 10px 8;"
        "font-size: 24px;"
    );

    QLabel* TitleLabel = new QLabel("Add entry to the chart");
    TitleLabel->setStyleSheet(
        "font-size: 32px;"
        "font-weight: bold;"
        "color: #042A2B;"
    );
    TitleLabel->setAlignment(Qt::AlignHCenter);

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setSpacing(16);
    layout->setContentsMargins(0, 20, 0, 20);

    layout->addStretch();
    layout->addWidget(TitleLabel, 0, Qt::AlignHCenter);
    layout->addWidget(AmountInput, 0, Qt::AlignHCenter);
    layout->addWidget(AddEntryButton, 0, Qt::AlignHCenter);
    layout->addStretch();

    setLayout(layout);

    connect(AddEntryButton, &QPushButton::clicked, this, [this]() {
        emit buttonClicked(AmountInput->text());
    });
}