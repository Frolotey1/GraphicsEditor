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
public:
    TextObject(QDialog* parent = nullptr);
    QString get_text() const;
private slots:
    void on_ok_clicked();
    void on_cancel_clicked();
private:
    QTextEdit* text_object_name = nullptr;
    QPushButton* create_text_object_button = nullptr;
    QStatusBar* status = nullptr;
    QDialogButtonBox* button_box = nullptr;
    QString text;
};

#endif // TEXTOBJECT_H
