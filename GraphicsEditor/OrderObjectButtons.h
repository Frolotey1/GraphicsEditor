#ifndef ORDEROBJECTBUTTONS_H
#define ORDEROBJECTBUTTONS_H
#include "QGroupBox"
#include "QPushButton"
#include "QList"

class OrderObjectButtons {
public:
    OrderObjectButtons();
    QList<QPushButton*> get_order_buttons() const;
    QGroupBox* get_common_object_buttons_name() const;
    QGroupBox* get_order_buttons_name() const;
    QGroupBox* get_common_graphics_scene_name() const;
private:
    QGroupBox* common_object_buttons_name = nullptr;
    QGroupBox* order_buttons_name = nullptr;
    QGroupBox* common_graphics_scene_name = nullptr;
    QList<QPushButton*> order_buttons;
};

#endif // ORDEROBJECTBUTTONS_H
