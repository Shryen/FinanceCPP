#include "Window/MainWindow.h"

MainWindow::MainWindow(QString Title, int w, int h, QWidget* parent) : Title(Title), width(w), height(h), QWidget(parent)
{
	resize(QSize{ width, height });
	setWindowTitle(Title);
    this->setStyleSheet("background-color: #0B2D72");

	Filecontroller = new FileController{ "vault.data" };
	CurrencyMgr = new CurrencyManager{};
	Vault = new EntryManager{ Filecontroller, CurrencyMgr };

	SetupUI();
	SetupConnections();
}

void MainWindow::SetupUI()
{
    HLayout = new QHBoxLayout(this);
	HLayout->setContentsMargins(0, 0, 0, 0);
    HLayout->addSpacing(20);

	QLabel* TitleLabel = new QLabel(Title, this);
    TitleLabel->setAlignment(Qt::AlignTop);
    TitleLabel->setAlignment(Qt::AlignHCenter);
    TitleLabel->setStyleSheet(
        "font-size: 24px;" 
        "font-weight:bold;"
        "padding-top: 20px"
    );
	HLayout->addWidget(TitleLabel);

    VLayout = new QVBoxLayout();
    HLayout->addLayout(VLayout);
    VLayout->setContentsMargins(20, 20, 20, 20);
    VLayout->setSpacing(15);
    VLayout->addSpacing(10);
    VLayout->addStretch();

    NameLabel = new QLabel("Enter your name:", this);
    VLayout->addWidget(NameLabel);

    NameInput = new QLineEdit(this);
    VLayout->addWidget(NameInput);

    NameSaveButton = new QPushButton("Save", this);
    VLayout->addWidget(NameSaveButton);
    VLayout->addStretch();
}

void MainWindow::SetupConnections()
{
    connect(NameSaveButton, &QPushButton::clicked, this, [this]() {
        QString name = NameInput->text();
        if (!name.isEmpty()) {
            Vault->SetUserName(name);
            NameLabel->setText("Saved name: " + name);
            NameInput->clear();
        }
    });
}
