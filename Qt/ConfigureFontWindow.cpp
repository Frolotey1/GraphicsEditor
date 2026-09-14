#include "ConfigureFontWindow.h"

ConfigureFontWindow::ConfigureFontWindow(QDialog* parent) : QDialog(parent) {
    setWindowTitle("Настройка шрифтов текста");
    setFixedSize(300,300);
    setStyleSheet("background-color: white; color: black;");
    setModal(true);

    choose_font_button = new QPushButton("Выбрать шрифт для текста");
    choose_font_button->setStyleSheet("background-color: blue; color: white;");

    status = new QStatusBar();

    button_box = new QDialogButtonBox(
        QDialogButtonBox::Cancel | QDialogButtonBox::Ok, this);

    button_box->setCenterButtons(true);
    button_box->setStyleSheet("background-color: black; color: white;");

    QVBoxLayout* vertical_layout = new QVBoxLayout(this);
    vertical_layout->setAlignment(Qt::AlignCenter);
    vertical_layout->setSpacing(10);

    vertical_layout->addWidget(choose_font_button);
    vertical_layout->addWidget(button_box);
    vertical_layout->addWidget(status);

    connect(choose_font_button,&QPushButton::clicked,this,&ConfigureFontWindow::on_choose_clicked);
    QObject::connect(button_box,&QDialogButtonBox::accepted,this,&ConfigureFontWindow::on_ok_clicked);
    QObject::connect(button_box,&QDialogButtonBox::rejected,this,&ConfigureFontWindow::on_cancel_clicked);
}

void ConfigureFontWindow::on_choose_clicked() {
    bool ok;
    QFont _font = QFontDialog::getFont(&ok,QFont("Arial",10),this);

    if(ok) {
        font = _font;
        set_font(_font);
    } else {
        status->showMessage("Неизвестный шрифт",5000);
    }
}
void ConfigureFontWindow::on_ok_clicked() {
    if(!font.styleName().isEmpty()) {
        accept();
        return;
    }

    status->showMessage("Невалидный шрифт",5000);
}
void ConfigureFontWindow::on_cancel_clicked() {
    reject();
}
void ConfigureFontWindow::set_font(QFont _font) {
    font = _font;
}
QFont ConfigureFontWindow::get_font() {
    return font;
}
