#pragma execution_character_set("utf-8")
#include "FastCreator.h"
#include "ui_FastCreator.h"

#include <QIcon>
#include <QDir>
#include <QFile>
#include <QUrl>
#include <QTextStream>
#include <QDesktopServices>
#include <QTextBrowser>
#include <QMessageBox>
#include <QRegExp>

#define ProjectName "[ProjectName]"
#define FileKey		"[FileKey]"
#define GroupKey	"["
#define MinWidth	60



//////////////////////////////////////////////////////////////////////////

void replaceBusiness(const QString &src, const QString &dst, QString &content)
{
	content.replace(src, dst, Qt::CaseSensitive);
	content.replace(src.toUpper(), dst.toUpper(), Qt::CaseSensitive);
	content.replace(src.toLower(), dst.toLower(), Qt::CaseSensitive);
	//content.replace(upperFirstChar(src), upperFirstChar(dst), Qt::CaseSensitive);
}

//////////////////////////////////////////////////////////////////////////


void getDirFileInfoList(const QString &dirPath, QFileInfoList &fileInfos, QFileInfoList &folderInfos)
{
	QDir dir(dirPath);
	QFileInfoList fileInfosTmp = dir.entryInfoList(QDir::Files | QDir::Hidden/* | QDir::NoSymLinks*/);
	QFileInfoList folderInfosTmp = dir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot);

	fileInfos.append(fileInfosTmp);

	for (int i = 0; i != folderInfosTmp.size(); ++i)
	{
		const QFileInfo &fileInfo = folderInfosTmp.at(i);
		if (fileInfo.isSymLink()) {
			fileInfos.append(fileInfo);
			continue;
		}

		folderInfos.append(fileInfo);
		QString dirPath = fileInfo.absoluteFilePath();
		getDirFileInfoList(dirPath, fileInfos, folderInfos);
	}
}

void getCurrentSubDir(const QString &currentDir, QStringList &dirs)
{
	QFileInfo fileinfo(currentDir);
	if (!fileinfo.isDir())
		return;

	QDir filedir(currentDir);
	QFileInfoList fileinfos = filedir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot | QDir::NoSymLinks);
	for (auto &fileinfo : fileinfos)
		dirs.append(fileinfo.baseName());
}


FastCreator::FastCreator(QWidget *parent)
	: QWidget(parent)
{
	ui = new Ui::FastCreatorClass;
	ui->setupUi(this);
	setWindowIcon(QIcon(QString("%1/logo.ico").arg(QCoreApplication::applicationDirPath())));
	setMinimumSize(370, 120);
	
	_wit = new QWidget();
	ui->scrollArea->setWidget(_wit);

	QVBoxLayout *layout = new QVBoxLayout(_wit);
	layout->setContentsMargins(0, 0, 0, 0);
	_wit->setLayout(layout);

	connect(ui->btnGenerate, &QPushButton::clicked, this, &FastCreator::onGenerate);
	connect(ui->btnHelp, &QPushButton::clicked, this, &FastCreator::onHelp);
	connect(ui->comboBox, static_cast<void(QComboBox::*)(const QString &)>(&QComboBox::currentIndexChanged), 
		this, &FastCreator::onCurrentIndexChanged);

	QStringList dirs;
	getCurrentSubDir(QString("%1%2").arg(QCoreApplication::applicationDirPath()).arg("/template"), dirs);
	ui->comboBox->addItems(dirs);

	resize(500, 300);
}

void FastCreator::onGenerate()
{
	if (_curInfo.templateType.isEmpty()) {
		QMessageBox::information(this, "提示", QString("%1").arg("选择的模板类型无效"));
		return;
	}

	_curInfo.projectNameVal = ui->lineEdit->text();
	if (_curInfo.projectNameVal.isEmpty()) {
		QMessageBox::information(this, "提示", QString("%1").arg("请输入项目名"));
		return;
	}

	_curInfo.fileKeyValMap[_curInfo.projectNameKey] = _curInfo.projectNameVal;
	for (auto it = _ctrlGroupMap.begin(); it != _ctrlGroupMap.end(); ++it)
	{
		if (_curInfo.templateType != it.key())
			continue;
	
		auto &keyCtrlMap = it.value();
		for (auto itKc = keyCtrlMap.begin(); itKc != keyCtrlMap.end(); ++itKc)
			_curInfo.fileKeyValMap[itKc.key()] = itKc->lineEdit->text();
	}

	QString templatePath;
	QString resultPath;
	{
		templatePath = QString("%1%2%3").arg(QCoreApplication::applicationDirPath()).arg("/template/").arg(_curInfo.templateType);
		QFileInfo fileInfo(templatePath);
		templatePath = fileInfo.absoluteFilePath();
	}
	{
		resultPath = QString("%1%2%3").arg(QCoreApplication::applicationDirPath()).arg("/result/").arg(_curInfo.templateType);
		QFileInfo fileInfo(resultPath);
		resultPath = fileInfo.absoluteFilePath();
	}

	QString cfgFilePath = QString("%1%2%3%4").arg(QCoreApplication::applicationDirPath()).arg("/template/").arg(_curInfo.templateType).arg("/config.ini");
	QFileInfo fileInfo(cfgFilePath);
	_curInfo.configPath = fileInfo.absoluteFilePath();

	QFileInfoList fileInfos;
	QFileInfoList folderInfos;
	getDirFileInfoList(templatePath, fileInfos, folderInfos);

	QStringList filePaths;
	copyAndRenameFiles(templatePath, resultPath, fileInfos, filePaths);

	replaceFilesData(filePaths);

	QDesktopServices::openUrl(QUrl::fromUserInput(resultPath));
}

void FastCreator::onHelp()
{
	QTextBrowser *pTextBrowser = new QTextBrowser();
	pTextBrowser->setWindowTitle("帮助文档");
	pTextBrowser->setWindowIcon(QIcon(QString("%1/logo.ico").arg(QCoreApplication::applicationDirPath())));
	pTextBrowser->resize(600, 400);
	pTextBrowser->show();

	QString filepath = QString("%1%2").arg(QCoreApplication::applicationDirPath()).arg("/template/ReadMe.txt");
	QFileInfo fileinfo(filepath);
	if (!fileinfo.exists()) {
		QMessageBox::information(this, "提示", QString("文件不存在：%1").arg(filepath));
		return;
	}

	QStringList lineDatas;
	if (!readFileLines(filepath, lineDatas)) {
		QMessageBox::information(this, "提示", QString("读取文件失败：%1").arg(filepath));
		return;
	}

	int lines = lineDatas.size();
	for (int line = lines - 1; line >= 0; --line)
	{
		if (lineDatas[line].isEmpty())
			lineDatas.removeAt(line);
		else
			break;
	}

	pTextBrowser->setText(lineDatas.join('\n'));
}

void FastCreator::onCurrentIndexChanged(const QString & text)
{
	_lastTemplateType = _curInfo.templateType;

	_curInfo.clear();
	_curInfo.templateType = text;

	QString cfgFilePath = QString("%1%2%3%4").arg(QCoreApplication::applicationDirPath()).arg("/template/").arg(_curInfo.templateType).arg("/config.ini");
	QFileInfo fileInfo(cfgFilePath);
	_curInfo.configPath = fileInfo.absoluteFilePath();

	bool bRet = readConfigFile(_curInfo.configPath, _curInfo);
	if (!bRet) {
		QMessageBox::information(this, "提示", QString("%1%2").arg("读取配置文件失败：").arg(_curInfo.configPath));
		return;
	}

	_infoMap[_curInfo.templateType] = _curInfo;

	generateConfigUi(_curInfo);

	auto itFind = _infoMapCache.find(_curInfo.templateType);
	if (itFind != _infoMapCache.end())
		updateConfigUi(itFind.value());
	else
		_infoMapCache[_curInfo.templateType] = _curInfo;
}

void FastCreator::onTextEdited(const QString & text)
{
	//进行一次界面全部保存到缓冲区
	_infoMapCache[_curInfo.templateType].projectNameKey = ui->label->text();
	_infoMapCache[_curInfo.templateType].projectNameVal = ui->lineEdit->text();

	auto itFind = _ctrlGroupMap.find(_curInfo.templateType);
	if (itFind != _ctrlGroupMap.end())
	{
		for (auto it = itFind.value().begin(); it != itFind.value().end(); ++it)
		{
			QString val = it.value().lineEdit->text();
			_infoMapCache[_curInfo.templateType].fileKeyValMap[it.key()] = val;
		}
	}
}

void FastCreator::copyAndRenameFiles(const QString &src, const QString &dst, QFileInfoList &fileInfos, QStringList &filePaths)
{
	for (const QFileInfo &fileInfo : fileInfos)
	{
		QString filepath = fileInfo.absoluteFilePath();
		if (_curInfo.configPath == filepath)
			continue;

		QString filePathResult = QString(filepath).replace(src, dst, Qt::CaseInsensitive);

		replaceBusiness(_curInfo.projectNameKey, _curInfo.projectNameVal, filePathResult);

		QFileInfo fileInfoTmp(filePathResult);
		QString fileFolder = fileInfoTmp.absolutePath();
		QDir dir(fileFolder);
		if (!dir.exists())
			dir.mkpath(fileFolder);

		QFile::copy(filepath, filePathResult);
		filePaths.append(filePathResult);
	}
}

void FastCreator::replaceFilesData(const QStringList &filePaths)
{
	for (const QString &filePath : filePaths)
	{
		QString content;
		QFile fileRead(filePath);
		if (!fileRead.open(QIODevice::ReadOnly | QIODevice::Text))
			continue;

		QTextStream in(&fileRead);
		in.setCodec("UTF-8");
		content = in.readAll();
		fileRead.close();

		for (auto it = _curInfo.fileKeyValMap.begin(); it != _curInfo.fileKeyValMap.end(); ++it)
			replaceBusiness(it.key(), it.value(), content);

		QFile fileWrite(filePath);
		if (!fileWrite.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text))
			continue;

		QTextStream out(&fileWrite);
		out.setCodec("UTF-8");
		out.setGenerateByteOrderMark(true);
		out << content;
		out.flush();

		fileWrite.close();
	}
}

bool FastCreator::readConfigFile(const QString &filePath, Data::ModuleInfo &info)
{
	QStringList lineDatas;
	if (!readFileLines(filePath, lineDatas))
		return false;

	lineDatas.removeAll("");
	removeAnno(lineDatas);
	removeSpaces(lineDatas);
	lineDatas.removeAll("");

	parseConfig(lineDatas, info);

	return true;
}

void FastCreator::generateConfigUi(const Data::ModuleInfo & info)
{
	ui->label->setText(QString("%1:").arg(info.projectNameKey));
	ui->lineEdit->setText(QString("%1").arg(info.projectNameVal));
	ui->label->setMinimumWidth(MinWidth);

	for (auto it = info.fileKeyValMap.begin(); it != info.fileKeyValMap.end(); ++it)
		_wit->layout()->removeItem(_ctrlGroupMap[_lastTemplateType][it.key()].layout);
	_ctrlGroupMap.remove(_lastTemplateType);

	for (auto it = info.fileKeyValMap.begin(); it != info.fileKeyValMap.end(); ++it)
	{
		if (info.projectNameKey == it.key())
			continue;

		QHBoxLayout *hLayout = new QHBoxLayout(_wit);
		QLabel *label = new QLabel(QString("%1:").arg(it.key()));
		label->setMinimumWidth(MinWidth);
		label->setAlignment(Qt::AlignRight);
		QLineEdit *lineEdit = new QLineEdit(it.value());
		connect(lineEdit, &QLineEdit::textEdited, this, &FastCreator::onTextEdited);

		_ctrlGroupMap[info.templateType][it.key()];
		_ctrlGroupMap[info.templateType][it.key()].layout = hLayout;
		_ctrlGroupMap[info.templateType][it.key()].label = label;
		_ctrlGroupMap[info.templateType][it.key()].lineEdit = lineEdit;

		hLayout->addWidget(label);
		hLayout->addWidget(lineEdit);
		((QVBoxLayout*)_wit->layout())->addLayout(hLayout);
	}
	_wit->update();
}

void FastCreator::updateConfigUi(const Data::ModuleInfo & info)
{
	ui->label->setText(QString("%1:").arg(info.projectNameKey));
	ui->lineEdit->setText(QString("%1").arg(info.projectNameVal));

	auto itFind = _ctrlGroupMap.find(info.projectNameKey);
	if (itFind != _ctrlGroupMap.end())
	{
		for (auto it = info.fileKeyValMap.begin(); it != info.fileKeyValMap.end(); ++it)
		{
			_ctrlGroupMap[info.templateType][it.key()].label->setText(QString("%1:").arg(it.key()));
			_ctrlGroupMap[info.templateType][it.key()].lineEdit->setText(it.value());
		}
	}
}

bool FastCreator::readFileLines(const QString &filePath, QStringList &lineDatas)
{
	QFile file(filePath);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
		return false;

	QTextStream in(&file);
	in.setCodec("UTF-8");
	QString line = in.readLine();
	while (!line.isNull()) {
		lineDatas.append(line);
		line = in.readLine();
	}
	file.close();

	return true;
}

void FastCreator::parseConfig(const QStringList & strs, Data::ModuleInfo & info)
{
	bool bDst, bCon;//用于行为控制

	bDst = false;
	bCon = true;
	//>parse project name key
	for (const auto &lineData : strs)
	{
		if (ProjectName == lineData) {
			bDst = true;
			continue;
		}

		if (bDst && GroupKey == QString(lineData[0]))
			break;

		if (bDst) {
			QStringList datas = lineData.split("=");
			int iSize = datas.size();
			if (1 == iSize)//有key，无val
				info.projectNameKey = datas.front();
			else if (2 == iSize) {//有key，有val
				info.projectNameKey = datas.front();
				auto val = datas.last();
				if (checkNaming(val) && checkString(val))
					info.projectNameVal = val;
			}
		}
	}

	if (!info.projectNameKey.isEmpty())
		info.fileKeyValMap[info.projectNameKey] = info.projectNameVal;

	bDst = false;
	bCon = true;
	//>parse file data key
	for (const auto &lineData : strs)
	{
		if (FileKey == lineData) {
			bDst = true;
			continue;
		}

		if (bDst && GroupKey == QString(lineData[0]))
			break;

		if (bDst) {
			QStringList datas = lineData.split("=");
			int iSize = datas.size();
			if (1 == iSize)
				info.fileKeyValMap[datas.front()] = "";
			else if (2 == iSize) {
				auto val = datas.last();
				if (checkNaming(val) && checkString(val))
					info.fileKeyValMap[datas.front()] = val;
			}
		}
	}
}

bool FastCreator::checkNaming(const QString & str)
{
	QRegExp reg("^[_|a-z|A-Z]");
	reg.indexIn(str);
	bool bRet = !(reg.capturedTexts().isEmpty());

	return bRet;
}

bool FastCreator::checkString(const QString & str)
{
	QRegExp reg("[_|a-z|A-Z|0-9]");
	int count = 0;
	int pos = 0;
	while ((pos = reg.indexIn(str, pos)) != -1) {
		++count;
		pos += reg.matchedLength();
	}

	return (count == str.size());
}

void FastCreator::removeSpaces(QString & str)
{
	str.replace(" ", "");
}

void FastCreator::removeSpaces(QStringList & strs)
{
	for (QString &str : strs)
		str.replace(" ", "");
}

void FastCreator::removeAnno(QString & str)
{
	//>带注释检查
	if (str.startsWith("//")
		|| str.startsWith("#")
		|| str.startsWith("[]")
		|| str.startsWith("=")
		){
		str = "";
		return;
	}

	//>去注释
	int index = str.indexOf("//");
	if (index >= 0)
		str = str.left(index);
	else if((index = str.indexOf("#")) >= 0)
		str = str.left(index);

	//>去注释后检查
	if (!str.contains("=") && !str.startsWith("[") && !str.endsWith("]")) {
		str = "";
		return;
	}

	if (str.contains("]=")) {
		str = "";
		return;
	}
}

void FastCreator::removeAnno(QStringList & strs)
{
	for (auto &str : strs)
		removeAnno(str);
}
