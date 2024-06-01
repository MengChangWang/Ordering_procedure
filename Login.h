#pragma once

#include <QWidget>
#include <QMessageBox>
#include "ui_Login.h"
#include "Register.h"
#include <QFile>
#include "ManagerInterface.h"
#include "Menu.h"
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class LoginClass; };
QT_END_NAMESPACE

class Login : public QWidget
{
	Q_OBJECT

public:
	Login(QWidget *parent = nullptr);
	void RunManagerInterface(QString username, QString password,bool isLogin, shared_ptr<unordered_map<QString, QString>>& managerInfo);
	~Login();
	void ReadManagerInfo(QFile& file, shared_ptr<unordered_map<QString, QString>>& managerInfo);
	Menu *menu;

private:
	Ui::LoginClass *ui;
	Register *ui_register;
	ManagerInterface *ui_managerInterface;
	shared_ptr<unordered_map<QString, QString>> managerInfo;

private slots:
	void CheckInputInfo();

};
