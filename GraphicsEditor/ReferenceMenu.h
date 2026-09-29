#ifndef REFERENCEMENU_H
#define REFERENCEMENU_H
#include "QMenu"
#include "QAction"
#include "QToolButton"
#include "QWidgetAction"
#include "QString"
#include "DocumentationGithubInstructionsLists.h"

class ReferenceMenu {
public:
    ReferenceMenu();
    QMenu* get_menu() const;
    QAction* get_about_program_action() const;
    QToolButton* get_github_instructions_tool_button() const;
private:
    QMenu* set_menu = nullptr;
    QAction* about_program_action = nullptr;
    QWidgetAction* wa = nullptr;
    QToolButton* documentation_github_tool_button= nullptr;
    DocumentationGithubInstructionsLists* dgil;
};

#endif // REFERENCEMENU_H
