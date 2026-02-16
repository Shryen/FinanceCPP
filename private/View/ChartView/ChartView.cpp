#include "View/ChartView/ChartView.h"
#include <QLabel>
#include <QChart>
#include <QChartView>
#include <QVBoxLayout>
#include <QBarSet>
#include <QLineSeries>
#include <QDateTimeAxis>
#include <QValueAxis>
#include <QDateTime>
#include "Currency/CurrencyManager.h"

ChartView::ChartView(QWidget* parent)
{
    TitleLabel = new QLabel("Transactions", this);
    TitleLabel->setStyleSheet("font-size: 36px; font-weight: bold; color: #007;");
    TitleLabel->setAlignment(Qt::AlignLeft);

    layout = new QVBoxLayout();
    layout->addWidget(TitleLabel);
    setLayout(layout);

    Series = new QLineSeries();
    Series->setName("Money by time");
    Series->setPointsVisible(true);
    View = new QChartView();
    View->setRenderHint(QPainter::Antialiasing);
    View->chart()->legend()->setAlignment(Qt::AlignBottom);
    View->chart()->setTheme(QChart::ChartThemeQt);
}

void ChartView::UpdateChartData(const QVector<Entry>& Entries)
{
    if (Entries.isEmpty()) return;

    QDateTime XDate;
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
        YSum += Amount.ToEuros()/100;
        qDebug() << YSum;
        Series->append(XDate.toMSecsSinceEpoch(), YSum);
    }

    QDateTimeAxis* AxisX = new QDateTimeAxis;
    AxisX->setFormat("dd/MM/yyyy hh:mm:ss");
    QValueAxis* AxisY = new QValueAxis;
    AxisY->setLabelFormat("%.2f");
    View->chart()->addSeries(Series);
    View->chart()->setAxisX(AxisX, Series);
    View->chart()->setAxisY(AxisY, Series);

    layout->addWidget(View);
}
