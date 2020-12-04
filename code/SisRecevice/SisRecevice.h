#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_SisRecevice.h"

class SisRecevice : public QMainWindow
{
	Q_OBJECT

public:
	SisRecevice(QWidget *parent = Q_NULLPTR);

private:
	Ui::SisReceviceClass ui;
};
