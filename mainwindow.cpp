#include "mainwindow.h"
#include "ui_mainwindow.h"


#include <QItemSelectionModel>
#include <QTableView>

#include "pychart.h"
#include "filesdatamodel.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    computeDataForModel = computeFilesSize;

    filesModel = new FilesDataModel(this, computeFilesSize("D:/QT_projects/lab3/tests"));

    ui->tableView->setModel(filesModel);


    QItemSelectionModel *selectionModel = ui->treeView->selectionModel();

    dirModel = new QFileSystemModel(this);
    dirModel->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs);
    dirModel->setRootPath(QDir::rootPath());

    ui->treeView->setModel(dirModel);
    ui->treeView->hideColumn(1);
    ui->treeView->hideColumn(2);
    ui->treeView->hideColumn(3);


    //connect(ui->treeView,SIGNAL(expanded()),this,SLOT(expanded()));

    connect(selectionModel, SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection &)),
            this, SLOT(on_selectionChangedSlot(const QItemSelection &, const QItemSelection &)));

    //selectionModel->select(toggleSelection, QItemSelectionModel::Toggle);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::expanded()
{

}

void MainWindow::on_selectionChangedSlot(const QItemSelection &selected, const QItemSelection &deselected)
{
    //Q_UNUSED(selected);
    Q_UNUSED(deselected);
    QModelIndex index = ui->treeView->selectionModel()->currentIndex();
    QModelIndexList indexs =  selected.indexes();
    QString filePath = "";

    // Размещаем инфо в statusbar относительно выделенного модельного индекса

    if (indexs.count() >= 1) {
        QModelIndex ix =  indexs.constFirst();
        filePath = dirModel->filePath(ix);
        this->statusBar()->showMessage("Выбранный путь : " + dirModel->filePath(indexs.constFirst()));
    }

    //TODO: !!!!!
    /*
    Тут простейшая обработка ширины первого столбца относительно длины названия папки.
    Это для удобства, что бы при выборе папки имя полностью отображалась в  первом столбце.
    Требуется доработка(переработка).
    */
//    int length = 200;
//    int dx = 30;

//    if (dirModel->fileName(index).length() * dx > length) {
//        length = length + dirModel->fileName(index).length() * dx;
//        qDebug() << "r = " << index.row() << "c = " << index.column() << dirModel->fileName(index) << dirModel->fileInfo(
//                     index).size();

//    }

    //ui->treeView->header()->resizeSection(index.column(), length + dirModel->fileName(index).length());
    //tableView->setRootIndex(fileModel->setRootPath(filePath));
}

double MainWindow::computeDirFilesSize(const QString &path)
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

double MainWindow::computeDirectorySize(const QString &path)
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

QList<Entry> MainWindow::computeFilesSize(const QString &path)
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

QList<Entry> MainWindow::computeExtensionsSize(const QString &path)
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
