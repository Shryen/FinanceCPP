#include "View/Components/Menu/MenuLabel.h"

MenuLabel::MenuLabel(QString Text, QWidget* parent) : QLabel(parent), Text(Text), parent(parent)
{
	this->setText(Text);
	this->setAlignment(Qt::AlignCenter);
	this->setStyleSheet("font-size: 24px; margin-bottom: 10px;");
	this->setAlignment(Qt::AlignJustify);
}
