#ifndef ACTIONTABLE_H
#define ACTIONTABLE_H

#include <QTableView>
#include <QStandardItemModel>
#include <QSortFilterProxyModel>
#include <QFile>
#include <QDialog>
#include <QMessageBox>

#include "config.h"

class ActionTable : public QTableView
{

            Q_OBJECT

public:
    ActionTable();

private:
    QStandardItemModel* model;
    QSortFilterProxyModel* proxyModel;

public slots:
    void addRow(QString, int, double, double);
    void saveInFile(QString);
    //void removeRow(int);
};

#endif // ACTIONTABLE_H
