#pragma once
#include "ui_SisSend.h"

#include <QtWidgets/QMainWindow>

#ifdef Q_OS_WIN
#pragma comment(lib, "user32.lib")
#include <qt_windows.h>
#endif

const ULONG_PTR CUSTOM_TYPE = 10000;
const QString c_strTitle = "SisRecevice";


class SisSend : public QMainWindow
{
	Q_OBJECT

public:
	SisSend(QWidget *parent = Q_NULLPTR);

private slots:
	void on_pushButton_clicked();

	void on_pushButton_2_clicked();

private:
	Ui::SisSendClass ui;
};
