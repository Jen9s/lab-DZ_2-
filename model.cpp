#include "model.h"
#include <QTime>
#include <QBrush>

Model::Model(const QVector<table> & strings, QObject*parent) :
    QAbstractTableModel(parent), array(strings) {}

int Model::rowCount(const QModelIndex & /*parent*/) const{
    return array.size();
}
int Model::columnCount(const QModelIndex & /*parent*/) const{
    return 3;
}
QVariant Model::data(const QModelIndex &index, int role) const{
    if(index.isValid() && index.row() < array.size() && index.column() == 0 && role == Qt::DisplayRole){
        return array.at(index.row()).title;
    }
    if(index.isValid() && index.row() < array.size() && index.column() == 1 && role == Qt::DisplayRole){
        return array.at(index.row()).begin_t;
    }
    if(index.isValid() && index.row() < array.size() && index.column() == 2 && role == Qt::DisplayRole){
        return array.at(index.row()).end_t;
    }
    if(index.isValid() && index.row() < array.size() && index.column() == 0 && role == Qt::CheckStateRole){
        return array.at(index.row()).check ? Qt::Checked : Qt::Unchecked;
    }
    if(index.isValid() && index.row() < array.size()
            && array.at(index.row()).check
            && role == Qt::BackgroundRole){
        return QColor(Qt::green);
    }
    return QVariant();
}
bool Model::setData(const QModelIndex &index, const QVariant &value, int role){
    if (role == Qt::EditRole) {
            if (index.isValid()){
                if(index.column() == 0){
            array[index.row()].title = value.toString();
                }
                if(index.column() == 1){
            array[index.row()].begin_t = value.toTime();
                }
                if(index.column() == 2){
            array[index.row()].end_t = value.toTime();
                }
            emit dataChanged(index, index);
            return true;
        }
    }
    if(role == Qt::CheckStateRole){
        if (index.isValid()){
            if(value == Qt::Checked){
        array[index.row()].check = true;
            }
            if(value == Qt::Unchecked){
        array[index.row()].check = false;
            }

        emit dataChanged(index, QAbstractTableModel::index(index.row(), index.column() + 2));
        return true;
    }
    }
    return false;
}

QVariant Model::headerData(int section, Qt::Orientation orientation, int role) const{
   if(role != Qt::DisplayRole) return QVariant();
   else if(section == 0 && orientation == Qt::Horizontal) return QString("Title");
   else if(section == 1 && orientation == Qt::Horizontal) return QString("Begin Time");
   else if(section == 2 && orientation == Qt::Horizontal) return QString("End Time");
}

bool Model::insertRows(int row, int count, const QModelIndex &/*parent*/){
    beginInsertRows(QModelIndex(), row, row + count - 1);
    int tmp = array.size();
    array.resize(array.size()+1);
        array[tmp].title = "";
        array[tmp].begin_t = QTime::currentTime();
        array[tmp].end_t = QTime::currentTime();
        array[tmp].check = false;
    endInsertRows();
    return true;
}
Qt::ItemFlags Model::flags(const QModelIndex &index) const{
    if(index.column() == 0) return Qt::ItemIsUserCheckable | Qt::ItemIsEditable | QAbstractTableModel::flags(index);
    return Qt::ItemIsEditable | QAbstractTableModel::flags(index);
}
void Model::sort(int column, Qt::SortOrder order){
    if(order == Qt::AscendingOrder){
        if(column == 0){
        std::sort(array.begin(), array.end(), [&](const table& lhs, const table& rhs){
            if(lhs.check != rhs.check)
                return lhs.check > rhs.check;
            return lhs.title > rhs.title;
        });
        }
        if(column == 1){
        std::sort(array.begin(), array.end(), [&](const table& lhs, const table& rhs){
            if(lhs.check != rhs.check)
                return lhs.check > rhs.check;
            return lhs.begin_t > rhs.begin_t;
        });
        }
        if(column == 2){
        std::sort(array.begin(), array.end(), [&](const table& lhs, const table& rhs){
            if(lhs.check != rhs.check)
                return lhs.check > rhs.check;
            return lhs.end_t > rhs.end_t;
        });
        }
    } else {
        if(column == 0){
        std::sort(array.begin(), array.end(), [&](const table& lhs, const table& rhs){
            if(lhs.check != rhs.check)
                return lhs.check > rhs.check;
            return lhs.title < rhs.title;
        });
        }
        if(column == 1){
        std::sort(array.begin(), array.end(), [&](const table& lhs, const table& rhs){
            if(lhs.check != rhs.check)
                return lhs.check > rhs.check;
            return lhs.begin_t < rhs.begin_t;
        });
        }
        if(column == 2){
        std::sort(array.begin(), array.end(), [&](const table& lhs, const table& rhs){
            if(lhs.check != rhs.check)
                return lhs.check > rhs.check;
            return lhs.end_t < rhs.end_t;
        });
        }
    }
    emit dataChanged(index(0, 0), index(array.size(), 3));
}
