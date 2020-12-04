#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_SisSend.h"

class SisSend : public QMainWindow
{
	Q_OBJECT

public:
	SisSend(QWidget *parent = Q_NULLPTR);

private:
	Ui::SisSendClass ui;
};
