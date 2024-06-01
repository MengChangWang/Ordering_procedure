#include "OrderItem.h"

OrderItem::OrderItem(QWidget *parent)
	: QDialog(parent)
	, ui(new Ui::OrderItemClass())
{
	ui->setupUi(this);
}

OrderItem::~OrderItem()
{
	delete ui;
}

void OrderItem::setItem(QString& name, double& price, unsigned int& num)
{
	ui->orderList->addItem(name + " ￥" + QString::number(price) + "   x" + QString::number(num));
}
void OrderItem::setItem(double& price)
{
	ui->orderList->addItem("		总价为: ￥" + QString::number(price));
}

void OrderItem::setItem(QString& NO)
{
	ui->orderList->addItem("订单号: " + NO);
}

void OrderItem::on_clear_clicked()
{
	ui->orderList->clear();
	itemCleared();
}
void OrderItem::on_yes_clicked()
{
	this->close();

}