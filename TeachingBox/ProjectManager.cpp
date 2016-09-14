#include "stdafx.h"
#include "ProjectManager.h"
#include "QDir"
#include "TVariateManager.h"
#include <assert.h>


const QString ProjectManager::PROJECT_PATH{QDir::currentPath() + "/Project" };
const QString ProjectManager::FILE_SUFFIX{ "txt" };

void ProjectManager::GetAllFiles(QTreeWidgetItem* parent)
{
	GetAllFilesFromPath(PROJECT_PATH, parent);
}

void ProjectManager::GetAllFilesFromPath(const QString & path, QTreeWidgetItem* parent)
{
	QDir dir(path);

	/*若不存在文件，则返回*/
	if (!dir.exists())
	{
		return;
	}

	dir.setFilter(QDir::Dirs | QDir::Files);
	dir.setSorting(QDir::DirsFirst);


	/*读取文件信息*/
	QFileInfoList list = dir.entryInfoList();
	int i = 0;
	bool bIsDir; /*是否是文件夹*/
	while (i < list.size())
	{
		QFileInfo fileInfo = list.at(i);
		bIsDir = fileInfo.isDir();

		if (fileInfo.fileName() == "." | fileInfo.fileName() == ".." | (!bIsDir && fileInfo.suffix() != FILE_SUFFIX))
		{
			i++;
			continue;
		}

		QStringList files=GetStateTexts(fileInfo.baseName());
		QTreeWidgetItem *childItem = new QTreeWidgetItem(parent, files);

		if (bIsDir)
		{
			GetAllFilesFromPath(fileInfo.filePath(), childItem);
		}
		i++;
	}
}


/*删除给定项目文件夹并清除相应的数据库数据*/
void ProjectManager::DeleteProject(const QString& name)
{
	/*获取项目下所有文件作用域名*/
	QStringList scopeList{ name };
	QStringList files = GetProjectFiles(name);

	for (auto file: files)
	{
		scopeList.append(GetWholeFileName(file));
	}

	/*删除内存中的所有相关变量*/
	TVariateManager::GetInstance()->DeleteProjectVariates(scopeList);

	/*删除文件夹及内部所有文件*/
	QString projectPath = PROJECT_PATH + "/" + name;
	QDir dir(projectPath);
	dir.removeRecursively();
}

void ProjectManager::DeleteProgram(const QString& project, const QString& program)
{
	/*删除文件*/
	QString programPath = PROJECT_PATH + "/" + project+"/"+GetWholeFileName(program);
	QFile::remove(programPath);

	/*清除数据库中的数据*/
	TVariateManager::GetInstance()->DeleteProgramVariates(project + "." + program);
}

bool ProjectManager::ExistProject(const QString& project)
{
	QString path = PROJECT_PATH + "/" + project;
	QDir dir(path);

	return dir.exists();
}

bool ProjectManager::ExistProgram(const QString& project, const QString& program)
{
	QString path = PROJECT_PATH + "/" + project;
	QDir dir(path);

	return dir.exists(GetWholeFileName(program));
}

bool ProjectManager::CreateProject(const QString& project)
{
	QDir dir(PROJECT_PATH);
	return dir.mkdir(project);
}

bool ProjectManager::CreateProgram(const QString& project, const QString& program)
{
	QFile file(PROJECT_PATH + "/" + project + "/" + GetWholeFileName(program));
	if (file.open(QIODevice::WriteOnly))
	{
		file.write("EOF");
		file.close();
		return true;
	}

	return false;
}

QStringList ProjectManager::GetStateTexts(const QString& fileName)
{
	return QStringList{ fileName, "---" };
}

QStringList ProjectManager::GetProjectFiles(const QString& project)
{
	QStringList fileList;
	QString projectPath = PROJECT_PATH + "/" + project;
	QDir dir(projectPath);

	QFileInfoList list = dir.entryInfoList();
	for (auto fileInfo : list)
	{
		if (fileInfo.suffix() != FILE_SUFFIX)
		{
			continue;
		}
		fileList << project + "." + fileInfo.baseName();
	}

	return fileList;
}

QString ProjectManager::GetWholeFileName(const QString& fileName)
{
	return fileName + "." + FILE_SUFFIX;
}

QString ProjectManager::GetFileText(const QString& project, const QString& program)
{
	QString filePath = PROJECT_PATH + "/" + project + "/" + GetWholeFileName(program);
	QFile file(filePath);

	QString result;
	if (file.open(QFile::ReadOnly))
	{
		QTextStream fileIn(&file);
		fileIn.setCodec("UTF-8");
		fileIn.seek(0);
		result = fileIn.readAll();
		file.close();
	}

	return result;
}

ProjectManager::FILE_MAP ProjectManager::GetFileMap()
{
	FILE_MAP result;
	QDir dir(PROJECT_PATH);

	/*若不存在文件，则返回*/
	if (!dir.exists())
	{
		return result;
	}

	dir.setFilter(QDir::Dirs | QDir::Files);
	dir.setSorting(QDir::DirsFirst);

	/*读取文件信息*/
	QFileInfoList list = dir.entryInfoList();

	for (int i = 0; i < list.size(); ++i)
	{
		QFileInfo projectInfo = list.at(i);

		if (projectInfo.fileName() == "." || projectInfo.fileName() == ".." || !projectInfo.isDir())
		{
			continue;
		}

		QDir projectDir(projectInfo.filePath());
		projectDir.setFilter(QDir::Dirs | QDir::Files);
		projectDir.setSorting(QDir::DirsFirst);
		auto fileInfoList = projectDir.entryInfoList();

		QVector<QString> fileNameList;
		for (int j = 0; j < fileInfoList.size();++j)
		{
			if (fileInfoList.at(j).fileName() == "." || fileInfoList.at(j).fileName() == ".." || fileInfoList.at(j).isDir())
			{
				continue;
			}

			fileNameList.append(projectInfo.baseName()+"."+fileInfoList.at(j).baseName());
		}
		result[projectInfo.baseName()] = fileNameList;
	}
	
	return result;
}

bool ProjectManager::SaveFile(const QString& program, const QString& text)
{
	auto names = program.split(".");
	assert(names.size() == 2);
	QString project = names.at(0);
	QString fileName = names.at(1);

	QString filePath = PROJECT_PATH + "/" + project + "/" + GetWholeFileName(fileName);
	QFile file(filePath);

	if (file.open(QFile::WriteOnly))
	{
		QTextStream fileOut(&file);
		fileOut.setCodec("UTF-8");
		fileOut.seek(0);
		fileOut << text;
		file.close();

		return true;
	}

	return false;
}

