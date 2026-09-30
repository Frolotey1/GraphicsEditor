#include "include/Styles/StyleBrushLists.h"

StyleBrushLists::StyleBrushLists(QString set_brush_style) {
    brush_style = set_brush_style;

    brush_styles["Горизонтальный"] = Qt::HorPattern;
    brush_styles["Вертикальный"] = Qt::VerPattern;
    brush_styles["Сплошной"] = Qt::SolidPattern;
    brush_styles["Нет заливки"] = Qt::NoBrush;
}
Qt::BrushStyle StyleBrushLists::get_brush_style() const {
    return brush_styles.value(brush_style,Qt::SolidPattern);
}
