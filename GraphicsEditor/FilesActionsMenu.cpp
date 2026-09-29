#include "FilesActionsMenu.h"

FilesActionsMenu::FilesActionsMenu() {
    create_menu = new QMenu("Создать в формате");
    create_menu->addAction("JPG");
    create_menu->addAction("JPEG");
    create_menu->addAction("PNG");
    create_menu->addAction("SVG");
    create_menu->addAction("BMP");

    pdf_menu = new QMenu("PDF");

    set_tool_button = new QToolButton();
    set_tool_button->setText("Экспорт");
    set_tool_button->setPopupMode(QToolButton::MenuButtonPopup);

    wa = new QWidgetAction(pdf_menu);
    sspfl = new ScaleSizePdfFileLists(set_tool_button);

    set_tool_button->setMenu(sspfl->get_scale_size_menu());

    wa->setDefaultWidget(set_tool_button);

    pdf_menu->addAction(wa);
    pdf_menu->addAction("Импорт");

    open_action = new QAction("Открыть");
    open_action->setShortcut(QKeySequence::Open);

    save_action = new QAction("Сохранить");
    save_action->setShortcut(QKeySequence::Save);
}

QMenu* FilesActionsMenu::get_menu() {
    set_menu = new QMenu("Файл");

    set_menu->addAction(create_menu->menuAction());
    set_menu->addAction(open_action);
    set_menu->addAction(save_action);
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
QAction* FilesActionsMenu::get_import_action() const {
    return import_action;
}
QToolButton* FilesActionsMenu::get_tool_button() const {
    return set_tool_button;
}