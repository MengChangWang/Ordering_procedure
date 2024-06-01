#pragma once

#include <QWidget>
#include "ui_dish.h"
#include <QPixmap>


QT_BEGIN_NAMESPACE
namespace Ui { class dishClass; };
QT_END_NAMESPACE

typedef struct {
	QString name;
	double price;
	double discount;
} dishInfo;

class dish : public QWidget
{
	Q_OBJECT

public:
	dish(QWidget *parent = nullptr);
	~dish();
	void setPicture(QString &path);
	void setDishData(QString& name, double& price);
	void initDishData(QString& name, double& price, double& discount);

signals:
	emit void sendDishData(QString& name, double& price, double& discount,unsigned int& num);
private slots:
	void on_add_clicked();
	void on_sub_clicked();
	void clearDishData();


private:
	Ui::dishClass *ui;
	dishInfo dishData;
};
