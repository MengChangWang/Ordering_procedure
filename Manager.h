#pragma once
#include <QObject>
#include "Menu.h"



class Manager  : public QObject
{
	Q_OBJECT

private:
	QString m_name;
	QString m_password;
	bool m_loggedIn;

public:
	Manager(QObject *parent);
	Manager(const QString& name,const QString& password,bool loggedIn);
	void setName(QString& name);
	void setPassword(QString& password);
	void addMenu(Menu** ppMenu, QString& name, QString& type, double price, double discount);
	void deleteMenu(Menu** ppMenu, int index);
	void displayMenu(Menu** ppMenu);
	QString getName();
	QString getPassword();

	~Manager();
};
