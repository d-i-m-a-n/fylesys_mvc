#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileSystemModel>
#include <QList>

#include "entry.h"

class QTableView;
class QItemSelection;

class PieChart;
class BarChart;
class FilesDataModel;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
private slots:
    void treeViewCollapsedOrExpanded();

    void actionChanged(int action_id);

    void displayTypeChanged(int display_id);

    void on_selectionChangedSlot(const QItemSelection &selected, const QItemSelection &deselected);

signals:
    void updateModel(QList<Entry> model);

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:

    QList<Entry> (*computeDataForModel)(const QString &path);

    Ui::MainWindow *ui;

    FilesDataModel* filesModel;
    QFileSystemModel* dirModel;

    QString currentDir;

    QTableView* view;
    QTableView *tableView;
    PieChart *pieChart;
    BarChart *barChart;

};
#endif // MAINWINDOW_H
