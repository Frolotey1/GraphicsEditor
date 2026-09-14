#ifndef CREATEINFORMATWINDOW_H
#define CREATEINFORMATWINDOW_H
#include "QDialog"
#include "QDialogButtonBox"
#include "QPushButton"
#include "QStatusBar"
#include "QVBoxLayout"
#include "QFile"
#include "QIODevice"
#include "QTextEdit"
#include "QRegularExpression"
#include "QStandardPaths"

class CreateInFormatWindow : public QDialog {
    QTextEdit* file_name;
    QPushButton* create_file_button;
    QDialogButtonBox* button_box;
    QStatusBar* status;
    QString set_type_image = "";
    bool create_file = false;
public:
    CreateInFormatWindow(QWidget* parent,QString type_image);
    bool is_created() const;
private slots:
    void on_ok_clicked();
    void on_cancel_clicked();
};

#endif // CREATEINFORMATWINDOW_H
