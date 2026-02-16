#include <QWidget>
class QPushButton;
class QHBoxLayout;
class QVBoxLayout;

class LoginView : public QWidget
{
	Q_OBJECT
public:
	LoginView(QWidget* parent = nullptr);

signals:
	void LoginButtonClicked(QString CurrentUser);
public slots:
	void OnAnaButtonClicked() { emit LoginButtonClicked("Ana"); }
	void OnKriszButtonClicked() { emit LoginButtonClicked("Krisz"); }

private:
	//LAYOUT AND WIDGET
	QVBoxLayout* LoginLayout;
	QWidget* LoginWidget;

	// BUTTONS
	QPushButton* AnaButton;
	QPushButton* KriszButton;

	void SetupButtons();
};