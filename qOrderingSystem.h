#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_qOrderingSystem.h"
#include "UserInterface.h"
#include "Login.h"

QT_BEGIN_NAMESPACE
namespace Ui { class qOrderingSystemClass; };
QT_END_NAMESPACE

class qOrderingSystem : public QMainWindow
{
    Q_OBJECT

public:
    qOrderingSystem(QWidget *parent = nullptr);
    ~qOrderingSystem();

private:
    Ui::qOrderingSystemClass *ui;
    UserInterface* ui_userInterface = nullptr;
    Login* ui_login = nullptr;

};
