#include "Manager.h"
int Menu::m_food_count = 0;
Manager::Manager(QObject *parent)
	: QObject(parent)
{}

Manager::Manager(const QString& name, const QString& password, bool loggedIn = false)
{
	m_name = name;
	m_password = password;
	m_loggedIn = loggedIn;
}
void Manager::setName(QString& name)
{
	m_name = name;
}
void Manager::setPassword(QString& password)
{
	m_password = password;
}
void Manager::addMenu(Menu** ppMenu, QString& name, QString& type, double price, double discount)
{
	Menu* pMenu = new Menu;
	
	pMenu->m_food.name = name;
	pMenu->m_food.type = type;
	pMenu->m_food.price = price;
	pMenu->m_food.discount = discount;

	Menu* cur;

	while ((cur = *ppMenu) != NULL && cur->m_food.name != name)
	{
		ppMenu = &cur->pNextMenu;
	}
	while ((cur = *ppMenu) != NULL && cur->m_food.name == name)
	{
		ppMenu = &cur->pNextMenu;
	}
	Menu::m_food_count++;
	*ppMenu = pMenu;
}
void Manager::deleteMenu(Menu** ppMenu, int index)
{	
	Menu* cur;
	index--;
	while ((cur = *ppMenu) && index)
	{
		*ppMenu = cur->pNextMenu;
		index--;
	}
	if (cur)
	{
		*ppMenu = cur->pNextMenu;
		delete cur;
		Menu::m_food_count--;
	}
}

void Manager::displayMenu(Menu** ppMenu)
{

}
QString Manager::getName()
{
	return m_name;
}

QString Manager::getPassword()
{
	return m_password;
}

Manager::~Manager()
{
}
