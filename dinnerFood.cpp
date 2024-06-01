#include "dinnerFood.h"

dinnerFood::dinnerFood(QWidget *parent)
	: QDialog(parent)
	, ui(new Ui::dinnerFoodClass())
{
	ui->setupUi(this);
}

dinnerFood::~dinnerFood()
{
	delete ui;
}
void dinnerFood::on_yes_clicked()
{
	commit_dinnerItem();
	this->close();
}