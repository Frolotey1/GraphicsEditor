#include "GridScene.h"

GridScene::GridScene(QObject *parent) : QGraphicsScene(parent) {}

void GridScene::set_grid_size(int size) {
    grid_size = size;
    update();
}
void GridScene::set_grid_visible(bool &&visible) {
    grid_visible = visible;
    update();
}
void GridScene::drawBackground(QPainter *painter, const QRectF &rect) {
    QGraphicsScene::drawBackground(painter,rect);

    if(!grid_visible) return;

    QPen pen(Qt::lightGray);
    pen.setWidth(1);
    painter->setPen(pen);

    qreal left = int(rect.left()) - (int(rect.left()) % grid_size);
    qreal top = int(rect.top()) - (int(rect.top()) % grid_size);

    QList<QLineF> lines;

    for (qreal x = left; x < rect.right(); x += grid_size) {
        lines.append(QLineF(x, rect.top(), x, rect.bottom()));
    }

    for (qreal y = top; y < rect.bottom(); y += grid_size) {
        lines.append(QLineF(rect.left(), y, rect.right(), y));
    }

    painter->drawLines(lines);
}
int GridScene::get_grid_size() const {
    return grid_size;
}
