#pragma once

#include <QWidget>
#include "Manager.h"
#include "ui_ManagerInterface.h"
#include <QFile>
#include <QMessageBox>
#include <QTimer>
#include <QTableWidget>
#include <QCheckBox>
#include <QFileDialog>
QT_BEGIN_NAMESPACE
namespace Ui { class ManagerInterfaceClass; };
QT_END_NAMESPACE

class ManagerInterface : public QWidget
{
	Q_OBJECT

public:
	ManagerInterface(QWidget *parent = nullptr, Manager* manager = nullptr, shared_ptr<unordered_map<QString, QString>> managerInfo = nullptr);
	~ManagerInterface();
	void creatTableRows(int rowNo,QString menuName,QString type,double price,double discount,QString imagePath);
	void readMenuInfo();
	void saveMenuInfo();
	void displayOrder();

private:
	Ui::ManagerInterfaceClass *ui;
	shared_ptr<unordered_map<QString, QString>> managerInfo;
	Manager* manager;
	QString imagePath;

private slots:
	void on_YES_clicked();
	void on_Back_clicked();
	void on_clear_clicked();
	void on_commit_clicked();
	void on_select_clicked();
	void on_save_clicked();
	void on_deleteBut_clicked();
	void on_openfile_clicked();
};
