#include "stdafx.h"
#include "ProjectManager.h"
#include "QDir"



const QString ProjectManager::PROJECT_PATH{QDir::currentPath() + "/Project" };

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

		if (fileInfo.fileName() == "." | fileInfo.fileName() == ".." | (!bIsDir && fileInfo.suffix() != QString("txt")))
		{
			i++;
			continue;
		}

		QStringList files;
		files << fileInfo.baseName() << "---" << "";
		QTreeWidgetItem *childItem = new QTreeWidgetItem(parent, files);

		if (bIsDir)
		{
			GetAllFilesFromPath(fileInfo.filePath(), childItem);
		}
		i++;
	}
}
