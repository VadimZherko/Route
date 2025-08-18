#include "../include/marktable.h"
#include <QString>

MarkTable::MarkTable()
{
    model = new QStandardItemModel(0,3);
    //this->setModel(model);

    this->horizontalHeader()->sortIndicatorOrder();

    proxyModel = new QSortFilterProxyModel(this);
    proxyModel->setSourceModel(model);
    proxyModel->setSortRole(Qt::UserRole);

    this->setModel(proxyModel);
    this->setSortingEnabled(false);
    this->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    this->verticalHeader()->setVisible(false);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    model->setHorizontalHeaderLabels({"id", "x", "y"});
    this->setColumnWidth(0, COLUMN_WIDTH_MARKTABLE);
    this->setColumnWidth(1, COLUMN_WIDTH_MARKTABLE);
    this->setColumnWidth(2, COLUMN_WIDTH_MARKTABLE);
}

void MarkTable::addRow(int id, double x, double y)
{
    auto row = model->rowCount();
    model->insertRow(row);

    //actionItem->setData(QVariant::fromValue(action), Qt::UserRole);

    auto idItem = new QStandardItem(QString::number(id));
    //idItem->setData(QVariant::fromValue(id), Qt::UserRole);

    auto xItem = new QStandardItem(QString::number(x));
    //xItem->setData(QVariant::fromValue(x), Qt::UserRole);

    auto yItem = new QStandardItem(QString::number(y));
    //yItem->setData(QVariant::fromValue(y), Qt::UserRole);

    model->setItem(row, 0, idItem);
    model->setItem(row, 1, xItem);
    model->setItem(row, 2, yItem);


    proxyModel->invalidate();
    proxyModel->sort(1, Qt::AscendingOrder);
}

/*void MarkTable::updateRow(int id, int angular)
{
    auto elem = model->findItems(QString::number(id));
    auto row = elem.first()->row();
    model->setItem(row, 3, new QStandardItem(QString::number(angular)));
}*/

void MarkTable::updateCoordsRow(int id,double x, double y)
{
    auto elem = model->findItems(QString::number(id));
    auto row = elem.first()->row();
    model->setItem(row, 2, new QStandardItem(QString::number(x)));
    model->setItem(row, 3, new QStandardItem(QString::number(y)));
}

void MarkTable::removeRow(int id)
{
    auto elem = model->findItems(QString::number(id),Qt::MatchExactly,0);
    auto row = elem.first()->row();
    model->removeRows(row, 0);
}

QPair<double, double> MarkTable::getCoords(int row)
{
    QPair<double, double> pair{model->item(row, 1)->text().toDouble(), model->item(row, 2)->text().toDouble()};
    return pair;
}
