#include "dish.h"

dish::dish(QWidget *parent)
	: QWidget(parent)
	, ui(new Ui::dishClass())
{
	ui->setupUi(this);
}

dish::~dish()
{
	delete ui;
}
void dish::setPicture(QString& path)
{
	QPixmap pixmap(path);
	ui->imageLab->setPixmap(pixmap);
	ui->imageLab->setScaledContents(true);
}

void dish::setDishData(QString& name, double& price)
{
	ui->nameLab->setText(name);
	ui->priceLab->setText(QString("￥") + QString::number(price) +"/份");
	ui->numLab->setText("0");
	ui->sub->setEnabled(false);
}

void dish::on_add_clicked()
{
	QString num = ui->numLab->text();
	unsigned int numInt = num.toUInt();
	numInt++;
	ui->numLab->setText(QString::number(numInt));
	ui->numLab->setScaledContents(true);
	ui->sub->setEnabled(true);
	sendDishData(dishData.name, dishData.price, dishData.discount, numInt);
}
void dish::on_sub_clicked()
{
	QString num = ui->numLab->text();
	unsigned int numInt = num.toUInt();
	if (numInt > 0)
	{
		numInt--;
		ui->numLab->setText(QString::number(numInt));
		ui->numLab->setScaledContents(true);
		sendDishData(dishData.name, dishData.price, dishData.discount, numInt);
		if (numInt == 0)
		{
			ui->sub->setEnabled(false);
		}
	}
}

void dish::initDishData(QString& name, double& price, double& discount)
{
	dishData.name = name;
	dishData.price = price;
	dishData.discount = discount;
}
void dish::clearDishData()
{
	ui->numLab->setText("0");
	ui->sub->setEnabled(false);
	
}
