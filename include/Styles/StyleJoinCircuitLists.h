#ifndef STYLEJOINCIRCUITLISTS_H
#define STYLEJOINCIRCUITLISTS_H
#include "QMap"
#include "QPen"
#include "QString"

class StyleJoinCircuitLists {
public:
    StyleJoinCircuitLists(QString set_pen_join_style);
    Qt::PenJoinStyle get_pen_join_style() const;
private:
    QMap<QString,Qt::PenJoinStyle> pen_join_styles;
    QString pen_join_style;
};

#endif // STYLEJOINCIRCUITLISTS_H
