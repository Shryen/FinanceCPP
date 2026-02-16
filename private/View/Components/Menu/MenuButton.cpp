#include "View/Components/Menu/MenuButton.h"

MenuButton::MenuButton(QString Text, QWidget* parent) : Text(Text), parent(parent)
{
	this->setStyleSheet(
		"QPushButton {"
		"background-color: #192841;"
		"color: white;"
		"border: 1px solid black;"
		"padding: 10px 20px;"
		"font-size: 14px;"
		"border-radius: 5px;"
		"}"
		"QPushButton:hover {"
		"background-color: #1A4E9C;"
		"}"
	);
	this->setText(Text);
	this->setCursor(Qt::PointingHandCursor);
}