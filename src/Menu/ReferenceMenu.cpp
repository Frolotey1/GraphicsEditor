#include "include/Menu/ReferenceMenu.h"

ReferenceMenu::ReferenceMenu() {
    set_menu = new QMenu("Справка");

    about_program_action = new QAction("О программе");

    wa = new QWidgetAction(set_menu);

    documentation_github_tool_button = new QToolButton();
    documentation_github_tool_button->setText("Документация на Github");
    documentation_github_tool_button->setPopupMode(QToolButton::MenuButtonPopup);

    dgil = new DocumentationGithubInstructionsLists(documentation_github_tool_button);
    documentation_github_tool_button->setMenu(dgil->get_github_instructions_menu());

    wa->setDefaultWidget(documentation_github_tool_button);

    set_menu->addAction(wa);
    set_menu->addAction(about_program_action);
}
QMenu* ReferenceMenu::get_menu() const {
    return set_menu;
}
QAction* ReferenceMenu::get_about_program_action() const {
    return about_program_action;
}
QToolButton* ReferenceMenu::get_github_instructions_tool_button() const {
    return documentation_github_tool_button;
}
