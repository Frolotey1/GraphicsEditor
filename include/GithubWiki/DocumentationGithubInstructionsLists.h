#ifndef DOCUMENTATIONGITHUBINSTRUCTIONSLISTS_H
#define DOCUMENTATIONGITHUBINSTRUCTIONSLISTS_H
#include "QMenu"
#include "QStringList"
#include "QToolButton"
#include "QString"

class DocumentationGithubInstructionsLists {
public:
    DocumentationGithubInstructionsLists(QToolButton* tool_button);
    QMenu* get_github_instructions_menu() const;
private:
    QStringList github_instructions;
    QMenu* github_instructions_menu = nullptr;
};

#endif // DOCUMENTATIONGITHUBINSTRUCTIONSLISTS_H
