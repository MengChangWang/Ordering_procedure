#pragma once

#include <QDialog>
#include "ui_dinnerFood.h"

QT_BEGIN_NAMESPACE
namespace Ui { class dinnerFoodClass; };
QT_END_NAMESPACE

class dinnerFood : public QDialog
{
	Q_OBJECT

public:
	dinnerFood(QWidget *parent = nullptr);
	~dinnerFood();
signals:
	void commit_dinnerItem();
private slots:
	void on_yes_clicked();

private:
	Ui::dinnerFoodClass *ui;
};
