#pragma once

#include <YZCommonCtrl/QTableWidgetEx.h>

struct YZAzzXgg;

class AzzXggTable : public QTableWidgetEx
{
	Q_OBJECT

public:
	AzzXggTable(QWidget *parent);
	~AzzXggTable();

	void setData(const QList<YZAzzXgg> &azzxggs);
	void prependData(const YZAzzXgg &azzxgg);
	void updateData(const YZAzzXgg &azzxgg);

signals:
	void azzxggDetail(const QString &azzxggId);

private:
	void setRowData(int row, const YZAzzXgg &azzxgg);
	void onCellClicked(int row, int column);
};
