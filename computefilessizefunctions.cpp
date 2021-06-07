#include "computefilessizefunctions.h"

#include <QDir>
#include <QFileInfoList>

QList<Entry> computeFilesSize(const QString &path)
{
    QList<Entry> filesSizeList;

    if(!path.isEmpty())
    {
        QDir directory(path);

        if(!directory.exists())
            throw QString("Directory does not exist");

        QFileInfoList filesInfoList = directory.entryInfoList(QDir::AllDirs | QDir::NoDotAndDotDot);

        double dirSize = computeDirectorySize(path);

        double itemSize;
        itemSize = computeDirFilesSize(path);
        filesSizeList.push_back(Entry("(Current directory)",itemSize/dirSize,itemSize));

        for (QFileInfo &curItem : filesInfoList)
        {
            itemSize = computeDirectorySize(path + '/' + curItem.fileName());
            filesSizeList.push_back(Entry(curItem.fileName(),itemSize/dirSize,itemSize));
        }
    }

    return filesSizeList;
}

QList<Entry> computeExtensionsSize(const QString &path)
{
    QList<Entry> extensionsSizeList;

    if(!path.isEmpty())
    {
        QDir directory(path);

        if(!directory.exists())
            throw QString("Directory does not exist");

        QFileInfoList filesInfoList = directory.entryInfoList(QDir::Files);

        QFileInfoList dirList = directory.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot);

        for(int i = 0; i < dirList.size(); i++)
        {
            filesInfoList += QDir(dirList[i].absoluteFilePath()).entryInfoList(QDir::Files);
            dirList += QDir(dirList[i].absoluteFilePath()).entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot);
        }

        double dirSize = computeDirectorySize(path);

        QFileInfoList::iterator iterFileInfo;
        QString curSuffix;

        while(!filesInfoList.isEmpty())
        {
            curSuffix = filesInfoList.front().suffix();
            extensionsSizeList.append(Entry(curSuffix,0,0));

            iterFileInfo = filesInfoList.begin();

            while (iterFileInfo != filesInfoList.end())
            {
                if(iterFileInfo->suffix() == curSuffix)
                {
                    extensionsSizeList.last().m_size += iterFileInfo->size();
                    iterFileInfo = filesInfoList.erase(iterFileInfo);
                }
                else
                    iterFileInfo++;
            }
            extensionsSizeList.last().m_sizePercent = extensionsSizeList.last().m_size / dirSize;
        }
    }

    return extensionsSizeList;
}

double computeDirFilesSize(const QString &path)
{
    double dirFilesSize = 0;
    QDir directory(path);

    QFileInfoList entryList = directory.entryInfoList(QDir::Files);

    for(auto &curItem : entryList)
    {
        if(curItem.isDir())
            dirFilesSize += computeDirFilesSize(path + '/' +curItem.fileName());
        else
            dirFilesSize += curItem.size();
    }

    return dirFilesSize;
}

double computeDirectorySize(const QString &path)
{
    double dirSize = 0;
    QDir directory(path);

    QFileInfoList entryList = directory.entryInfoList(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot);

    for(auto &curItem : entryList)
    {
        if(curItem.isDir())
            dirSize += computeDirectorySize(path + '/' +curItem.fileName());
        else
            dirSize += curItem.size();
    }

    return dirSize;
}

