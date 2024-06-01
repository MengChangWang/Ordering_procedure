#include "Login.h"

Login::Login(QWidget *parent)
	: QWidget(parent)
	, ui(new Ui::LoginClass())
{
	ui->setupUi(this);
	managerInfo = make_shared<unordered_map<QString, QString>>();
	QFile file("manangerInfo.dat");
	file.open(QIODevice::ReadOnly);
	ReadManagerInfo(file, managerInfo);
	ui->Password->setMaxLength(10);
	ui->Password->setEchoMode(QLineEdit::PasswordEchoOnEdit);


	ui_register = new Register(nullptr, managerInfo);
	connect(ui->Registered, &QPushButton::clicked, this, [=]() {
		this->hide();
		ui_register->show(); });
	connect(ui_register, &Register::bacToLogin, this, [=]() {
		ui_register->close();
		this->show(); }
	);
	connect(ui->Login, &QPushButton::clicked, this, &Login::CheckInputInfo);
}

Login::~Login()
{
	delete ui;
}

void Login::ReadManagerInfo(QFile& file, shared_ptr<unordered_map<QString, QString>>& managerInfo) {
	if (file.isOpen()) {
		while (!file.atEnd())
		{
			QString key, value;
			QDataStream in(&file);
			in >> key;
			in >> value;
			(*managerInfo)[key] = value;
			qDebug() << key << value;
		}
		file.close();
	}
	else if (!file.exists()) {
		QMessageBox::warning(this, "Warning", "您还尚未注册管理员账号，请先注册管理员账号");
	}
	else
	{
		QMessageBox::warning(this, "Warning", "账户信息文件打开失败");
	}

}

void Login::CheckInputInfo()
{
	QString userName = ui->UserName->text();
	QString password = ui->Password->text();
	managerInfo = ui_register->managerInfo;
	
	QTimer*	m_timer = new QTimer(this);
	m_timer->setSingleShot(true);
	m_timer->setInterval(1000);
	

	if (userName.isEmpty() || password.isEmpty())
	{
		ui->display->setStyleSheet("color: red;" " font-size: 10px;");
		ui->display->setAlignment(Qt::AlignRight);
		ui->display->setText("用户名或密码不能为空");
		m_timer->start();
		connect(m_timer, &QTimer::timeout, this, [=]() {
			ui->display->clear(); });
	}
	else if ((*managerInfo)[userName] == password)
	{
		this->hide();
		RunManagerInterface(userName, password,true, managerInfo);
	}
	else
	{
		ui->UserName->clear();
		ui->Password->clear();
		ui->display->setStyleSheet("color: red;" " font-size: 10px;");
		ui->display->setAlignment(Qt::AlignRight);
		ui->display->setText("用户名或密码错误");
		m_timer->start();
		connect(m_timer, &QTimer::timeout, this, [=]() {
			ui->display->clear(); });
	}
}

void Login::RunManagerInterface(QString userName, QString password, bool isLogin, shared_ptr<unordered_map<QString, QString>>& managerInfo)
{
	ui_managerInterface = new ManagerInterface(nullptr,new Manager(userName, password, isLogin), managerInfo);
	ui_managerInterface->show();
}