#include "UserInterface.h"

int UserInterface::NO = 0;

UserInterface::UserInterface(QWidget *parent)
	: QWidget(parent)
	, ui(new Ui::UserInterfaceClass())
{
	ui->setupUi(this);
	initTablesetting();
	initTable();
}

UserInterface::~UserInterface()
{
	delete ui;
}
void UserInterface::hideHeader()
{
	//隐藏行表头和列表头还有表格线
	ui->Vegetable->horizontalHeader()->hide();
	ui->Vegetable->verticalHeader()->hide();
	ui->Vegetable->setShowGrid(false);

	ui->Meat->horizontalHeader()->hide();
	ui->Meat->verticalHeader()->hide();
	ui->Meat->setShowGrid(false);

	ui->Drink->horizontalHeader()->hide();
	ui->Drink->verticalHeader()->hide();
	ui->Drink->setShowGrid(false);

	ui->something->horizontalHeader()->hide();
	ui->something->verticalHeader()->hide();
	ui->something->setShowGrid(false);

	ui->Snack->horizontalHeader()->hide();
	ui->Snack->verticalHeader()->hide();
	ui->Snack->setShowGrid(false);

	ui->Seafood->horizontalHeader()->hide();
	ui->Seafood->verticalHeader()->hide();
	ui->Seafood->setShowGrid(false);

}
void UserInterface::initTablesetting()
{
	hideHeader();
	ui->Seafood->setSelectionMode(QAbstractItemView::NoSelection);
	ui->Snack->setSelectionMode(QAbstractItemView::NoSelection);
	ui->something->setSelectionMode(QAbstractItemView::NoSelection);
	ui->Drink->setSelectionMode(QAbstractItemView::NoSelection);
	ui->Meat->setSelectionMode(QAbstractItemView::NoSelection);
	ui->Vegetable->setSelectionMode(QAbstractItemView::NoSelection);

	ui->Seafood->setEditTriggers(QAbstractItemView::NoEditTriggers);
	ui->Snack->setEditTriggers(QAbstractItemView::NoEditTriggers);
	ui->something->setEditTriggers(QAbstractItemView::NoEditTriggers);
	ui->Drink->setEditTriggers(QAbstractItemView::NoEditTriggers);
	ui->Meat->setEditTriggers(QAbstractItemView::NoEditTriggers);
	ui->Vegetable->setEditTriggers(QAbstractItemView::NoEditTriggers);

	ui->Vegetable->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	ui->Vegetable->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	ui->Meat->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	ui->Meat->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	ui->Drink->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	ui->Drink->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	ui->something->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	ui->something->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	ui->Snack->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	ui->Snack->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	ui->Seafood->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	ui->Seafood->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}
void UserInterface::initTable()
{
	qDebug() << "initTable";

	int meat_count = 0;
	int vegetable_count = 0;
	int snack_count = 0;
	int seafood_count = 0;
	int something_count = 0;
	int drink_count = 0;

	QFile menuFile("menuInfo.dat");
	if (!menuFile.open(QIODevice::ReadOnly)) {
		qDebug() << "Failed to open menu file.";
		QMessageBox::warning(this, "提示", "管理员尚未添加菜单信息");
	}
	QDataStream in(&menuFile);
	while (!in.atEnd()) {
		in >> one_dish.name >> one_dish.type >> one_dish.price >> one_dish.discount >> one_dish.imagePath;
		dish* Tab = new dish();
		Tab->setPicture(one_dish.imagePath);
		Tab->setDishData(one_dish.name,one_dish.price);
		Tab->initDishData(one_dish.name, one_dish.price, one_dish.discount);

		if (one_dish.type == "素菜") {
			ui->Vegetable->horizontalHeader()->setDefaultSectionSize(Tab->width());
			ui->Vegetable->verticalHeader()->setDefaultSectionSize(Tab->height());
			ui->Vegetable->setCellWidget(vegetable_count / 3, vegetable_count % 3, Tab);

			vegetable_count++;
		}
		else if (one_dish.type == "荤菜") {
			ui->Meat->horizontalHeader()->setDefaultSectionSize(Tab->width());
			ui->Meat->verticalHeader()->setDefaultSectionSize(Tab->height());
			ui->Meat->setCellWidget(meat_count / 3, meat_count % 3, Tab);

			meat_count++;
		}
		else if (one_dish.type == "酒水") {
			ui->Drink->horizontalHeader()->setDefaultSectionSize(Tab->width());
			ui->Drink->verticalHeader()->setDefaultSectionSize(Tab->height());
			ui->Drink->setCellWidget(drink_count / 3, drink_count % 3, Tab);
			drink_count++;
		}
		else if (one_dish.type == "小吃") {
			ui->Snack->horizontalHeader()->setDefaultSectionSize(Tab->width());
			ui->Snack->verticalHeader()->setDefaultSectionSize(Tab->height());
			ui->Snack->setCellWidget(snack_count / 3, snack_count % 3, Tab);

			snack_count++;
		}
		else if (one_dish.type == "其他") {
			ui->something->horizontalHeader()->setDefaultSectionSize(Tab->width());
			ui->something->verticalHeader()->setDefaultSectionSize(Tab->height());
			ui->something->setCellWidget(something_count / 3, something_count % 3, Tab);
			something_count++;
		}
		
		else if (one_dish.type == "海鲜") {
			ui->Seafood->horizontalHeader()->setDefaultSectionSize(Tab->width());
			ui->Seafood->verticalHeader()->setDefaultSectionSize(Tab->height());
			ui->Seafood->setCellWidget(seafood_count / 3, seafood_count % 3, Tab);
			seafood_count++;
		}
		qDebug() << one_dish.name << one_dish.type << one_dish.price << one_dish.discount << one_dish.imagePath;

		connect(ui->reset,SIGNAL(clicked()),Tab,SLOT(clearDishData()));
		connect(ui->reset,SIGNAL(clicked()),this,SLOT(resetOrderList()));
		connect(Tab,&dish::sendDishData,this,&UserInterface::receiveDishData);
	}
	menuFile.close();
}

void UserInterface::receiveDishData(QString& dishName, double& dishPrice,double& dishDiscount, unsigned int& dishNum)
{
	orderInfo one_order;
	one_order.price = dishPrice;
	one_order.discount = dishDiscount;
	one_order.name = dishName;
	one_order.num = dishNum;

	for (int i = 0; i < order_list.size(); i++)
	{
		if (order_list[i].name == dishName)
		{
			if (dishNum <= 0)
			{
				order_list.erase(order_list.begin() + i);
				qDebug() << "receiveDishData" << dishName << dishPrice << dishDiscount << dishNum;
				return;
			}
			order_list[i].num = dishNum;
			qDebug() << "receiveDishData" << dishName << dishPrice << dishDiscount << dishNum;
			return;
		}
	}
	order_list.push_back(one_order);

	qDebug() << "receiveDishData" << dishName << dishPrice << dishDiscount << dishNum;
}
void UserInterface::resetOrderList()
{
	order_list.clear();
	qDebug() << "resetOrderList";
}
void UserInterface::saveOrderList()
{
	QDateTime time = QDateTime::currentDateTime();	//id号以时间戳和自增数生成
	QString order_id = time.toString("yyyyMMdd") + QString::number(NO);

	double total_price = 0;
	for (int i = 0; i < order_list.size(); i++)
	{
		total_price += order_list[i].price * order_list[i].num*(order_list[i].discount/100.0);
	}
	QFile orderFile("orderInfo.txt");
	if (!orderFile.open( QIODevice::Append)) {
		qDebug() << "Failed to open order file.";
	}
	QTextStream out(&orderFile);
	out << "订餐编号:"<<order_id<<"\n";
	for (int i = 0; i < order_list.size(); i++)
	{
		out << "菜名:" << order_list[i].name <<"  " << "单价:" << order_list[i].price <<"元  " << "折扣:" << order_list[i].discount <<"%  " << "数量:" << order_list[i].num\
			<< "\n";
	}
	out << "总价:" << total_price<<"元";
	out<<"\n";
	orderFile.close();
}

void UserInterface::on_order_clicked()
{
	NO++;
	QDateTime time = QDateTime::currentDateTime();	//id号以时间戳和自增数生成
	QString order_id = time.toString("yyyyMMdd") + QString::number(NO);
	qDebug() << "order_id:" << order_id;
	current_order = new OrderItem();
	current_order->show();
	QString name; double price; double discount; unsigned int num;
	double total_price = 0;
	current_order->setItem(order_id);
	for (int i = 0; i < order_list.size(); i++)
	{
		name = order_list[i].name;
		price = order_list[i].price;
		discount = order_list[i].discount;
		num = order_list[i].num;
		current_order->setItem(name, price, num);
		total_price += price * num*(discount/100.0);
	}
	current_order->setItem(total_price);
	connect(current_order, &OrderItem::itemCleared, ui->reset, &QPushButton::click);
}
void UserInterface::on_takeaway_clicked()
{
	if (order_list.empty())
	{
		QMessageBox::warning(this, "提示", "请先点餐");
	}
	else
	{
		tky = new Takeaway();
		tky->show();
		connect(tky, &Takeaway::commit_orderItem, this, [&]() {
			on_order_clicked();
			saveOrderList();
			});
	}
}

void UserInterface::on_dinnerFood_clicked()
{
	if (order_list.empty())
	{
		QMessageBox::warning(this, "提示", "请先点餐");
	}
	else
	{
		dF = new dinnerFood();
		dF->show();
		connect(dF, &dinnerFood::commit_dinnerItem, this, [&]() {
			on_order_clicked();
			saveOrderList();
			});
	}
}