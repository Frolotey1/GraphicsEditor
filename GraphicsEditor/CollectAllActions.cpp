#include "CollectAllActions.h"

QStringList CollectAllActions::collect_all_actions(QToolBar *tool_bar) {

    for(QAction* action : tool_bar->actions()) {
        QMenu* menu = action->menu();

        if(!menu) continue;

        for(QAction* menu_action : menu->actions()) {
            QString menu_text = menu_action->text();

            if(!menu_text.isEmpty()) all_actions << menu_text;


            QMenu* sub_menu = menu_action->menu();

            if(sub_menu) {
                for(QAction* sub_menu_action : sub_menu->actions()) {
                    QString sub_menu_text = sub_menu_action->text();

                    if(!sub_menu_text.isEmpty()) all_actions << sub_menu_text;


                    QMenu* sub_sub_menu = sub_menu_action->menu();

                    if(sub_sub_menu) {
                        for(QAction* sub_sub_menu_action : sub_sub_menu->actions()) {
                            QString sub_sub_menu_text = sub_sub_menu_action->text();

                            if(!sub_sub_menu_text.isEmpty()) all_actions << sub_sub_menu_text;
                        }
                    }
                }
            }
        }
    }

    return all_actions;
}