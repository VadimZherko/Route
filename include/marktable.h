#ifndef MARKTABLE_H
#define MARKTABLE_H

#include <QTableView>
#include <QStandardItemModel>
#include <QHeaderView>
#include <QFile>
#include <QMessageBox>
#include <QSortFilterProxyModel>

#include "../include/mark.h"
#include "../include/config.h"

class MarkTable : public QTableView
{

    Q_OBJECT
public:
    MarkTable();
    QPair<double, double> getCoords(int row);

private:
    QStandardItemModel* model;
    QSortFilterProxyModel* proxyModel;

public slots:
    void addRow(QString,int, double, double);
    /*void updateRow(int, int);*/
    void updateCoordsRow(int, double, double);
    void removeRow(int);
};

#endif // MARKTABLE_H
