#pragma once

#include <QDialog>
#include "ui_Takeaway.h"

QT_BEGIN_NAMESPACE
namespace Ui { class TakeawayClass; };
QT_END_NAMESPACE

class Takeaway : public QDialog
{
	Q_OBJECT

public:
	Takeaway(QWidget *parent = nullptr);
	~Takeaway();

private slots:
	void on_clear_clicked();
	void on_yes_clicked();
signals:
	void commit_orderItem();
private:
	Ui::TakeawayClass *ui;
};
