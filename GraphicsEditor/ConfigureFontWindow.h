#ifndef CONFIGUREFONTWINDOW_H
#define CONFIGUREFONTWINDOW_H
#include "QDialog"
#include "QDialogButtonBox"
#include "QFont"
#include "QFontDialog"
#include "QPushButton"
#include "QVBoxLayout"
#include "QStatusBar"

class ConfigureFontWindow : public QDialog {
public:
    ConfigureFontWindow(QDialog* parent = nullptr);
    void set_font(QFont _font);
    QFont get_font();
private slots:
    void on_choose_clicked();
    void on_ok_clicked();
    void on_cancel_clicked();
private:
    QFont font;
    QPushButton* choose_font_button = nullptr;
    QStatusBar* status = nullptr;
    QDialogButtonBox* button_box = nullptr;
};

#endif // CONFIGUREFONTWINDOW_H
