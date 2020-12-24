#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_UuidHelper.h"

class UuidHelper : public QMainWindow
{
	Q_OBJECT

public:
	UuidHelper(QWidget *parent = Q_NULLPTR);

private:
	Ui::UuidHelperClass ui;
};
