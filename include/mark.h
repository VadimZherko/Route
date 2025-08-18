#ifndef MARK_H
#define MARK_H

#include <QGraphicsRectItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
#include <QMenu>
#include <QItemSelection>
#include <QPainter>

class Mark : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
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
    QPixmap QrImage;
    QMenu menu;

    void contextMenuEvent(QGraphicsSceneContextMenuEvent*) override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*) override;
    QVariant itemChange(GraphicsItemChange, const QVariant&) override;
    QPainterPath shape() const override;

signals:
    void markAction(QString, int, double, double);
};

#endif // MARK_H
