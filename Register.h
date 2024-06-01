#pragma once

#include <QWidget>
#include "ui_Register.h"
#include <QString>
#include <QLineEdit>
#include <memory>
using namespace std;


QT_BEGIN_NAMESPACE
namespace Ui { class RegisterClass; };
QT_END_NAMESPACE

class Register : public QWidget
{
	Q_OBJECT

public:
	Register(QWidget *parent = nullptr, shared_ptr<unordered_map<QString, QString>> managerInfo = nullptr);
	~Register();
	shared_ptr<unordered_map<QString, QString>> managerInfo;
private:
	Ui::RegisterClass* ui;
	
signals:
	void bacToLogin();

public slots:
	virtual void CheckInputInfo();
};
