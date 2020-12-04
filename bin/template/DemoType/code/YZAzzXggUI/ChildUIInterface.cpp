#include "YZAzzXggUI.h"

#include <YZSoftBase/ChildUIInterface.h>

ChildUIInterface* CreateUIInterface()
{
	YZAzzXggUI* pNewUI = new YZAzzXggUI();
	return pNewUI;
}
