#ifndef FilesDataModel_H
#define FilesDataModel_H

#include <QAbstractTableModel>
#include <QList>

#include "entry.h"

class FilesDataModel : public QAbstractTableModel
{
public:
    FilesDataModel(QObject *parent, QList<Entry> model = QList<Entry>());

    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;


private:

    enum ColumnName {
    NAME,
    SIZE,
    PERCENT
    };


    QList<Entry> m_model;

};

#endif // FilesDataModel_H
