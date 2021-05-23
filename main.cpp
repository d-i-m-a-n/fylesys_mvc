#include "mainwindow.h"

#include <QApplication>

#include <QList>
#include <QString>
#include <QDir>
#include <QFileInfoList>
#include <iostream>

#include "entry.h"


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
