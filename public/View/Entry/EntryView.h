#include <QObject>
#include <QWidget>

class QLabel;

class EntryView : public QWidget {
	Q_OBJECT;

public:
	EntryView(QWidget* parent = nullptr);

private:
	QLabel* IDLabel;
	QLabel* DateLabel;
	QLabel* AmountLabel;
	QLabel* PersonLabel;
	QLabel* TypeOfTransactionLabel;
};