#pragma execution_character_set("utf-8")
#include "AzzXggManager.h"
#include "ui_AzzXggManager.h"
#include "AzzXggCreate.h"
#include "AzzXggDetail.h"
#include "YZAzzXggUtils.h"

#include <YZCommonCtrl/YZProgressBar.h>
#include <YZCommonCtrl/YZMessageBox.h>
#include <YZAzzXggData/YZAzzXggHeader.h>
#include <YZAzzXggData/YZAzzXggData.h>
#include <YZPrimaryData/YZPrimaryData.h>
#include <YZPublicFun/YZExcel.h>
#include <YZPublicFun/YZDateTime.h>
#include <YZPublicFun/YZFileOperate.h>
#include <YZPublicFun/YZUserInterface.h>
#include <YZPublicFun/YZGlobalSetting.h>
#include <YZPublicPro/YZPubPro.h>
#include <YZSoftBase/ISoftCache.h>

	
	//文件内字段测试
	//void TestKeyAaa();
	//void TestKeyBbb(QString &str);
	//TestKeyCcc
	//TestKey222
	//TestKey--
	//TestKey222

AzzXggManager::AzzXggManager(const YZCommand &command, QWidget *parent /*= Q_NULLPTR*/)
	: YZWidgetBase(parent)
	, m_command(command)
{
	ui = new Ui::AzzXggManager();
	ui->setupUi(this);

	auto handlerFun = std::bind(&AzzXggManager::azzxggView, this, std::placeholders::_1);
	ui->tableWidget->setDoubleClickHandler(handlerFun);

	ui->cbxCreator->setDisplayText(tr("创建人"));
	ui->cbxCreator->setFilterMode(true);

	ui->searchWidget->setPlaceholderText(tr("请输入名称关键字"));

	InitializeSplitter;

	//QTreeWidgetItem *itemMy = new QTreeWidgetItem(ui->treeWidget, QStringList(tr("我的")), YZAzzXggCondition::Mine);
	//QTreeWidgetItem *itemToDo = new QTreeWidgetItem(itemMy, QStringList(tr("待执行")), YZAzzXggCondition::Wait);
	//QTreeWidgetItem *itemDone = new QTreeWidgetItem(itemMy, QStringList(tr("已执行")), YZAzzXggCondition::Executed);
	//QTreeWidgetItem *itemCopy = new QTreeWidgetItem(itemMy, QStringList(tr("抄送我")), YZAzzXggCondition::Cc);
	//QTreeWidgetItem *itemCreate = new QTreeWidgetItem(itemMy, QStringList(tr("我创建")), YZAzzXggCondition::Create);
	//QTreeWidgetItem *itemDraft = new QTreeWidgetItem(ui->treeWidget, QStringList(tr("我的草稿箱")), YZAzzXggCondition::Draft);

	//if (m_command.bCustomApp)
	//{
	//	QTreeWidgetItem *itemAll = new QTreeWidgetItem(ui->treeWidget, QStringList(tr("全部")), YZAzzXggCondition::All);
	//}

	//itemMy->setExpanded(true);
	//ui->treeWidget->setCurrentItem(itemToDo);
	connect(ui->treeWidget, &QTreeWidget::currentItemChanged, this, &AzzXggManager::azzxggScopeChanged);

	connect(ui->btnAdd, &QToolButton::clicked, this, &AzzXggManager::createAzzXgg);
	connect(ui->btnExport, &QToolButton::clicked, this, &AzzXggManager::exportAzzXgg);
	connect(ui->btnDelete, &QToolButton::clicked, this, &AzzXggManager::deleteAzzXgg);
	connect(ui->btnRefresh, &QToolButton::clicked, this, &AzzXggManager::loadAzzXggData);

	connect(ui->searchWidget, &SearchUI::searchClicked, this, &AzzXggManager::loadAzzXggData);
	connect(ui->pageWidget, &QPageWidgetWithGo::currentRangeChanged, this, &AzzXggManager::rangeChanged);
	connect(ui->tableWidget, &AzzXggTable::countChanged, ui->pageWidget, &QPageWidgetWithGo::countChanged);
	connect(ui->tableWidget, &AzzXggTable::sortChanged, this, &AzzXggManager::loadAzzXggData);
	//connect(ui->tableWidget, &AzzXggTable::azzxggView, this, &AzzXggManager::azzxggView);
}

AzzXggManager::~AzzXggManager()
{
	//delete m_azzxggDetail;
	//delete m_templateManager;
	delete ui;
}

void AzzXggManager::initData()
{
	YZProgressBarAuto progressBar(NULL, RoundBar, ProgressRequest);

	loadAuthData();
	loadCbxData();
	loadAzzXggData();
}

void AzzXggManager::loadAuthData()
{
	//bool bCreate = YZAzzXggDataPtr()->canCreateAzzXgg(m_command.category);
	//bool bExport = YZAzzXggDataPtr()->canExportAzzXgg(m_command.category);
	//bool bDelete = YZAzzXggDataPtr()->canDeleteAzzXgg(m_command.category);
	//bool bCanOwn = YZAzzXggDataPtr()->canOwnAzzXgg(m_command.category);

	//ui->btnAdd->setVisible(bCreate);
	//ui->btnExport->setVisible(bExport);
	//ui->btnDelete->setVisible(bDelete || bCanOwn);
}

void AzzXggManager::loadCbxData()
{
	YZProgressBarAuto progressBar(NULL, RoundBar, ProgressRequest);

	////表单状态
	//ui->cbxStatus->clear();
	//ui->cbxStatus->addItem(tr("执行状态"), (int)YZAzzXggCondition::AllStatus);
	//ui->cbxStatus->addItem(tr("执行中"), (int)YZAzzXggCondition::Executing);
	//ui->cbxStatus->addItem(tr("已完成"), (int)YZAzzXggCondition::Completed);
	//ui->cbxStatus->addItem(tr("已关闭"), (int)YZAzzXggCondition::End);

	////延期状态
	//ui->cbxDelay->clear();
	//ui->cbxDelay->addItem(tr("延期状态"), (int)YZAzzXggCondition::DelayAll);
	//ui->cbxDelay->addItem(tr("未延期"), (int)YZAzzXggCondition::Delay0);
	//ui->cbxDelay->addItem(tr("延期1-7天"), (int)YZAzzXggCondition::Delay1_7);
	//ui->cbxDelay->addItem(tr("延期8-30天"), (int)YZAzzXggCondition::Delay8_30);
	//ui->cbxDelay->addItem(tr("延期30天以上"), (int)YZAzzXggCondition::Delay31_);

	////类型
	//if (m_command.bCustomApp)
	//{
	//	ui->cbxTemplate->clear();
	//	ui->cbxTemplate->addItem(tr("类型"));

	//	QList<YZAzzXggTemplate> azzxggTemplates;
	//	YZAzzXggDataPtr()->getModuleAzzXggTemplate(m_command.moduleId, azzxggTemplates);
	//	for (const YZAzzXggTemplate &azzxggTemplate : azzxggTemplates)
	//	{
	//		ui->cbxTemplate->addItem(azzxggTemplate.name, azzxggTemplate._id);
	//	}
	//}
	//else
	//{
	//	ui->cbxTemplate->hide();
	//}

	//创建人
	ui->cbxCreator->initData();
	ui->cbxCreator->setAllChecked(true);

	ui->searchWidget->resetData();
	ui->tableWidget->resetSort();
}

void AzzXggManager::loadAzzXggData()
{
	//YZProgressBarAuto progressBar(NULL, RoundBar, ProgressRequest);

	//YZAzzXggCondition condition;
	//getSearchCondition(condition);

	//int count(0);
	//YZAzzXggDataPtr()->getAzzXggRangeCount(condition, count);
	//ui->pageWidget->setTotalItemCount(count);
}

void AzzXggManager::getSearchCondition(YZAzzXggCondition &condition)
{
	ui->searchWidget->getQueryCondition(condition);

	//condition.azzxggScope = (YZAzzXggCondition::AzzXggScope)getCurrentAzzXggScope();
	//condition.azzxggStatus = (YZAzzXggCondition::AzzXggStatus)ui->cbxStatus->currentData().toInt();
	//condition.azzxggDelay = (YZAzzXggCondition::AzzXggDelay)ui->cbxDelay->currentData().toInt();
	//condition.templateId = ui->cbxTemplate->currentData().toString();
	//condition.category = m_command.category;

	//condition.bAllCreator = ui->cbxCreator->isCheckedAll();
	//if (!condition.bAllCreator)
	//{
	//	condition.creators = ui->cbxCreator->getSelectUserIds();
	//}

	//condition.sortQuery = ui->tableWidget->getSortQueryString();
}

void AzzXggManager::azzxggScopeChanged()
{
	//重置搜索条件
	//YZPub::setComboBoxCurrentData(ui->cbxStatus, (int)YZAzzXggCondition::AllStatus);
	//YZPub::setComboBoxCurrentData(ui->cbxDelay, (int)YZAzzXggCondition::DelayAll);
	//ui->cbxCreator->setAllChecked(true);
	//ui->searchWidget->resetData();

	//int taskScope = getCurrentAzzXggScope();
	//bool bSortByCreate = (taskScope == (int)YZAzzXggCondition::Create);//我创建默认按创建
	//ui->tableWidget->setSortByCreate(bSortByCreate);
	//ui->tableWidget->resetSort();
	//ui->tableWidget->setColumnVisible(taskScope);

	loadAzzXggData();
}

int AzzXggManager::getCurrentAzzXggScope()
{
	if (QTreeWidgetItem *treeItem = ui->treeWidget->currentItem())
	{
		return treeItem->type();
	}

	//return (int)YZAzzXggCondition::Mine;
	return 0;
}

void AzzXggManager::setCurrentAzzXggScope(int type)
{
	QTreeWidgetItemIterator iter(ui->treeWidget);
	while (*iter)
	{
		QTreeWidgetItem *item = *iter;

		if (item->type() == type)
		{
			ui->treeWidget->setCurrentItem(item);
			break;
		}

		++iter;
	}
}

void AzzXggManager::rangeChanged(int skip, int limit)
{
	YZProgressBarAuto progressBar(NULL, RoundBar, ProgressRequest);

	//YZAzzXggCondition condition;
	//getSearchCondition(condition);

	//QList<YZAzzXgg> azzxggs;
	//YZAzzXggDataPtr()->getAzzXggRangeData(condition, skip, limit, azzxggs);
	//ui->tableWidget->setData(azzxggs);
}

void AzzXggManager::createAzzXgg()
{
	//if (!m_templateManager)
	//{
	//	m_templateManager = new AzzXggTemplateManager(m_command);
	//	connect(m_templateManager, &AzzXggTemplateManager::azzxggChanged, this, &AzzXggManager::azzxggChanged);
	//}

	//m_templateManager->activateWindow();
	//m_templateManager->raise();
	//m_templateManager->show();
	//m_templateManager->initData();
}

void AzzXggManager::exportAzzXgg()
{
	//QStringList azzxggIds = ui->tableWidget->getCheckedIds();
	//if (azzxggIds.isEmpty())
	//{
	//	YZMessageBox::information(tr("请先选择表单"));
	//	return;
	//}

	//YZAzzXggUtils::exportAzzXggs(azzxggIds);
}

void AzzXggManager::azzxggChanged()
{
	loadAzzXggData();
}

void AzzXggManager::deleteAzzXgg()
{
	//QStringList azzxggIds = ui->tableWidget->getCheckedIds();
	//if (azzxggIds.isEmpty())
	//{
	//	YZMessageBox::information(tr("请先选择%1").arg(m_command.moduleName));
	//	return;
	//}

	//if (!YZMessageBox::question(tr("确定删除%1？").arg(m_command.moduleName)))
	//{
	//	return;
	//}

	//YZProgressBarAuto progressBar(NULL, RoundBar, ProgressDelete);
	//bool bDelete = YZAzzXggDataPtr()->canDeleteAzzXgg(m_command.category);
	////bool bCanOwn = YZAzzXggDataPtr()->canOwnAzzXgg(m_command.category);
	//QStringList forbidNames;
	//if (!bDelete)//仅有个人操作授权
	//{
	//	auto iter = std::remove_if(azzxggIds.begin(), azzxggIds.end(), [&](const QString &azzxggId)
	//	{
	//		YZAzzXgg azzxgg;
	//		YZAzzXggDataPtr()->getAzzXgg(azzxggId, azzxgg, true);
	//		if (azzxgg.createdBy != CurrentUserId)//不是自己创建的
	//		{
	//			forbidNames.append(azzxgg.name);
	//			return true;
	//		}

	//		return false;
	//	});
	//	azzxggIds.erase(iter, azzxggIds.end());
	//}

	//QStringList deleteIds;
	//QStringList failedNames;
	//for (const QString &azzxggId : azzxggIds)
	//{
	//	if (YZAzzXggDataPtr()->deleteAzzXgg(azzxggId))
	//	{
	//		deleteIds.append(azzxggId);
	//	}
	//	else
	//	{
	//		failedNames.append(YZAzzXggDataPtr()->getAzzXggName(azzxggId));
	//	}
	//}

	//progressBar.stopProgressBar();

	//if (!forbidNames.isEmpty())
	//{
	//	QStringList messages;
	//	messages.append(tr("以下%1无删除权限：").arg(m_command.moduleName));
	//	messages.append(forbidNames.join("\n"));
	//	YZMessageBox::information(messages.join("\n"));
	//}
	//if (!failedNames.isEmpty())
	//{
	//	QStringList messages;
	//	messages.append(tr("以下%1删除失败：").arg(m_command.moduleName));
	//	messages.append(failedNames.join("\n"));
	//	YZMessageBox::information(messages.join("\n"));
	//}

	////ui->tableWidget->removeRowByIds(deleteIds);
	//loadAzzXggData();

	//if (m_azzxggDetail && m_azzxggDetail->isVisible())
	//{
	//	if (deleteIds.contains(m_azzxggDetail->getAzzXggId()))
	//	{
	//		m_azzxggDetail->hide();
	//	}
	//}
}

void AzzXggManager::azzxggView(const QString &azzxggId)
{
	//if (getCurrentAzzXggScope() == (int)YZAzzXggCondition::Draft)
	//{
	//	azzxggModify(azzxggId);
	//	return;
	//}

	//if (!m_azzxggDetail)
	//{
	//	m_azzxggDetail = new AzzXggDetail(m_command);
	//	connect(m_azzxggDetail, &AzzXggDetail::azzxggChanged, this, &AzzXggManager::azzxggChanged);
	//	connect(m_azzxggDetail, &AzzXggDetail::modifyAzzXgg, this, &AzzXggManager::azzxggModify);	
	//	connect(m_azzxggDetail, &AzzXggDetail::deleteAzzXgg, this, &AzzXggManager::azzxggDelete);
	//}

	//m_azzxggDetail->activateWindow();
	//m_azzxggDetail->raise();
	//m_azzxggDetail->show();
	//m_azzxggDetail->initData(azzxggId);;
}

void AzzXggManager::azzxggModify(const QString &azzxggId)
{
	//if (m_azzxggDetail && m_azzxggDetail->isVisible())
	//{
	//	if (m_azzxggDetail->getAzzXggId() == azzxggId)
	//	{
	//		m_azzxggDetail->hide();
	//	}
	//}

	//AzzXggCreate *create = new AzzXggCreate(m_command);
	//create->setWindowTitle(tr("修改%1").arg(m_command.moduleName));
	//connect(create, &AzzXggCreate::azzxggChanged, this, &AzzXggManager::azzxggChanged);
	//create->show();
	//create->initAzzXgg(azzxggId);
}

void AzzXggManager::azzxggDelete(const QString &azzxggId)
{
	//if (!YZMessageBox::question(tr("确定删除该XXXX？")))
	//{
	//	return;
	//}

	//YZProgressBarAuto progressBar(NULL, RoundBar, ProgressDelete);
	//if (!YZAzzXggDataPtr()->deleteAzzXgg(azzxggId))
	//{
	//	YZMessageBox::information(tr("删除失败"));
	//	return;
	//}

	//progressBar.stopProgressBar();

	////ui->tableWidget->removeRowById(azzxggId);
	//loadAzzXggData();

	//if (m_azzxggDetail && m_azzxggDetail->isVisible())
	//{
	//	if (m_azzxggDetail->getAzzXggId() == azzxggId)
	//	{
	//		m_azzxggDetail->hide();
	//	}
	//}
}