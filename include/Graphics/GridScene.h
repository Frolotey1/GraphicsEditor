#ifndef GRIDSCENE_H
#define GRIDSCENE_H
#include "QObject"
#include "QGraphicsScene"
#include <QList>
#include "QPen"
#include "QBrush"
#include "QPainter"

class GridScene : public QGraphicsScene {
public:
    GridScene(QObject* parent = nullptr);
    int get_grid_size() const;
    void set_grid_size(int size);
    void set_grid_visible(bool&& visible);
    void drawBackground(QPainter *painter, const QRectF &rect);
private:
    bool grid_visible = false;
    int grid_size = 0;
};

#endif // GRIDSCENE_H
