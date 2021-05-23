#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileSystemModel>
#include <QList>


#include "entry.h"

class FilesDataModel;
class QItemSelection;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
private slots:
    void expanded();

    void on_selectionChangedSlot(const QItemSelection &selected, const QItemSelection &deselected);

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:

    QList<Entry> (*computeDataForModel)(const QString &path);
    static double computeDirFilesSize(const QString &path);
    static double computeDirectorySize(const QString &path);
    static QList<Entry> computeFilesSize(const QString &path);
    static QList<Entry> computeExtensionsSize(const QString &path);

    Ui::MainWindow *ui;

    FilesDataModel* filesModel;
    QFileSystemModel* dirModel;
    QWidget* view;
};
#endif // MAINWINDOW_H
