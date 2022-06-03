#ifndef MODEL_H
#define MODEL_H

#include <QTime>
#include <QAbstractTableModel>
struct table{
    QString title;
    QTime begin_t;
    QTime end_t;
    bool check;
};
class Model: public QAbstractTableModel{
private:
    QVector<table> array;
public:
    Model(const QVector<table> & strings, QObject *parent = nullptr);
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    bool insertRows(int row, int count, const QModelIndex &parent);
    Qt::ItemFlags flags(const QModelIndex &index) const;
    void sort(int column, Qt::SortOrder order);
};

#endif // MODEL_H
