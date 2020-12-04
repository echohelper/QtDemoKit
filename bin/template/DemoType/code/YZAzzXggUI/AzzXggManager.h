#pragma once

#include <QWidget>
#include <YZCommonCtrl/YZWidgetBase.h>
#include <YZSoftBase/YZCommand.h>

namespace Ui { class AzzXggManager; };

struct YZAzzXggCondition;
struct YZAzzXgg;

class AzzXggDetail;
class AzzXggTemplateLite;
class AzzXggTemplateManager;

	
	//文件内字段测试
	//void TestKeyAaa();
	//void TestKeyBbb(QString &str);
	//TestKeyCcc
	//TestKey222
	//TestKey--
	//TestKey222

//表单审批
class AzzXggManager : public YZWidgetBase
{
	Q_OBJECT

public:
	AzzXggManager(const YZCommand &command, QWidget *parent = Q_NULLPTR);
	~AzzXggManager();

	void initData();

	void azzxggView(const QString &azzxggId);

private:
	void rangeChanged(int skip, int limit);
	void getSearchCondition(YZAzzXggCondition &condition);
	void azzxggScopeChanged();
	void setCurrentAzzXggScope(int type);
	int getCurrentAzzXggScope();

	void loadAuthData();
	void loadCbxData();
	void loadAzzXggData();

	void createAzzXgg();
	void exportAzzXgg();
	void deleteAzzXgg();

	void azzxggModify(const QString &azzxggId);
	void azzxggDelete(const QString &azzxggId);

	void azzxggChanged();

private:
	Ui::AzzXggManager *ui;

	YZCommand m_command;

	//bool m_bCanExport = false;
	//AzzXggDetail *m_azzxggDetail = nullptr;

	//AzzXggTemplateLite *m_templateLite = nullptr;
	//AzzXggTemplateManager *m_templateManager = nullptr;
};
