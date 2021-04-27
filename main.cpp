#include "mainwindow.h"

#include <QApplication>

#include <QList>
#include <QString>
#include <QDir>
#include <QFileInfoList>

QList<std::pair<QString,double>> computeFilesSize(const QString &path)
{
    QList<std::pair<QString,double>> filesSizeList;

    if(!path.isEmpty())
    {
        QDir directory(path);

        if(!directory.exists())
            throw QString("Directory does not exist");

        QFileInfoList filesInfoList = directory.entryInfoList();

        double dirSize = QFileInfo(path).size();

        for (QFileInfo &curFile : filesInfoList)
        {
            filesSizeList.push_back(std::pair<QString,double> (curFile.fileName(),curFile.size()/dirSize));
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

        QFileInfoList filesInfoList = directory.entryInfoList(QDir::Filter::Files);

        QStringList dirList = directory.entryList(QDir::Filter::Dirs);

        for(QString &curDir : dirList)
        {
            filesInfoList += QDir(curDir).entryInfoList(QDir::Filter::Files);
            dirList += QDir(curDir).entryList(QDir::Filter::Dirs);
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
    MainWindow w;
    w.show();
    return a.exec();
}
