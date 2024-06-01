#pragma once

#include <QWidget>
#include "ui_UserInterface.h"
#include "dish.h"
#include <QFile>
#include <vector>
#include <QTime>
#include "OrderItem.h"
#include "Takeaway.h"
#include <QMessageBox>
#include "dinnerFood.h"
using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class UserInterfaceClass; };
QT_END_NAMESPACE

typedef struct {
	QString name;
	QString type;
	double price;
	double discount;
	QString imagePath;
}menuInfo;

typedef struct {
	QString name;
	double price;
	double discount;
	unsigned int num;
}orderInfo;

class UserInterface : public QWidget
{
	Q_OBJECT

public:
	UserInterface(QWidget *parent = nullptr);
	~UserInterface();
	void hideHeader();
	void initTablesetting();
	void initTable();
	void saveOrderList();
private slots:
	void receiveDishData(QString& name, double& price, double& discount, unsigned int& num);
	void resetOrderList();
	void on_order_clicked();
	void on_takeaway_clicked();
	void on_dinnerFood_clicked();
private:
	Ui::UserInterfaceClass *ui;
	menuInfo one_dish;
	OrderItem* current_order;
	vector<orderInfo> order_list;
	static int NO;
	Takeaway* tky;
	dinnerFood* dF;
};
