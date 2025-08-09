#include "../include/actiontable.h"

ActionTable::ActionTable()
{
    model = new QStandardItemModel(0,1);
    //this->setModel(model);

    //this->horizontalHeader()->sortIndicatorOrder();

    proxyModel = new QSortFilterProxyModel(this);
    proxyModel->setSourceModel(model);
    proxyModel->setSortRole(Qt::UserRole);

    this->setModel(proxyModel);
    this->setSortingEnabled(false);
    //this->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    //this->verticalHeader()->setVisible(false);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    model->setHorizontalHeaderLabels({"action"});
    this->setColumnWidth(0, MARKTABLE_SIZE);
}

/*void ActionTable::addRow(QString action, int id, double x, double y)
{
    auto row = model->rowCount();
    model->insertRow(row);

    action = "Nothing";
    auto actionItem = new QStandardItem(action);
    //actionItem->setData(QVariant::fromValue(action), Qt::UserRole);

    auto idItem = new QStandardItem(QString::number(id));
    //idItem->setData(QVariant::fromValue(id), Qt::UserRole);

    auto xItem = new QStandardItem(QString::number(x));
    //xItem->setData(QVariant::fromValue(x), Qt::UserRole);

    auto yItem = new QStandardItem(QString::number(y));
    //yItem->setData(QVariant::fromValue(y), Qt::UserRole);

    model->setItem(row, 0, actionItem);
    model->setItem(row, 1, idItem);
    model->setItem(row, 2, xItem);
    model->setItem(row, 3, yItem);


    proxyModel->invalidate();
    proxyModel->sort(1, Qt::AscendingOrder);
}*/

/*void MarkTable::updateRow(int id, int angular)
{
    auto elem = model->findItems(QString::number(id));
    auto row = elem.first()->row();
    model->setItem(row, 3, new QStandardItem(QString::number(angular)));
}*/

void ActionTable::updateCoordsRow(int id,double x, double y)
{
    auto elem = model->findItems(QString::number(id));
    auto row = elem.first()->row();
    model->setItem(row, 2, new QStandardItem(QString::number(x)));
    model->setItem(row, 3, new QStandardItem(QString::number(y)));
}

void ActionTable::removeRow(int id)
{
    auto elem = model->findItems(QString::number(id),Qt::MatchExactly,1);
    auto row = elem.first()->row();
    model->removeRows(row, 1);
}

QPair<double, double> ActionTable::getCoords(int row)
{
    QPair<double, double> pair{model->item(row, 2)->text().toDouble(), model->item(row, 3)->text().toDouble()};
    return pair;
}
