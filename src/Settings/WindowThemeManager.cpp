#include "include/Settings/WindowThemeManager.h"

WindowThemeManager::WindowThemeManager(QString type_style) : set_type_style(type_style) {
    theme_type_styles["Светлая тема"] = {qMakePair(Qt::white,Qt::black),qMakePair(Qt::white,Qt::black)};
    theme_type_styles["Темная тема"] = {qMakePair(Qt::black,Qt::white),qMakePair(Qt::black,Qt::white)};
    theme_type_styles["Светло-темная тема"] = {qMakePair(Qt::white,Qt::black),qMakePair(Qt::black,Qt::white)};
    theme_type_styles["Темно-светлая тема"] = {qMakePair(Qt::black,Qt::white),qMakePair(Qt::white,Qt::black)};
}

QPair<QPair<QColor,QColor>,QPair<QColor,QColor>> WindowThemeManager::get_style_palette() {
    auto pair =
        qMakePair(theme_type_styles[set_type_style].at(0),theme_type_styles[set_type_style].at(1));

    return pair;
}
