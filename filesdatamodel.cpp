#include "filesdatamodel.h"

FilesDataModel::FilesDataModel(QObject *parent, QList<Entry> model) : QAbstractTableModel(parent)
{
    m_model = model;
}

int FilesDataModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_model.count();
}

int FilesDataModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return PERCENT + 1;
}

QVariant FilesDataModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole) {
        return QVariant();
    }
    if (orientation == Qt::Vertical) {
        return section;
    }

    switch (section) {
    case NAME:
        return trUtf8("Название");
    case SIZE:
        return trUtf8("Размер");
    case PERCENT:
        return trUtf8("В процентах");
    }
    return QVariant();
}

QVariant FilesDataModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || m_model.count() <= index.row() || (role != Qt::DisplayRole && role != Qt::EditRole))
    {
        return QVariant();
    }

    if (index.column() == 0) {
        return m_model[index.row()].m_name;
    }
    else if (index.column() == 1) {
        return m_model[index.row()].m_size;
    }
    else if (index.column() == 2) {
        return m_model[index.row()].m_sizePercent;
    }
}


