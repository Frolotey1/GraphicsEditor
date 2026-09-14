#include "FilesActionsMenu.h"

FilesActionsMenu::FilesActionsMenu() {
    create_menu = new QMenu("Создать в формате");
    create_menu->addAction("JPG");
    create_menu->addSeparator();
    create_menu->addAction("PNG");
    create_menu->addSeparator();
    create_menu->addAction("SVG");
    create_menu->addSeparator();
    create_menu->addAction("BMP");

    pdf_menu = new QMenu("PDF");
    pdf_menu->addAction("Экспорт");
    pdf_menu->addAction("Импорт");

    pdf_menu->actions().at(0)->setShortcut(QKeySequence("Ctrl+E"));
    pdf_menu->actions().at(1)->setShortcut(QKeySequence("Ctrl+I"));

    open_action = new QAction("Открыть");
    open_action->setShortcut(QKeySequence::Open);

    save_action = new QAction("Сохранить");
    save_action->setShortcut(QKeySequence::Save);
}

QMenu* FilesActionsMenu::get_menu() {
    set_menu = new QMenu("Файл");

    set_menu->addAction(create_menu->menuAction());
    set_menu->addSeparator();
    set_menu->addAction(open_action);
    set_menu->addSeparator();
    set_menu->addAction(save_action);
    set_menu->addSeparator();
    set_menu->addAction(pdf_menu->menuAction());

    return set_menu;
}
QMenu* FilesActionsMenu::get_pdf_menu() const {
    return pdf_menu;
}
QMenu* FilesActionsMenu::get_create_menu() const {
    return create_menu;
}
QAction* FilesActionsMenu::get_open_action() const {
    return open_action;
}

QAction* FilesActionsMenu::get_save_action() const {
    return save_action;
}