#pragma once

#include <QtWidgets/QWidget>
#include <QFileInfoList>
#include <QMap>
#include <QLabel>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>

namespace Ui { class FastCreatorClass; }

namespace Data
{
	struct ModuleInfo
	{
		QString projectNameKey;	//<项目名称的key
		QString projectNameVal;	//<项目名称
		QString templateType;	//<模板类型
		QString configPath;		//<配置文件路径

		QMap<QString, QString> fileKeyValMap;	//<文件内字段(key，value)，项目名key也被添加


		void clear()
		{
			projectNameKey.clear();
			projectNameVal.clear();
			templateType.clear();
			configPath.clear();
			fileKeyValMap.clear();
		}
	};

	struct CtrlGroup
	{
		QHBoxLayout *layout = nullptr;
		QLabel *label = nullptr;
		QLineEdit *lineEdit = nullptr;


		CtrlGroup() { }
		~CtrlGroup() { clear(); }

		void clear()
		{
			auto DeletePtr = [](QWidget *wit) 
			{
				if (wit){
					wit->disconnect();
					delete wit;
					wit = nullptr;
				}
			};

			DeletePtr(label);
			DeletePtr(lineEdit);
		}
	};
}


class FastCreator : public QWidget
{
	Q_OBJECT
public:
	FastCreator(QWidget *parent = Q_NULLPTR);



private:
	///>slots
	void onGenerate();
	void onHelp();
	void onCurrentIndexChanged(const QString &text);
	void onTextEdited(const QString &text);


	/*!
	* 替换路径、文件名，并完成拷贝
	*/
	void copyAndRenameFiles(const QString &src, const QString &dst, QFileInfoList &fileInfos, QStringList &filePaths);

	/*!
	* 对文件内容进行替换
	*/
	void replaceFilesData(const QStringList &filePaths);

	/*!
	* 解析config.ini配置文件
	*/
	bool readConfigFile(const QString &filePath, Data::ModuleInfo &info);

	/*!
	* 依据配置文件动态生成配置的编辑界面
	*/
	void generateConfigUi(const Data::ModuleInfo &info);

	/*!
	* 使用_infoMapCache的操作缓冲，进行更新界面数据
	*/
	void updateConfigUi(const Data::ModuleInfo &info);


	///>helper
	bool readFileLines(const QString &filePath, QStringList &lineDatas);//按行读取文件所有行
	void parseConfig(const QStringList &strs, Data::ModuleInfo &info);
	bool checkNaming(const QString &str);//<验证值是否符合变量命名
	bool checkString(const QString &str);//<验证字符是否符合变量命名
	void removeSpaces(QString &str);//移除空格
	void removeSpaces(QStringList &strs);//移除空格
	void removeAnno(QString &str);//移除注释
	void removeAnno(QStringList &strs);//移除注释


private:
	Ui::FastCreatorClass *ui = nullptr;

	QString _lastTemplateType;//上一次模板类型
	Data::ModuleInfo _curInfo;//当前模板类型的配置信息
	QMap<QString, Data::ModuleInfo> _infoMap;//(TemplateType, ModuleInfo)
	QMap<QString, Data::ModuleInfo> _infoMapCache;//(TemplateType, ModuleInfo)

	QWidget *_wit = nullptr;
	QMap<QString, QMap<QString, Data::CtrlGroup>> _ctrlGroupMap;//(TemplateType, (fileKey, CtrlGroup))
};
