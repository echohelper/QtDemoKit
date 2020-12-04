#include "YZAzzXggUI.h"
#include "AzzXggManager.h"

#include <YZSoftBase/ISoftCache.h>
#include <YZSoftBase/IEventCenter.h>
#include <YZCommonCtrl/YZDropUtils.h>
#include <YZAzzXggData/YZAzzXggData.h>

	
	//文件内字段测试
	//void TestKeyAaa();
	//void TestKeyBbb(QString &str);
	//TestKeyCcc
	//TestKey222
	//TestKey--
	//TestKey222

YZAzzXggUI::YZAzzXggUI()
{
	GetEventCenter()->RegisterProjectEvent(this);
}

YZAzzXggUI::~YZAzzXggUI()
{

}

bool YZAzzXggUI::ExecuteCommand(const YZCommand &command)
{
	const QString &strCommandId = command.id;
	bool bChecked = command.isChecked();

	if (strCommandId == "XXXX")//XXXX
	{
		if (!m_pAzzXggManager)
		{
			m_pAzzXggManager = new AzzXggManager(command);
		}
		GetSoftCache()->GetMainContainer()->addDropWidget(YZDropUtils::CenterDropArea, m_pAzzXggManager);
		m_pAzzXggManager->initData();

		return true;
	}

	return false;
}

void YZAzzXggUI::OpenProject()
{
	YZAzzXggDataPtr()->clear();
}

void YZAzzXggUI::CloseProject()
{
	GetSoftCache()->GetMainContainer()->deleteDropWidget(m_pAzzXggManager);
	m_pAzzXggManager = nullptr;
}

void YZAzzXggUI::OpenModel()
{

}

void YZAzzXggUI::CloseModel()
{

}

void YZAzzXggUI::SaveSetting()
{

}

void YZAzzXggUI::ClickSingleEntity(const QString &strEntityGuid)
{

}
