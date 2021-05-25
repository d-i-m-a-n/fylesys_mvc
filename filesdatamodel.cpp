#include "filesdatamodel.h"
#include <cmath>

#include "computefilessizefunctions.h"

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
        return "Название";
    case SIZE:
        return "Размер";
    case PERCENT:
        return "В процентах";
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
        if(m_model[index.row()].m_size == 0)
            return 0;
        if(m_model[index.row()].m_sizePercent*100 > 0.01)
            return std::trunc(m_model[index.row()].m_sizePercent*10000)/100;
        return "<0,01";
    }
}

void FilesDataModel::updateModel(QList<Entry> model)
{
    m_model = model;
}
