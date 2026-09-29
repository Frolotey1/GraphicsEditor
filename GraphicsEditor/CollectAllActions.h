#ifndef COLLECTALLACTIONS_H
#define COLLECTALLACTIONS_H
#include "QToolBar"
#include "QMenu"
#include "QAction"
#include "QString"
#include "QStringList"

class CollectAllActions {
public:
    QStringList collect_all_actions(QToolBar* tool_bar);
private:
    QStringList all_actions;
};

#endif // COLLECTALLACTIONS_H
