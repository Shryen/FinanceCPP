#include "Window/Window.h"


Window::Window(QString Title, int w, int h, QWidget* parent) : Title(Title), width(w), height(h), QWidget(parent)
{
	this->resize(QSize{ width,height });
	this->setWindowTitle(this->Title);
}
