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
public:
    CreateInFormatWindow(QWidget* parent,QString type_image);
    bool is_created() const;
private slots:
    void on_ok_clicked();
    void on_cancel_clicked();
private:
    QTextEdit* file_name = nullptr;
    QPushButton* create_file_button = nullptr;
    QDialogButtonBox* button_box = nullptr;
    QStatusBar* status = nullptr;
    QString set_type_image = "";
    bool create_file = false;
};

#endif // CREATEINFORMATWINDOW_H
