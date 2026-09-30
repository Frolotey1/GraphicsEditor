#ifndef STYLEBRUSHLISTS_H
#define STYLEBRUSHLISTS_H
#include "QMap"
#include "QBrush"
#include "QString"

class StyleBrushLists {
public:
    StyleBrushLists(QString set_brush_style);
    Qt::BrushStyle get_brush_style() const;
private:
    QMap<QString,Qt::BrushStyle> brush_styles;
    QString brush_style;
};

#endif // STYLEBRUSHLISTS_H
