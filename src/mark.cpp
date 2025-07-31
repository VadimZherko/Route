#include "../include/mark.h"
#include <QGraphicsSceneMouseEvent>
#include <QMenu>

Mark::Mark(int id, double x, double y)
{
    this->setPos(x, y);

    QPixmap QrImage(":/new/prefix1/markIconLifterUp.png");

    this->setPixmap(QrImage);
    this->setFlag(QGraphicsItem::ItemIsSelectable);

    this->id = id;
    this->isLifterUpped = false;

    QString* text_id = new QString;
    text_id->setNum(id);
    textItem = new QGraphicsTextItem(*text_id,this);
    textItem->setDefaultTextColor(Qt::white);
    textItem->setPos(this->boundingRect().center().x() - textItem->boundingRect().width() / 2, this->boundingRect().bottom() - 5);
}

int Mark::getId()
{
    return id;
}

void Mark::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    QMenu menu;

    menu.addAction("Move");
    menu.addAction("Lifter up/down");

    QMenu* degrees = menu.addMenu("Degree");
    degrees->addAction("1.571");
    degrees->addAction("3.142");
    degrees->addAction("4.712");

    menu.exec(event->screenPos());
}
