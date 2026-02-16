#include <QWidget>
#include <QObject>
#include "Entry/Entry.h"

class QLabel;
class QChart;
class QLineSeries;
class QChartView;
class QVBoxLayout;
class QDateTimeAxis;

class ChartView : public QWidget
{
	Q_OBJECT

public:
	ChartView(QWidget* parent = nullptr);

	void UpdateChartData(const QVector<Entry>& Entries);

private:
	QLabel* TitleLabel;
	QVBoxLayout* layout;
	QLineSeries* Series;
	QChartView* View;
};