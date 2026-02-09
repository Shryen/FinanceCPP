#include <QWidget>
#include <QString>

class Window : public QWidget {
public:
	Window(QString Title, int w, int h, QWidget* parent = nullptr);

private:
	int width{ 800 };
	int height{ 600 };
	QString Title{ "Finances" };
};