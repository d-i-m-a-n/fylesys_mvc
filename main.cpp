#include "mainwindow.h"

#include <QApplication>

#include <QList>
#include <QString>
#include <QDir>
#include <QFileInfoList>

QList<std::pair<QString,double>> computeFilesSize(const QString &path)
{
    QList<std::pair<QString,double>> filesSize;

    if(!path.isEmpty())
    {
        QDir directory(path);

        if(!directory.exists())
            throw QString("Directory does not exists");

        QFileInfoList filesInfo = directory.entryInfoList();

        double dirSize = QFileInfo(path).size();

        for (QFileInfo &curFile : filesInfo)
        {
            filesSize.push_back(std::pair<QString,double> (curFile.fileName(),curFile.size()/dirSize));
        }

    }

    return filesSize;
}


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
