#pragma execution_character_set("utf-8")
#include "AzzXggTable.h"
#include "YZAzzXggUtils.h"

#include <YZAzzXggData/YZAzzXggData.h>
#include <YZPublicFun/YZNewItem.h>
#include <YZPublicFun/YZGlobalSetting.h>
#include <YZPublicPro/YZPubUser.h>

enum STCol
{
	CheckBox = 0,
	Number = 1,
	Name = 2,
	Operator = 3,
	UpdatedAt = 4,
	Detail = 5,
	Empty = 6,
};

AzzXggTable::AzzXggTable(QWidget *parent)
	: QTableWidgetEx(parent)
{
	QList<std::tuple<int, QString, int>> columns
	{
		std::make_tuple(STCol::CheckBox, "", YZPub::Column_Width_Check),
		std::make_tuple(STCol::Number, tr("序号"), YZPub::Column_Width_Number),
		std::make_tuple(STCol::Name, tr("姓名"), 160),
		std::make_tuple(STCol::Operator, tr("操作人"), YZPub::Column_Width_User),
		std::make_tuple(STCol::UpdatedAt, tr("更新时间"), YZPub::Column_Width_Time),
		std::make_tuple(STCol::Detail, tr("详情"), YZPub::Column_Width_Operate),
		std::make_tuple(STCol::Empty, "", YZPub::Column_Width_Empty)
	};

	setColumns(columns);
	setNumberColumn(STCol::Number);

	connect(this, &QTableWidget::cellClicked, this, &AzzXggTable::onCellClicked);
}

AzzXggTable::~AzzXggTable()
{
}

void AzzXggTable::setData(const QList<YZAzzXgg> &azzxggs)
{
	clearContents();
	setRowCount(azzxggs.size());

	int row(0);
	for (const YZAzzXgg &azzxgg : azzxggs)
	{
		setRowData(row++, azzxgg);
	}
}

void AzzXggTable::prependData(const YZAzzXgg &azzxgg)
{
	insertRow(0);
	setRowData(0, azzxgg);
}

void AzzXggTable::updateData(const YZAzzXgg &azzxgg)
{
	int count = rowCount();
	for (int row = 0; row < count; row++)
	{
		if (azzxgg._id == getRowId(row))
		{
			setRowData(row, azzxgg);
			break;
		}
	}
}

void AzzXggTable::setRowData(int row, const YZAzzXgg &azzxgg)
{
	setItem(row, STCol::CheckBox, YZPub::newTableItemCheck(azzxgg._id));
	setItem(row, STCol::Number, YZPub::newTableItem(QString::number(row + 1), true));
	setItem(row, STCol::Name, YZPub::newTableItem(azzxgg.name));

	setItem(row, STCol::UpdatedAt, YZPub::newTableItemDate(azzxgg.updatedAt));
	setItem(row, STCol::Operator, YZPub::newTableItem(YZPubPro::getUserNameByUserId(azzxgg.updatedBy), true));

	setCellWidget(row, STCol::Detail, YZPub::newTableCellIcon("detail"));
}

void AzzXggTable::onCellClicked(int row, int column)
{
	switch (column)
	{
	case STCol::Detail: emit azzxggDetail(getRowId(row)); break;
	default: break;
	}
}