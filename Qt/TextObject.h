#ifndef TEXTOBJECT_H
#define TEXTOBJECT_H
#include "QDialog"
#include "QDialogButtonBox"
#include "QTextEdit"
#include "QPushButton"
#include "QVBoxLayout"
#include "QStatusBar"
#include "CustomShapeItem.h"

class TextObject : public QDialog {
    QTextEdit* text_object_name;
    QPushButton* create_text_object_button;
    QStatusBar* status;
    QDialogButtonBox* button_box;
    QString text;
public:
    TextObject(QDialog* parent = nullptr);
    QString get_text() const;
private slots:
    void on_ok_clicked();
    void on_cancel_clicked();
};

#endif // TEXTOBJECT_H
