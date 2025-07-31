#ifndef MARK_H
#define MARK_H

#include <QGraphicsRectItem>
#include <QGraphicsPixmapItem>

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

    QGraphicsTextItem* textItem;

    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;
};

#endif // MARK_H
