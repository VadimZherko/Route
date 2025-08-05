#include "../include/mark.h"
#include <QGraphicsSceneMouseEvent>
#include <QMenu>

Mark::Mark(int id, double x, double y)
{
    this->setPos(x, y);

    QrImage.load(":/new/prefix1/markIcon.png");

    this->setPixmap(QrImage);
    this->setFlag(QGraphicsItem::ItemIsSelectable);

    this->id = id;
    this->isLifterUpped = false;
    this->isArrowOn = false;

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

void Mark::addArrow()
{
    QGraphicsPixmapItem* arrow = new QGraphicsPixmapItem(this);
    QPixmap arrowImage(":/new/prefix1/arrow.png");
    arrow->setPixmap(arrowImage);
    arrow->show();
    arrow->setPos(this->boundingRect().topLeft().x() - 5, this->boundingRect().topLeft().y() - 5);
}

void Mark::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    auto typeClick = menu.exec(event->screenPos());
    QGraphicsPixmapItem::contextMenuEvent(event);
    if(typeClick == nullptr) return;

    if(typeClick->toolTip() == "1.57" || typeClick->toolTip() == "3.14"|| typeClick->toolTip() == "-1.57" && isArrowOn)
    {
        isArrowOn = true;
        addArrow();
    }
    else if(typeClick->toolTip() == "Lifter up/down")
    {
        if(isLifterUpped)
        {
            QrImage.load(":/new/prefix1/markIconLifterDown.png");
            this->setPixmap(QrImage);
            isLifterUpped = false;
        }
        else
        {
            QrImage.load(":/new/prefix1/markIconLifterUp.png");
            this->setPixmap(QrImage);
            isLifterUpped = true;
        }
    }
}
