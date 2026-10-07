#include "include/GithubWiki/DocumentationGithubInstructionsLists.h"

DocumentationGithubInstructionsLists::DocumentationGithubInstructionsLists(QToolButton* tool_button) {
    github_instructions_menu = new QMenu(tool_button);
    github_instructions_menu->setToolTipsVisible(true);

    github_instructions = {"Панель окна",
                           "Графическая сцена"};

    for(auto& github_instruction : github_instructions) {
        github_instructions_menu->addAction(github_instruction);
    }

    for(QAction* github_instruction_action : github_instructions_menu->actions()) {
        if(github_instruction_action->text() == "Панель окна") {
            github_instruction_action->setToolTip("Инструкция для работы с панелью окна приложения");
        } else if(github_instruction_action->text() == "Графическая сцена") {
            github_instruction_action->setToolTip("Инструкция для работы с графической сценой приложения");
        }
    }
}
QMenu* DocumentationGithubInstructionsLists::get_github_instructions_menu() const {
    return github_instructions_menu;
}
