#pragma once

#include <QDialog>
#include "ui_OrderItem.h"

QT_BEGIN_NAMESPACE
namespace Ui { class OrderItemClass; };
QT_END_NAMESPACE

class OrderItem : public QDialog
{
	Q_OBJECT

public:
	OrderItem(QWidget *parent = nullptr);
	~OrderItem();
	void setItem(QString& itemName, double& itemPrice, unsigned int& num);
	void setItem(double& totalPrice);
	void setItem(QString& NO);
private slots:
	void on_yes_clicked();
	void on_clear_clicked();

signals:
	void itemCleared();

private:
	Ui::OrderItemClass *ui;
};
