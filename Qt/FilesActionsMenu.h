#ifndef FILESACTIONSMENU_H
#define FILESACTIONSMENU_H
#include <QAction>
#include <QMenu>
#include <QString>
#include <QKeySequence>

class FilesActionsMenu {
public:
    FilesActionsMenu();

    QMenu* get_menu();
    QMenu* get_create_menu() const;
    QMenu* get_pdf_menu() const;

    QAction* get_open_action() const;
    QAction* get_save_action() const;

private:
    QMenu* set_menu = nullptr;
    QMenu* create_menu = nullptr;
    QMenu* pdf_menu = nullptr;

    QAction* open_action = nullptr;
    QAction* save_action = nullptr;
};

#endif // FILESACTIONSMENU_H