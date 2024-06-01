#pragma once
using namespace std;
struct Food {
	QString name;
	QString type;
	double price;
	double discount;
};

class Menu {
public:
	Food m_food;
	QString url;
	static int m_food_count;
	Menu* pNextMenu;
};

class Orderdishes : public Menu {
public:
	int shared;
	double m_price;
	Orderdishes* pNextOrder;
};