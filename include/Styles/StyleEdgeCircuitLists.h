#ifndef STYLEEDGECIRCUITLISTS_H
#define STYLEEDGECIRCUITLISTS_H
#include "QMap"
#include "QPen"
#include "QString"

class StyleEdgeCircuitLists {
public:
    StyleEdgeCircuitLists(QString set_pen_cap_style);
    Qt::PenCapStyle get_pen_cap_style() const;
private:
    QString pen_cap_style;
    QMap<QString,Qt::PenCapStyle> pen_cap_styles;
};

#endif // STYLEEDGECIRCUITLISTS_H
