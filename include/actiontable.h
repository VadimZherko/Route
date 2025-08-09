#ifndef ACTIONTABLE_H
#define ACTIONTABLE_H

#include <QTableView>
#include <QStandardItemModel>
#include <QSortFilterProxyModel>

#include "config.h"

class ActionTable : public QTableView
{

            Q_OBJECT

public:
    ActionTable();
    QPair<double, double> getCoords(int row);

private:
    QStandardItemModel* model;
    QSortFilterProxyModel* proxyModel;

public slots:
    //void addRow(QString,int, double, double);
    /*void updateRow(int, int);*/
    void updateCoordsRow(int, double, double);
    void removeRow(int);
};

#endif // ACTIONTABLE_H
