#include "ManagerInterface.h"

ManagerInterface::ManagerInterface(QWidget *parent,Manager* manager, shared_ptr<unordered_map<QString, QString>> managerInfo)
	: QWidget(parent), manager(manager), managerInfo(managerInfo)
	, ui(new Ui::ManagerInterfaceClass())
{
	ui->setupUi(this);
	ui->UserName->setMaxLength(10);
	ui->Password->setMaxLength(10);
	ui->Checking->setMaxLength(10);
	ui->Password->setEchoMode(QLineEdit::PasswordEchoOnEdit);
	ui->Checking->setEchoMode(QLineEdit::PasswordEchoOnEdit);
	ui->UserName->setText(manager->getName());
	ui->UserName->setReadOnly(true);
	ui->discount->setText("100");
	ui->menuTable->setSelectionBehavior(QAbstractItemView::SelectRows);
	ui->menuTable->setColumnWidth(0, 150);
	ui->menuTable->setColumnHidden(4, true);
	readMenuInfo();
	displayOrder();
}

ManagerInterface::~ManagerInterface()
{
	delete ui;
}

void ManagerInterface::readMenuInfo()
{
	QFile file("menuInfo.dat");
	file.open(QIODevice::ReadOnly);
	if (!file.isOpen())
	{
		qDebug() << "文件打开失败1";
		QMessageBox::warning(this, "Warning", "您尚未创建菜单,请注意创建");
	}
	else
	{
		QString name;
		QString type;
		double price;
		double discount;
		QString imagePath;
		QDataStream in(&file);
		while (!in.atEnd())
		{
			in >> name >> type >> price >> discount>> imagePath;
			ui->menuTable->insertRow(ui->menuTable->rowCount());
			creatTableRows(ui->menuTable->rowCount()-1, name, type, price, discount,imagePath);
			qDebug() << name << type << price << discount << imagePath;
		}
	}
	file.close();
}

void ManagerInterface::on_select_clicked()
{
	
	QTableWidgetItem* item;
	for (int i = 0; i < ui->menuTable->rowCount(); i++)
	{
		item = ui->menuTable->item(i, 0);
		item->setCheckState(Qt::Unchecked);
	}

}

void ManagerInterface::on_YES_clicked()
{
	QTimer* tm = new QTimer(this);
	tm->setSingleShot(true);
	tm->setInterval(1000);
	QString password = ui->Password->text();
	QString checking = ui->Checking->text();
	if (password.isEmpty() || checking.isEmpty())
	{
		ui->display->setStyleSheet("color: red;"  " font-size: 10px;");
		ui->display->setAlignment(Qt::AlignRight);
		ui->display->setText("输入密码不能为空");
		tm->start();
		connect(tm, &QTimer::timeout, [=]() {
			ui->display->clear();});
	}
	else if (password == checking)
	{
	
		QString userName = ui->UserName->text();
		(*managerInfo)[userName] = password;
		QFile file("manangerInfo.dat");
		file.open(QIODevice::WriteOnly);
		if (!file.isOpen())
		{
			qDebug() << "文件打开失败";
			QMessageBox::warning(this, "Warning", "文件打开失败");
			return;
		}
		for (auto it = managerInfo->begin(); it != managerInfo->end(); it++)
		{
			QDataStream out(&file);
			out << it->first << it->second;
		}
		file.close();
		ui->display->setStyleSheet("color: green;"  " font-size: 10px;");
		ui->display->setAlignment(Qt::AlignRight);
		ui->display->setText("密码修改成功");
		tm->start();
		connect(tm, &QTimer::timeout, [=]() {
			ui->display->clear(); });
		manager->setPassword(password);
		
	}
	else
	{
		ui->display->setStyleSheet("color: red;"  " font-size: 10px;");
		ui->display->setAlignment(Qt::AlignRight);
		ui->display->setText("两次输入的密码不一致");
		tm->start();
		connect(tm, &QTimer::timeout, [=]() {
			ui->display->clear();});
	}
}

void ManagerInterface::on_Back_clicked()
{
	ui->Password->clear();
	ui->Checking->clear();
}


void ManagerInterface::on_clear_clicked()
{
	ui->menuName->clear();
	ui->price->clear();
	ui->discount->setText("100");
	ui->image->setText("NULL");
}

void ManagerInterface::on_commit_clicked()
{
	int rowNo = ui->menuTable->rowCount();
	QString menuName = ui->menuName->text();
	QString type = ui->type->currentText();
	double price = ui->price->text().toDouble();
	double discount = ui->discount->text().toDouble();
	QString imagepath = imagePath;

	if (menuName.isEmpty() || type.isEmpty() || price == 0)
	{
		QMessageBox::warning(this, "Warning", "输入不能为空");
	}
	else
	{
		ui->menuTable->insertRow(rowNo);
		creatTableRows(rowNo, menuName, type, price, discount,imagepath);
	}
	ui->menuName->clear();
	ui->price->clear();
	ui->discount->setText("100");
	ui->image->setText("NULL");
}

void ManagerInterface::creatTableRows(int rowNo,  QString menuName, QString type, double price, double discount,QString imagePath)
{
	QTableWidgetItem* item;
	
	item = new QTableWidgetItem(menuName);
	item->setTextAlignment(Qt::AlignCenter);
	ui->menuTable->setItem(rowNo, 0, item);

	item = new QTableWidgetItem(type);
	item->setTextAlignment(Qt::AlignCenter);
	ui->menuTable->setItem(rowNo, 1, item);	

	item = new QTableWidgetItem(QString::number(price, 'f', 2));
	item->setTextAlignment(Qt::AlignCenter);
	ui->menuTable->setItem(rowNo, 2, item);

	item = new QTableWidgetItem(QString::number(discount, 'f', 2));
	item->setTextAlignment(Qt::AlignCenter);
	ui->menuTable->setItem(rowNo, 3, item);

	item = new QTableWidgetItem(imagePath);
	item->setTextAlignment(Qt::AlignCenter);
	ui->menuTable->setItem(rowNo, 4, item);

}

void ManagerInterface::saveMenuInfo()
{
	QFile file("menuInfo.dat");
	file.open(QIODevice::WriteOnly);
	if (!file.isOpen())
	{
		qDebug() << "文件打开失败2";
	}
	else
	{
		QDataStream out(&file);
		for (int i = 0; i < ui->menuTable->rowCount(); i++)
		{
			QTableWidgetItem* item = ui->menuTable->item(i, 0);
			QString menuName = item->text();
			item = ui->menuTable->item(i, 1);
			QString type = item->text();
			item = ui->menuTable->item(i, 2);
			double price = item->text().toDouble();
			item = ui->menuTable->item(i, 3);
			double discount = item->text().toDouble();

			item = ui->menuTable->item(i, 4);
			QString imagePath = item->text();

			out << menuName << type << price << discount<<imagePath;
		
		}
		file.close();
		qDebug() << "菜单信息保存成功";
	}
}
void ManagerInterface::on_save_clicked()
{
	saveMenuInfo();
}

void ManagerInterface::on_deleteBut_clicked()
{
	for (int i = 0; i < ui->menuTable->rowCount()&&ui->menuTable->item(i,0) != NULL; i++)
	{
		if (ui->menuTable->item(i, 0)->checkState() == Qt::Checked)
		{
			ui->menuTable->removeRow(i);
			i--;
		}
		else
			continue;
	}
}

void ManagerInterface::on_openfile_clicked()
{
	QString curPath = QDir::currentPath();
	QString tempimagePath = QFileDialog::getOpenFileName(this, "选择图片", curPath, "图片文件(*.jpg *.png)");
	if (!tempimagePath.isEmpty())
	{
		imagePath = tempimagePath;
		QPixmap pixmap(imagePath);
		ui->image->setPixmap(pixmap);
		ui->image->setScaledContents(true);
	}

}

void ManagerInterface::displayOrder()
{
	QFile file("orderInfo.txt");
	file.open(QIODevice::ReadOnly | QIODevice::Text);
	if (!file.isOpen())
	{
		qDebug() << "orderInfo.txt文件打开失败";
	}
	else
	{
		QTextStream in(&file);
		ui->displayOrder->clear();
		ui->displayOrder->setReadOnly(true);
		ui->displayOrder->setPlainText(in.readAll());
		
	}
	file.close();
}
