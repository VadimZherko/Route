#ifndef MARK_H
#define MARK_H

#include <QGraphicsRectItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
#include <QMenu>

class Mark : public QGraphicsPixmapItem
{
public:
    Mark(int, double, double);
    void setId();
    int getId();

private:
    double x;
    double y;
    int id;
    bool isLifterUpped;
    bool isArrowOn;

    QGraphicsTextItem* textItem;
    QPixmap QrImage;
    QMenu menu;

    void addArrow();
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;
};

#endif // MARK_H
