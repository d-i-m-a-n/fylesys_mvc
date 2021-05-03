#include "mainwindow.h"

#include <QApplication>

#include <QList>
#include <QString>
#include <QDir>
#include <QFileInfoList>
#include <iostream>

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

QList<std::pair<QString,double>> computeFilesSize(const QString &path)
{
    QList<std::pair<QString,double>> filesSizeList;

    if(!path.isEmpty())
    {
        QDir directory(path);

        if(!directory.exists())
            throw QString("Directory does not exist");

        QFileInfoList filesInfoList = directory.entryInfoList(QDir::AllEntries | QDir::NoDotAndDotDot);

        double dirSize = computeDirectorySize(path);

        for (QFileInfo &curItem : filesInfoList)
        {
            double itemSize;
            if(curItem.isDir())
                itemSize = computeDirectorySize(path + '/' + curItem.fileName());
            else
                itemSize = (double)curItem.size();
            filesSizeList.push_back(std::pair<QString,double> (curItem.fileName(),itemSize/dirSize));
        }
    }

    return filesSizeList;
}

QList<std::pair<QString,double>> computeExtensionsSize(const QString &path)
{
    QList<std::pair<QString,double>> extensionsSizeList;

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
            extensionsSizeList.append(std::pair<QString,double>(curSuffix,0));

            iterFileInfo = filesInfoList.begin();

            while (iterFileInfo != filesInfoList.end())
            {
                if(iterFileInfo->suffix() == curSuffix)
                {
                    extensionsSizeList.last().second += iterFileInfo->size();
                    filesInfoList.erase(iterFileInfo);
                }
                else
                    iterFileInfo++;
            }
            extensionsSizeList.last().second /= dirSize;
        }
    }

    return extensionsSizeList;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QDir dir("D:/QT_projects/lab3/tests");
    QFileInfoList fileInfoList = dir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot);
    for(auto &curDir : fileInfoList)
    {
        QList<std::pair<QString,double>> filesSize = computeFilesSize(curDir.absoluteFilePath());

        std::cout << curDir.fileName().toStdString() << ":\n";
        for(auto& curFile : filesSize)
        {
            std::cout << curFile.first.toStdString() << "  " << curFile.second << std::endl;
        }
        if(filesSize.isEmpty())
            std::cout << "empty directory\n";
    }

    return a.exec();
}
