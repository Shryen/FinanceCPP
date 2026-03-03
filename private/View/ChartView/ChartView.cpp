#include <QLabel>
#include <QChartView>
#include <QVBoxLayout>
#include <QLineSeries>
#include <QDateTimeAxis>
#include <QValueAxis>
#include <QDateTime>
#include "View/ChartView/ChartView.h"
#include <QDir>

ChartView::ChartView(QWidget* parent) {
    TitleLabel = new QLabel("Transactions", this);
    TitleLabel->setStyleSheet("font-size: 36px; font-weight: bold; color: #042A2B;");
    TitleLabel->setAlignment(Qt::AlignLeft);

    Series = new QLineSeries();
    Series->setName("Money by time");
    Series->setPointsVisible(true);
    Series->setColor(QColor{ "#075F5F" });
    QPen pen = Series->pen();
    pen.setWidth(2);
    Series->setPen(pen);

    View = new QChartView();
    View->setRenderHint(QPainter::Antialiasing);
    View->chart()->legend()->setAlignment(Qt::AlignBottom);

    View->chart()->addSeries(Series);

    AxisX = new QDateTimeAxis;
    AxisY = new QValueAxis;
    AxisX->setFormat("dd/MM/yyyy hh:mm:ss");

    View->chart()->addAxis(AxisX, Qt::AlignBottom);
    View->chart()->addAxis(AxisY, Qt::AlignLeft);
    Series->attachAxis(AxisX);
    Series->attachAxis(AxisY);

    layout = new QVBoxLayout();
    layout->addWidget(TitleLabel);
    layout->addWidget(View);  
    setLayout(layout);
}

void ChartView::UpdateChartData(const QVector<Entry>& Entries)
{
    if (Entries.isEmpty()) return;
    Series->clear();
    QDateTime XDate;
    QDateTime XMin, XMax;
    qreal YMin = 0, YMax = 0;
    qreal YSum = 0;
    for (const Entry& entry : Entries) {
        const int year = entry.DateofRecord.GetYear();
        const int month = entry.DateofRecord.GetEMonth();
        const int day = entry.DateofRecord.GetDay();
        const int hour = entry.DateofRecord.GetHour();
        const int minute = entry.DateofRecord.GetMinute();
        const int second = entry.DateofRecord.GetSecond();
        XDate.setDate(QDate{ year, month, day });
        XDate.setTime(QTime{ hour, minute, second });
        Currency Amount = entry.amount;
        if (entry.TypeOfEntry == type::withdraw) 
			YSum -= Amount.ToEuros() ;
		else if (entry.TypeOfEntry == type::payin)
            YSum += Amount.ToEuros();

        if (Series->count() == 0) XMin = XDate;
        XMax = XDate;
        YMax = std::max(YMax, YSum);
        YMin = std::min(YMin, YSum);
        
        qDebug() << "X:" << XDate.toMSecsSinceEpoch() << "Y:" << YSum;
        Series->append(XDate.toMSecsSinceEpoch(), YSum);
    }

    AxisX->setRange(XMin, XMax);
    AxisY->setRange(YMin, YMax + 1);
 }
