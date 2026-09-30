#include "include/Styles/StyleLineCircuitLists.h"

StyleLineCircuitLists::StyleLineCircuitLists(QString set_pen_style) {
    pen_style = set_pen_style;

    pen_styles["Сплошная"] = Qt::SolidLine;
    pen_styles["Пунктир"] = Qt::DashLine;
    pen_styles["Точки"] = Qt::DotLine;
    pen_styles["Тире-точка"] = Qt::DashDotLine;
    pen_styles["Тире-две-точки"] = Qt::DashDotDotLine;
    pen_styles["Нет контура"] = Qt::NoPen;
}
Qt::PenStyle StyleLineCircuitLists::get_pen_style() const {
    return pen_styles.value(pen_style,Qt::SolidLine);
}
