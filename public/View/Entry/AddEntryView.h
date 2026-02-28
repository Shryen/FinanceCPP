#pragma once
#include <QWidget>
#include <QObject>

class QLineEdit;
class QPushButton;

class AddEntryView : public QWidget {
	Q_OBJECT

public:
	AddEntryView(QWidget* parent = nullptr);

signals:
	void buttonClicked(const QString& Amount);

private:
	QLineEdit* AmountInput;
	QPushButton* AddEntryButton;
};