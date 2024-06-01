#include "Takeaway.h"

Takeaway::Takeaway(QWidget *parent)
	: QDialog(parent)
	, ui(new Ui::TakeawayClass())
{
	ui->setupUi(this);
}

Takeaway::~Takeaway()
{
	delete ui;
}
void Takeaway::on_clear_clicked()
{
	ui->lineEdit->clear();
	ui->lineEdit_2->clear();
	ui->lineEdit_3->clear();
	ui->textEdit->clear();
}

void Takeaway::on_yes_clicked()
{
	commit_orderItem();
	this->close();
}