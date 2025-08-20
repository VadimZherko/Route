#include "../include/scene.h"

Scene::Scene()
{
    parentWidget = new QWidget();
    this->setSceneRect(-GRID_SIZE * SCENE_X_COEF, -GRID_SIZE * SCENE_Y_COEF, GRID_SIZE * SCENE_WIDTH_COEF, GRID_SIZE * SCENE_HEIGHT_COEF);

    Mark* temp = new Mark(-100, -100, -100);
    marks.push_back(temp);
}

Scene::~Scene()
{
    delete parentWidget;
}

void Scene::drawBackground(QPainter* painter, const QRectF& rect)
{
    //QColor color(225,79,0,255);
    //QColor color(0,0,139,100);
    QColor color(169, 169, 169, 50);
    QPen pen(color,1);
    painter->setPen(pen);

    auto left = this->sceneRect().left();
    auto right = this->sceneRect().right();
    auto top = this->sceneRect().top();
    auto bottom = this->sceneRect().bottom();

    for(int y = top; y < bottom; y += GRID_SIZE) //Grid
    {
        painter->drawLine(QLineF(left, y, right, y));
        painter->drawLine(QLineF());
    }

    for(int x = left; x < right; x += GRID_SIZE) //Grid
    {
        painter->drawLine(QLineF(x, top, x, bottom));
    }

    pen.setWidthF(0.2);
    painter->setPen(pen);

    for(int y = top; y < bottom; y += MILLIMIMETER_GRID) //Grid
    {
        painter->drawLine(QLineF(left, y, right, y));
    }

    for(int x = left; x < right; x += MILLIMIMETER_GRID) //Grid
    {
        painter->drawLine(QLineF(x, top, x, bottom));
    }

    /*pen.setWidth(3);
    painter->setPen(pen);
    painter->drawLine(QLineF(0, top, 0, bottom));

    painter->drawLine(QLineF(left, 0, right, 0));

    color.setRgb(200,200,200,200);
    QPen pen_text(color);
    painter->setPen(pen_text);
    QFont font = painter->font();
    font.setPixelSize(FONT_SIZE);
    painter->setFont(font);

    int i =  left / GRID_SIZE;
    for(int x = left; x < right; x+= GRID_SIZE, i++) //Lines on axis X
    {
        if(i == 0) continue;

        painter->setPen(pen);
        painter->drawLine(QLineF(x, -3, x, 3));

        painter->setPen(pen_text);
        painter->drawText(QPointF(x, FONT_POSE_Y), QString::number(i));
    }

    i = -(bottom / GRID_SIZE);
    for(int y = bottom; y > top; y -= GRID_SIZE, i++) //Lines on axis Y
    {
        if(i == 0) continue;

        painter->setPen(pen);
        painter->drawLine(QLineF(-3, y, 3, y));

        painter->setPen(pen_text);
        painter->drawText(QPointF(FONT_POSE_X, y), QString::number(i));
    }

    painter->drawText(QPointF(FONT_POSE_X, FONT_POSE_Y), QString::number(0));*/

    //Удалить
    /*pen.setWidth(2);
    color.setRgb(255,255,255);
    pen.setColor(color);
    painter->setPen(pen);
    for(double i =  8.1; i > 3.2; i -= 1.2)
    {
        painter->drawLine(QLineF(toPixels(0.6,i).first,toPixels(0,i).second,toPixels(1.2, i).first,toPixels(1.2, i).second));
    }
    painter->drawLine(QLineF(0,0,100,0));*/
}

QPair<double, double> Scene::toCoords(double x, double y)
{
    double new_x = (x + CENTER_MARK) /  GRID_SIZE;
    double new_y = (-y - CENTER_MARK) / GRID_SIZE;
    return QPair<double,double>(new_x, new_y);
}

QPair<double, double> Scene::toPixels(double x, double y)
{
    double new_x = x * GRID_SIZE - CENTER_MARK;
    double new_y = -y * GRID_SIZE - CENTER_MARK;
    return QPair<double, double>(new_x, new_y);
}

Mark* Scene::addMark(double x, double y, int id)
{
    auto [newX, newY] = toPixels(x, y);

    checkSceneSize(newX, newY);
    Mark* new_mark = new Mark(id, newX, newY);
    this->addItem(new_mark);
    new_mark->setSelected(true);

    emit markAdded(id, x, y);
    emit setScrollHandDrag();

    QObject::connect(new_mark, &Mark::markAction, this, &Scene::markActionSc);

    return new_mark;
}

void Scene::removeMark()
{
    auto selectedItems = this->selectedItems();
    if (!selectedItems.empty())
    {
        for(auto item : selectedItems)
        {
            this->removeItem(item);
            Mark* markItem = qgraphicsitem_cast<Mark*>(item);
            emit markRemoved(markItem->getId());
            narrowingScene(item);
            delete item;
        }
    }
    else
    {
        showError("No items selected\nSelect at least one object");
    }
}

void Scene::removeMark(Mark* mark)
{
    emit markRemoved(mark->getId());
    narrowingScene(mark);
    this->removeItem(mark);

    delete mark;
}

void Scene::narrowingScene(QGraphicsItem* item)
{
    auto left = this->sceneRect().left();
    auto right = this->sceneRect().right();
    auto top = this->sceneRect().top();
    auto bottom = this->sceneRect().bottom();

    auto x = item->pos().x();
    auto y = item->pos().y();

    qreal newLeft = 0;
    qreal newTop = 0;
    qreal newRight = 0;
    qreal newBottom = 0;

    if (x < 0 && this->items(x, top, left, bottom, Qt::IntersectsItemShape, Qt::AscendingOrder).empty()) {
        newLeft = left - (left - x);
    }
    if (y < 0 && this->items(left, y, right, top, Qt::IntersectsItemShape, Qt::AscendingOrder).empty()) {
        newTop = top - (top - y);
    }
    if (x > 0 && this->items(x, top, right, bottom, Qt::IntersectsItemShape, Qt::AscendingOrder).empty()) {
        newRight = right - (right - x);
    }
    if (y > 0 && this->items(left, y, right, bottom, Qt::IntersectsItemShape, Qt::AscendingOrder).empty()) {
        newBottom = bottom - (bottom - y);
    }

    if(newLeft > (-GRID_SIZE * SCENE_X_COEF)) newLeft =-GRID_SIZE * SCENE_X_COEF;
    if(newTop > (-GRID_SIZE * SCENE_Y_COEF)) newTop = -GRID_SIZE * SCENE_Y_COEF;
    if(newRight < (GRID_SIZE * SCENE_WIDTH_COEF)) newRight = GRID_SIZE * SCENE_WIDTH_COEF;
    if(newBottom < (GRID_SIZE * SCENE_HEIGHT_COEF)) newBottom = GRID_SIZE * SCENE_HEIGHT_COEF;

    this->setSceneRect(newLeft, newTop, newRight, newBottom);
    this->invalidate();
}

void Scene::checkSceneSize(double x, double y)
{
    auto left = this->sceneRect().left();
    auto right = this->sceneRect().right();
    auto top = this->sceneRect().top();
    auto bottom = this->sceneRect().bottom();

    if (x < left) {
        left = x - (int)x % GRID_SIZE - EXPANSION_COEF * GRID_SIZE;
    }
    if (y < top) {
        top = y - (int)y % GRID_SIZE - EXPANSION_COEF * GRID_SIZE;
    }
    if (x > right) {
        right = x + (int)x % GRID_SIZE + EXPANSION_COEF * GRID_SIZE;
    }
    if (y > bottom) {
        bottom = y + (int)y % GRID_SIZE + EXPANSION_COEF * GRID_SIZE;
    }

    this->setSceneRect(left, top, right - left, bottom - top);
    this->invalidate();
}

void Scene::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Control)
    {
        emit setRubberBandDrag();
    }

    if (event->modifiers() == Qt::ControlModifier && event->key() == Qt::Key_A)
    {
        for (QGraphicsItem* item : this->items())
        {
            item->setSelected(true);
        }
    }

    QGraphicsScene::keyPressEvent(event);
}

void Scene::keyReleaseEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Control && !event->isAutoRepeat())
    {
        emit setScrollHandDrag();
    }

    QGraphicsScene::keyReleaseEvent(event);
}

void Scene::loadTable(QString filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        showError("Error opening file");
        return;
    }
    QTextStream in(&file);
    QString myString;

    myString = in.readLine(100);

    auto allItems = this->items();

    for(auto item : allItems)
    {
        if(Mark* markItem = qgraphicsitem_cast<Mark*>(item))
        {
            removeMark(markItem);
        }
    }

    while(!in.atEnd())
    {
        myString = in.readLine(100);
        auto list = myString.split(',');
        addMark(list[1].toDouble(), list[2].toDouble(), list[0].toInt());
    }
}

void Scene::saveInFile(QString filePath)
{
    QFile file(filePath);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        showError("Error opening file");
        return;
    }

    QTextStream out(&file);
    out << "label_id," << " x," << " y" << "\n";

    auto items = this->items();

    QVector<Mark*> marks;
    for(auto item : items)
    {
        if(Mark* markItem = qgraphicsitem_cast<Mark*>(item))
        {
            marks.push_back(markItem);
        }
    }

    std::sort(marks.begin(), marks.end(), [](Mark* a, Mark* b) ->
              bool{ return a->getId() < b->getId(); });

    for(auto markItem : marks)
    {
        auto [x,y] = toCoords(markItem->scenePos().x(), markItem->scenePos().y());
        out << markItem->getId() << ',' <<  x << ',' << y << '\n';
    }

    file.close();
}

void Scene::showError(QString errorText)
{
    QMessageBox::warning(parentWidget, "Error", errorText);
    emit setScrollHandDrag();
}

void Scene::markActionSc(QString action, int id, double x, double y)
{
    auto tempCoords = toCoords(x, y);
    emit markAction(action, id, tempCoords.first, tempCoords.second);
}

void Scene::moveLineAdd(double x1, double y1, double x2, double y2)
{
    auto step = MARK_SIZE / 2;

    QColor color(255, 36, 0, 255);
    QPen pen(color, 2);

    auto firstCoords = toPixels(x1,y1);
    auto secondCoords = toPixels(x2,y2);
    addLine(firstCoords.first + step, firstCoords.second + step, secondCoords.first + step, secondCoords.second + step, pen);
}

void Scene::moveLineDelete(double x1, double y1, double x2, double y2)
{
    auto firstCoords = toPixels(x1,y1);
    auto secondCoords = toPixels(x2,y2);
    auto step = MARK_SIZE / 2;

    auto temp = this->items(firstCoords.first + step, firstCoords.second + step, secondCoords.first + step, secondCoords.second + step,
                            Qt::IntersectsItemShape, Qt::AscendingOrder);
    for(auto i : temp)
    {
        if(auto item = qgraphicsitem_cast<QGraphicsLineItem*>(i))
        delete item;
    }
}
