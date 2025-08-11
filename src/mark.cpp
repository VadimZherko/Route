#include "../include/mark.h"
#include <QGraphicsSceneMouseEvent>
#include <QMenu>

Mark::Mark(int id, double x, double y) : id(id), x(x), y(y), isLifterUpped(false)
{
    this->setPos(x, y);

    QrImage.load(":/new/prefix1/markIcon.png");

    this->setPixmap(QrImage);
    this->setFlag(QGraphicsItem::ItemIsSelectable);

    QString* text_id = new QString;
    text_id->setNum(id);
    textItem = new QGraphicsTextItem(*text_id,this);
    textItem->setDefaultTextColor(Qt::white);
    textItem->setPos(this->boundingRect().center().x() - textItem->boundingRect().width() / 2, this->boundingRect().bottom() - 5);

    menu.addAction("Move");
    menu.addAction("Lifter up/down");

    QMenu* degrees = menu.addMenu("Degree");
    degrees->addAction("0");
    degrees->addAction("1.57");
    degrees->addAction("3.14");
    degrees->addAction("-1.57");
}

int Mark::getId()
{
    return id;
}

void Mark::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    auto typeClick = menu.exec(event->screenPos());
    QGraphicsPixmapItem::contextMenuEvent(event);
    if(typeClick == nullptr) return;
    qDebug() << typeClick->toolTip(); //COM DEL

    if(typeClick->toolTip() == "Lifter up/down" && isLifterUpped == false)
    {
        emit markAction(typeClick->toolTip() + " 0", id, x, y);
        return;
    }
    else if(typeClick->toolTip() == "Lifter up/down" && isLifterUpped == true)
    {
        emit markAction(typeClick->toolTip() + " 1", id, x, y);
        return;
    }

    emit markAction(typeClick->toolTip(), id, x, y);
    }
