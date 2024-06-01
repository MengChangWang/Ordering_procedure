#include "qOrderingSystem.h"

qOrderingSystem::qOrderingSystem(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::qOrderingSystemClass())
{
    ui->setupUi(this);
    
    connect(ui->User, &QPushButton::clicked, this, [=]() {
        ui_userInterface = new UserInterface();
        this->hide();
        ui_userInterface->show();
        });
    connect(ui->Manager, &QPushButton::clicked, this, [=]() {
        ui_login = new Login();
        this->hide();
        ui_login->show();
    });

}

qOrderingSystem::~qOrderingSystem()
{
    delete ui;
}
