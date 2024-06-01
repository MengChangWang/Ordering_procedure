#include "Register.h"
#include <QMessageBox>
#include <QString>
#include <unordered_map>
#include <QLabel>
#include <QFile>
#include <QDataStream>

Register::Register(QWidget *parent, shared_ptr<unordered_map<QString, QString>> managerInfo)
	: QWidget(parent), managerInfo(managerInfo)
	, ui(new Ui::RegisterClass())
{
	ui->setupUi(this);
	ui->UserName->setMaxLength(10);
	ui->Password->setMaxLength(10);
	ui->Checking->setMaxLength(10);
	ui->Password->setEchoMode(QLineEdit::PasswordEchoOnEdit);
	ui->Checking->setEchoMode(QLineEdit::PasswordEchoOnEdit);
	connect(ui->Back, SIGNAL(clicked()), this, SIGNAL(bacToLogin()));
	connect(ui->Back, &QPushButton::clicked, this, [=]() {
		ui->display->clear();
		ui->UserName->clear();
		ui->Password->clear();
		ui->Checking->clear(); });
	connect(ui->YES, SIGNAL(clicked()), this, SLOT(CheckInputInfo()));
	
	

}


void Register::CheckInputInfo()
{
	QString userName = ui->UserName->text();
	QString password = ui->Password->text();
	QString checking = ui->Checking->text();
	if (managerInfo->find(userName) != managerInfo->end())
	{
		ui->display->setStyleSheet("color: red;"  " font-size: 10px;");
		ui->display->setAlignment(Qt::AlignRight);
		ui->display->setText("用户名已存在");
	}
	else if (password!= checking)
	{
		ui->display->setStyleSheet("color: red;"  " font-size: 10px;");
		ui->display->setAlignment(Qt::AlignRight);
		ui->display->setText("密码不一致");
		ui->Password->clear();
		ui->Checking->clear();
	}
	else if (userName.isEmpty() || password.isEmpty() || checking.isEmpty())
	{
		ui->display->setStyleSheet("color: red;"  " font-size: 10px;");
		ui->display->setAlignment(Qt::AlignRight);
		ui->display->setText("用户名或密码不能为空");
	}
	else
	{
		(*managerInfo)[userName] = password;
		QFile file("manangerInfo.dat");
		file.open(QIODevice::WriteOnly );
		if (!file.isOpen())
		{
			qDebug() << "文件打开失败";
			QMessageBox::warning(this, "Warning", "文件打开失败");
			return;
		}
		for (auto it = managerInfo->begin(); it != managerInfo->end(); it++)
		{
			QDataStream out(&file);
			out << it->first << it->second;
		}
		file.close();
		ui->display->setStyleSheet("color: green;"  " font-size: 10px;");
		ui->display->setAlignment(Qt::AlignRight);
		ui->display->setText("注册成功");
	}
}

Register::~Register()
{
	
	delete ui;
}
