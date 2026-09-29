#ifndef STYLELINECIRCUITLISTS_H
#define STYLELINECIRCUITLISTS_H
#include "QMap"
#include "QPen"
#include "QString"

class StyleLineCircuitLists {
public:
    StyleLineCircuitLists(QString set_pen_style);
    Qt::PenStyle get_pen_style() const;
private:
    QString pen_style;
    QMap<QString,Qt::PenStyle> pen_styles;
};

#endif // STYLELINECIRCUITLISTS_H
