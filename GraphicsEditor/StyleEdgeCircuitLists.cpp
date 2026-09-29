#include "StyleEdgeCircuitLists.h"

StyleEdgeCircuitLists::StyleEdgeCircuitLists(QString set_pen_cap_style) {
    pen_cap_style = set_pen_cap_style;

    pen_cap_styles["Квадратный"] = Qt::SquareCap;
    pen_cap_styles["Плоский"] = Qt::FlatCap;
    pen_cap_styles["Закругленный"] = Qt::RoundCap;
}
Qt::PenCapStyle StyleEdgeCircuitLists::get_pen_cap_style() const {
    return pen_cap_styles.value(pen_cap_style,Qt::SquareCap);
}
