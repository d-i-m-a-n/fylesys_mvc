#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QItemSelectionModel>
#include <QTableView>

#include "pychart.h"
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
    pieChart = new PieChart();
    barChart = new BarChart();

    tableView = new QTableView(this);
    tableView->setModel(filesModel);

    view = tableView;
    ui->horizontalLayout_3->addWidget(view,2);

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

    QItemSelection toggleSelection;
    QModelIndex topLeft;
    QString homePath = QDir::homePath();
    topLeft = dirModel->index(homePath);
    dirModel->setRootPath(homePath);

    toggleSelection.select(topLeft, topLeft);
    selectionModel->select(toggleSelection, QItemSelectionModel::Toggle);
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
    ui->treeView->update();
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
    update();
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
    ui->treeView->update();
}
