#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QItemSelectionModel>
#include <QAbstractItemView>
#include <QTableView>

#include "myview.h"
#include "piechart.h"
#include "barchart.h"
#include "filesdatamodel.h"
#include "computefilessizefunctions.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    computeDataForModel = computeFilesSize;

    currentDir = QDir::homePath();

    filesModel = new FilesDataModel(this, computeDataForModel(currentDir));
    pieChart = new PieChart(this);
    barChart = new BarChart(this);

    tableView = new QTableView(this);
    tableView->setModel(filesModel);

    ui->horizontalLayout_3->addWidget(tableView,2);
    ui->horizontalLayout_3->addWidget(barChart,2);
    ui->horizontalLayout_3->addWidget(pieChart,2);

    barChart->hide();
    barChart->setModel(filesModel);
    pieChart->hide();
    pieChart->setModel(filesModel);

    view = tableView;

    dirModel = new QFileSystemModel(this);
    dirModel->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs);
    dirModel->setRootPath(QDir::rootPath());

    ui->treeView->setModel(dirModel);
    ui->treeView->hideColumn(1);
    ui->treeView->hideColumn(2);
    ui->treeView->hideColumn(3);


    connect(ui->treeView,SIGNAL(expanded(const QModelIndex &)),this,SLOT(treeViewCollapsedOrExpanded()));
    connect(ui->treeView,SIGNAL(collapsed(const QModelIndex &)),this,SLOT(treeViewCollapsedOrExpanded()));

    connect(ui->comboBox_action,SIGNAL(currentIndexChanged(int)),this,SLOT(actionChanged(int)));
    connect(ui->comboBox_display,SIGNAL(currentIndexChanged(int)),this,SLOT(displayTypeChanged(int)));

    QItemSelectionModel *selectionModel = ui->treeView->selectionModel();

    connect(selectionModel, SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection &)),
            this, SLOT(on_selectionChangedSlot(const QItemSelection &, const QItemSelection &)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::treeViewCollapsedOrExpanded()
{
    ui->treeView->resizeColumnToContents(0);
}

void MainWindow::actionChanged(int action_id)
{
    switch(action_id)
    {
    case 0:
        computeDataForModel = computeFilesSize;
        break;
    case 1:
        computeDataForModel = computeExtensionsSize;
        break;
    default:
        return;
    }

    filesModel->updateModel(computeDataForModel(currentDir));
}

void MainWindow::displayTypeChanged(int display_id)
{
    view->hide();
    switch (display_id)
    {
    case 0:
        view = tableView;
        break;
    case 1:
        view = pieChart;
        break;
    case 2:
        view = barChart;
        break;
    }
    view->show();
}

void MainWindow::on_selectionChangedSlot(const QItemSelection &selected, const QItemSelection &deselected)
{
    Q_UNUSED(deselected);

    QModelIndexList indexs =  selected.indexes();

    if (indexs.count() >= 1) {
        QModelIndex ix =  indexs.constFirst();
        currentDir = dirModel->filePath(ix);
        this->statusBar()->showMessage("Выбранный путь : " + currentDir);
    }

    filesModel->updateModel(computeDataForModel(currentDir));
}
