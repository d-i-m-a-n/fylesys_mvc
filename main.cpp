#include "mainwindow.h"

#include <QApplication>

#include <QList>
#include <QString>
#include <QDir>
#include <QFileInfoList>
#include <iostream>

#include "entry.h"

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
            itemSize = computeDirFilesSize(path + '/' + curItem.fileName());
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

        QStringList dirList = directory.entryList(QDir::Dirs | QDir::NoDotAndDotDot);

        for(QString &curDir : dirList)
        {
            filesInfoList += QDir(curDir).entryInfoList(QDir::Files);
            dirList += QDir(curDir).entryList(QDir::Dirs | QDir::NoDotAndDotDot);
        }

        double dirSize = QFileInfo(path).size();

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
                    filesInfoList.erase(iterFileInfo);
                }
                else
                    iterFileInfo++;
            }
            extensionsSizeList.last().m_sizePercent = extensionsSizeList.last().m_size / dirSize;
        }
    }

    return extensionsSizeList;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;


    w.show();
//    QDir dir("D:/QT_projects/lab3/tests");
//    QFileInfoList fileInfoList = dir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot);
//    for(auto &curDir : fileInfoList)
//    {
//        QList<std::pair<QString,double>> filesSize = computeFilesSize(curDir.absoluteFilePath());

//        std::cout << curDir.fileName().toStdString() << ":\n";
//        for(auto& curFile : filesSize)
//        {
//            std::cout << curFile.first.toStdString() << "  " << curFile.second << std::endl;
//        }
//        if(filesSize.isEmpty())
//            std::cout << "empty directory\n";
//    }

    return a.exec();
}
