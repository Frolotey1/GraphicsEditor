#ifndef CUSTOMSHAPEITEM_H
#define CUSTOMSHAPEITEM_H
#include <QGraphicsItem>
#include <QPainter>
#include <QBrush>
#include <QPen>
#include <QString>
#include "QWidget"
#include "QGraphicsSceneMouseEvent"
#include "QGraphicsSceneHoverEvent"
#include "QGraphicsScene"
#include "QKeyEvent"
#include "QPainterPath"
#include "QList"
#include "QPointF"
#include "ShapeType.h"

class CustomShapeItem : public QGraphicsItem {
public:
    CustomShapeItem();

    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

    void hoverEnterEvent(QGraphicsSceneHoverEvent* event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent* event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void keyPressEvent(QKeyEvent* event) override;
    void set_shape(ShapeType type);

    ShapeType get_current_shape() const;

    void set_brush_color(QString brush_color);
    void set_pen_color(QString color);
    void set_text(const QString& _text);

    void start_custom_path();
    void finish_custom_path();
    void clear_custom_path();
    void add_point(const QPointF& point);

    QString get_brush_color() const;
    QString get_pen_color() const;
    QString get_text() const;
private:
    ShapeType current_shape = ShapeType::Rectangle;
    QBrush brush;
    QPen pen;
    QString text;

    QList<QPointF> custom_points;
    bool is_drawing_path = false;

    QString brush_color;
    QString pen_color;
};

#endif // CUSTOMSHAPEITEM_H