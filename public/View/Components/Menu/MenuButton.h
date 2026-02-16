#ifndef MENUBUTTON_H
#define MENUBUTTON_H

#include <QPushButton>

class MenuButton : public QPushButton {
public:
	MenuButton(QString Text, QWidget* parent = nullptr);

private:
	QString Text;
	QWidget* parent;
};

#endif