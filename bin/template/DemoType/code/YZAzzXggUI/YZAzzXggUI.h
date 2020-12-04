#pragma once

#include <YZSoftBase/IEventCenter.h>
#include <YZSoftBase/ChildUIInterface.h>

class AzzXggManager;

	
	//文件内字段测试
	//void TestKeyAaa();
	//void TestKeyBbb(QString &str);
	//TestKeyCcc
	//TestKey222
	//TestKey--
	//TestKey222

//XXXX
class YZAzzXggUI : public ChildUIInterface, public IProjectEvent
{
public:
	YZAzzXggUI();
	~YZAzzXggUI();

	bool ExecuteCommand(const YZCommand &command);

	void OpenProject();
	void CloseProject();
	void OpenModel();
	void CloseModel();
	void SaveSetting();

	void ClickSingleEntity(const QString &strEntityGuid);

private:
	AzzXggManager *m_pAzzXggManager = nullptr;
};
