#include "../include/mark.h"
#include <QGraphicsSceneMouseEvent>
#include <QMenu>

Mark::Mark(int id, double x, double y) : id(id), x(x), y(y), isFirst(false)
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
    menu.addAction("Charge");
    //menu.addAction("Lifter up/down");

    QMenu* degrees = menu.addMenu("Degree");
    degrees->addAction("0");
    degrees->addAction("1.57");
    degrees->addAction("3.14");
    degrees->addAction("-1.57");

    QMenu* Lifters = menu.addMenu("Lifter");
    Lifters->addAction("Up");
    Lifters->addAction("Down");
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

    if(typeClick->toolTip() == "Down")
    {
        emit markAction(typeClick->toolTip(), id, x, y);
        return;
    }
    else if(typeClick->toolTip() == "Up")
    {
        emit markAction(typeClick->toolTip(), id, x, y);
        return;
    }

    emit markAction(typeClick->toolTip(), id, x, y);
}

QVariant Mark::itemChange(GraphicsItemChange change, const QVariant& value)
{
    if (change == QGraphicsItem::ItemSelectedChange)
    {
        bool isBeSelected = value.toBool();
        if (isBeSelected)
        {
            QrImage.load(":/new/prefix1/markIconSelected.png");
            setPixmap(QrImage);
        }
        else
        {
            QrImage.load(":/new/prefix1/markIcon.png");
            setPixmap(QrImage);
        }
    }
    return QGraphicsPixmapItem::itemChange(change, value);
}

void Mark::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(0, 0, pixmap());
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

QPainterPath Mark::shape() const
{
    QPainterPath path;
    path.addRect(boundingRect());
    return path;
}

void Mark::markIsFirst()
{
    if(isFirst == false)
    {
        qDebug() << "Первая";
        QrImage.load(":/new/prefix1/markIcon.png");
        this->setPixmap(QrImage);
        isFirst = true;
    }
}

void Mark::markIsNotFirst()
{
    if(isFirst == true)
    {
        qDebug() << "НЕПервая";
        QrImage.load(":/new/prefix1/markIcon.png");
        this->setPixmap(QrImage);
        isFirst = false;
    }
}
