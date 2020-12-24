#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_ToolTemplate.h"

class ToolTemplate : public QMainWindow
{
	Q_OBJECT

public:
	ToolTemplate(QWidget *parent = Q_NULLPTR);

private:
	Ui::ToolTemplateClass ui;
};
