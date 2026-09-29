#include "StyleJoinCircuitLists.h"

StyleJoinCircuitLists::StyleJoinCircuitLists(QString set_pen_join_style) {
    pen_join_style = set_pen_join_style;

    pen_join_styles["Срезанный угол"] = Qt::BevelJoin;
    pen_join_styles["Острый угол"] = Qt::MiterJoin;
    pen_join_styles["Закругленный угол"] = Qt::RoundJoin;
}
Qt::PenJoinStyle StyleJoinCircuitLists::get_pen_join_style() const {
    return pen_join_styles.value(pen_join_style,Qt::BevelJoin);
}
