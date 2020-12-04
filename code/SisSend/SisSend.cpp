#include "SisSend.h"

#include <QIcon>
#include <QCoreApplication>
#include <QProcess>


SisSend::SisSend(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	setWindowIcon(QIcon(QString("%1%2").arg(QCoreApplication::applicationDirPath()).arg("/logo.ico")));

	connect(ui.pushButton, &QPushButton::clicked, this, &SisSend::on_pushButton_clicked);
	connect(ui.pushButton_2, &QPushButton::clicked, this, &SisSend::on_pushButton_2_clicked);
}

void SisSend::on_pushButton_clicked()
{
	QProcess *precess = new QProcess(this);
	precess->start(QString("SisRecevice.exe"));
}

void SisSend::on_pushButton_2_clicked()
{
	HWND hwnd = NULL;
	//do
	//{
	LPWSTR path = (LPWSTR)c_strTitle.utf16();  //path = L"SendMessage"
	hwnd = ::FindWindowW(NULL, path);
	//} while (hwnd == (HWND)effectiveWinId()); // 忽略自己

	if (::IsWindow(hwnd))
	{
		QString filename = ui.lineEdit->text();
		QByteArray data = filename.toUtf8();

		COPYDATASTRUCT copydata;
		copydata.dwData = CUSTOM_TYPE;  // 用户定义数据
		copydata.lpData = data.data();  //数据大小
		copydata.cbData = data.size();  // 指向数据的指针

		HWND sender = (HWND)effectiveWinId();

		::SendMessage(hwnd, WM_COPYDATA, reinterpret_cast<WPARAM>(sender), reinterpret_cast<LPARAM>(&copydata));
	}

}
