#ifndef FILESACTIONSMENU_H
#define FILESACTIONSMENU_H
#include <QAction>
#include <QWidgetAction>
#include <QToolButton>
#include <QMenu>
#include <QString>
#include <QKeySequence>
#include "include/Pdf/ScaleSizePdfFileLists.h"

class FilesActionsMenu {
public:
    FilesActionsMenu();

    QMenu* get_menu();
    QMenu* get_create_menu() const;
    QMenu* get_pdf_menu() const;

    QAction* get_open_action() const;
    QAction* get_save_action() const;
    QAction* get_import_action() const;
    QToolButton* get_tool_button() const;
private:
    QMenu* set_menu = nullptr;
    QMenu* create_menu = nullptr;
    QMenu* pdf_menu = nullptr;

    QWidgetAction* wa = nullptr;
    ScaleSizePdfFileLists* sspfl = nullptr;
    QToolButton* set_tool_button = nullptr;
    QAction* import_action = nullptr;
    QAction* open_action = nullptr;
    QAction* save_action = nullptr;
};

#endif // FILESACTIONSMENU_H