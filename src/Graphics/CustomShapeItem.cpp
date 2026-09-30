#include "include/Graphics/CustomShapeItem.h"

CustomShapeItem::CustomShapeItem() {
    brush = QBrush(Qt::black);
    pen = QPen(Qt::black);
    pen.setWidth(2);

    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsSelectable);
    setFlag(QGraphicsItem::ItemIsFocusable);
}
QRectF CustomShapeItem::boundingRect() const {
    if(current_shape == ShapeType::CustomPath && !custom_points.isEmpty()) {
        QRectF rect = QPolygonF(custom_points).boundingRect();
        return rect.adjusted(-10,10,10,10);
    }
    return QRectF(-100, -100, 200, 200);
}
void CustomShapeItem::set_shape(ShapeType type) {
    current_shape = type;
    update();
}
ShapeType CustomShapeItem::get_current_shape() const {
    return current_shape;
}
void CustomShapeItem::set_brush_color(QString _brush_color) {
    brush_color = _brush_color;
    brush.setColor(QColor(brush_color));
    update();
}
void CustomShapeItem::set_pen_color(QString _pen_color) {
    pen_color = _pen_color;
    pen.setColor(QColor(pen_color));
    update();
}
void CustomShapeItem::set_text(const QString& _text) {
    text = _text;
    update();
}
void CustomShapeItem::set_font_text_style(QFont set_font) {
    font = set_font;
    update();
}
void CustomShapeItem::configure_pen_style(Qt::PenStyle pen_style) {
    pen.setStyle(pen_style);
    update();
}
void CustomShapeItem::configure_brush_style(Qt::BrushStyle brush_style) {
    brush.setStyle(brush_style);
    update();
}
void CustomShapeItem::configure_pen_cap_style(Qt::PenCapStyle pen_cap_style) {
    pen.setCapStyle(pen_cap_style);
    update();
}
void CustomShapeItem::configure_pen_join_style(Qt::PenJoinStyle pen_join_style) {
    pen.setJoinStyle(pen_join_style);
    update();
}
QString CustomShapeItem::get_brush_color() const {
    return brush_color;
}
QString CustomShapeItem::get_pen_color() const {
    return pen_color;
}
QString CustomShapeItem::get_text() const {
    return text;
}
void CustomShapeItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setBrush(brush);
    painter->setPen(pen);

    switch(current_shape) {
        case ShapeType::Rectangle:
            painter->drawRect(-50, -30, 100, 60);
            break;
        case ShapeType::Ellipse:
            painter->drawEllipse(-50, -30, 100, 60);
            break;
        case ShapeType::Line:
            painter->drawLine(-80, 0, 80, 0);
            break;
        case ShapeType::Text: {
            painter->setPen(QPen(brush.color()));
            font.setPointSize(15);
            painter->setFont(font);

            QRectF rect(-100,-50,200,100);
            painter->drawText(rect,Qt::AlignCenter,text);
            break;
        }
        case ShapeType::Polygon: {
            QPolygonF polygon;
            polygon << QPointF(0, -50)
                    << QPointF(40, -10)
                    << QPointF(50, 30)
                    << QPointF(-50, 30)
                    << QPointF(-40, -10);
            painter->drawPolygon(polygon);
            break;
        }
        case ShapeType::CustomPath: {
            if(custom_points.size() < 2) break;

            painter->setBrush(Qt::NoBrush);

            QPainterPath path;
            path.moveTo(custom_points.at(0));

            for(int i = 1; i < custom_points.size(); ++i) {
                path.lineTo(custom_points.at(i));
            }

            painter->drawPath(path);
        }
    }
}
void CustomShapeItem::start_custom_path() {
    custom_points.clear();
    is_drawing_path = true;
    setFlag(QGraphicsItem::ItemIsMovable,false);
    update();
}
void CustomShapeItem::finish_custom_path() {
    is_drawing_path = false;
    setFlag(QGraphicsItem::ItemIsMovable,true);
    update();
}
void CustomShapeItem::add_point(const QPointF &point) {
    custom_points.append(point);
    update();
}
void CustomShapeItem::clear_custom_path() {
    custom_points.clear();
    update();
}
void CustomShapeItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event) {
    setOpacity(0.5);

    QGraphicsItem::hoverEnterEvent(event);
}
void CustomShapeItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event) {
    setOpacity(1.0);

    QGraphicsItem::hoverLeaveEvent(event);
}
void CustomShapeItem::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    if(event->button() == Qt::LeftButton) {
        setSelected(true);

        if(current_shape == ShapeType::CustomPath && is_drawing_path) {
            QPointF local_pos = mapFromScene(event->scenePos());
            add_point(local_pos);
            event->accept();
            return;
        }
    }

    if(event->button() == Qt::RightButton && is_drawing_path) {
        finish_custom_path();
        event->accept();
        return;
    }

    QGraphicsItem::mousePressEvent(event);
}
void CustomShapeItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    if(event->button() == Qt::LeftButton) {
        setSelected(false);
    }

    QGraphicsItem::mouseReleaseEvent(event);
}
void CustomShapeItem::mouseMoveEvent(QGraphicsSceneMouseEvent* event) {
    if (is_drawing_path && current_shape == ShapeType::CustomPath) {
        if (custom_points.isEmpty() ||
            QLineF(custom_points.last(), event->pos()).length() > 3) {
            add_point(event->pos());
        }
        event->accept();
        return;
    }

    QGraphicsItem::mouseMoveEvent(event);
}
void CustomShapeItem::keyPressEvent(QKeyEvent *event) {
    if(event->key() == Qt::Key_Delete) {
        if(scene()) {
            scene()->removeItem(this);
            delete this;
        }

        return;
    }

    QGraphicsItem::keyPressEvent(event);
}