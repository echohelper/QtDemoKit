#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_UuidHelper.h"

class UuidHelper : public QMainWindow
{
	Q_OBJECT

private:
	enum FormatType {
		WithoutBraces,
		InBraces,
		InParentheses,
		PureHexUpper,
		PureHexLower,
	};

public:
	UuidHelper(QWidget *parent = Q_NULLPTR);

	void initData();


private:
	void init();

	void generateGuid();
 	QString getGuid(FormatType type);

private slots:
	void onBtnCopy();
	void onBtnSave();
	void onBtnClear();
	void onBtnGenerate();

private:
	Ui::UuidHelperClass ui;
};
