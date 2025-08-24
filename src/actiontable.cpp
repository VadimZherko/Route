#include "../include/actiontable.h"

ActionTable::ActionTable()
{
    model = new QStandardItemModel(0,1);

    proxyModel = new QSortFilterProxyModel(this);
    proxyModel->setSourceModel(model);
    proxyModel->setSortRole(Qt::UserRole);

    this->setModel(proxyModel);
    this->setSortingEnabled(false);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    model->setHorizontalHeaderLabels({"action"});
    this->setColumnWidth(0, MARKTABLE_SIZE);

    menu.addAction("Delete action");
}

void ActionTable::addRow(QString action, int id, double x, double y)
{
    //auto row = model->rowCount();
    //model->insertRow(row);

    QStandardItem* actionItem;
    if(action == "Move")
    {
        QString row;
        for(int i = model->rowCount() - 1; i >= 0; i--)
        {
            row = model->item(i,0)->text();
            if(row.startsWith('M'))
            {
                auto rowSplited = row.split(' ');
                emit moveSignal(rowSplited[1].toDouble(),rowSplited[2].toDouble(), x, y);
                break;
            }
        }

        QString actionTemp = "MOVE " + QString::number(x) + ' ' + QString::number(y) + ' ' + QString::number(id);
        actionItem = new QStandardItem(actionTemp);
    }
    else if(action == "Lifter up/down 1")
    {
        QString actionTemp = "LIFTER 1 " + QString::number(id);
        actionItem = new QStandardItem(actionTemp);
    }
    else if(action == "Lifter up/down 0")
    {
        QString actionTemp = "LIFTER 0 " + QString::number(id);
        actionItem = new QStandardItem(actionTemp);
    }
    else if(action == "0" || action == "1.57" || action == "-1.57" || action == "3.14" )
    {
        QString actionTemp = "ROTATE " + action + ' ' + QString::number(id);
        actionItem = new QStandardItem(actionTemp);
    }
    else
    {
        QString actionTemp = "ERROR";
        actionItem = new QStandardItem(actionTemp);
    }

    model->insertRow(model->rowCount(), actionItem);
}

void ActionTable::saveInFile(QString filePath)
{
    QFile file(filePath);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QMessageBox::warning(this, "Error", "Error opening file");
        return;
    }

    QTextStream out(&file);

    auto rowCount = model->rowCount();

    for(auto i = 0; i < rowCount; i++)
    {
        out << model->item(i)->text() << '\n';
    }

    file.close();
}

void ActionTable::contextMenuEvent(QContextMenuEvent* event)
{
    auto typeClick = menu.exec(event->globalPos());
    if(typeClick == nullptr) return;

    if(typeClick->toolTip() == "Delete action")
    {
        deleteAction();
        return;
    }
}

void ActionTable::deleteAction()
{
    QList<int> rows;
    for(auto i : this->selectedIndexes())
    {
        rows.append(i.row());
    }

    std::sort(rows.begin(),rows.end(),std::greater<int>());

    for(auto i = rows.begin(); i != rows.end(); i++)
    {
        if(!model->item(*i,0)->text().startsWith('M'))
        {
            model->removeRow(*i);
            continue;
        }

        for(auto y = *i; y < this->model->rowCount(); y++)
        {
            qDebug() << *i << ' ' << this->model->rowCount() << ' ' << y;
            auto row = model->item(y,0)->text();
            if(row.startsWith('M'))
            {
                qDebug() << model->item(*i,0)->text() << "||" << model->item(y,0)->text();
                auto rowSplited = model->item(*i,0)->text().split(' ');
                auto rowTempSplited = row.split(' ');
                emit delMoveSignal(rowSplited[1].toDouble(),rowSplited[2].toDouble(), rowTempSplited[1].toDouble(), rowTempSplited[2].toDouble());
            }
        }

        for(auto y = *i - 1; y >= 0; y--)
        {
            auto row = model->item(y,0)->text();
            if(row.startsWith('M'))
            {
                qDebug() << model->item(*i,0)->text() << "||" << model->item(y,0)->text();
                auto rowSplited = model->item(*i,0)->text().split(' ');
                auto rowTempSplited = row.split(' ');
                emit delMoveSignal(rowSplited[1].toDouble(),rowSplited[2].toDouble(), rowTempSplited[1].toDouble(), rowTempSplited[2].toDouble());
                model->removeRow(*i);
                break;
            }
        }

        model->removeRow(*i);
    }
}
