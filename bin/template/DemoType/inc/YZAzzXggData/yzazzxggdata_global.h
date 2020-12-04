#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(YZAZZXGGDATA_LIB)
#  define YZAZZXGGDATA_EXPORT Q_DECL_EXPORT
# else
#  define YZAZZXGGDATA_EXPORT Q_DECL_IMPORT
# endif
#else
# define YZAZZXGGDATA_EXPORT
#endif

	//文件内字段测试
	//void TestKeyAaa();
	//void TestKeyBbb(QString &str);
	//TestKeyCcc
	//TestKey222
	//TestKey--
	//TestKey222
