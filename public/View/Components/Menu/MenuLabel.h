#ifndef MENULABEL_H
#define MENULABEL_H
#include <QLabel>

class QString;
class QWidget;

class MenuLabel : public QLabel {
public:
	MenuLabel(QString Text, QWidget* parent = nullptr);

private:
	QString Text;
	QWidget* parent;
};

#endif