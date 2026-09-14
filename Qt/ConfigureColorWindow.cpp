#include "ConfigureColorWindow.h"

ConfigureColorWindow::ConfigureColorWindow(QDialog* parent)
    : QDialog(parent) {

    setWindowTitle("Диалоговое окно");
    setFixedSize(300,300);
    setStyleSheet("background-color: white; color: black;");
    setModal(true);

    choose_color_button = new QPushButton("Выбрать цвет для окна");
    choose_color_button->setStyleSheet("background-color: blue; color: white;");

    status = new QStatusBar();

    button_box = new QDialogButtonBox(
        QDialogButtonBox::Cancel | QDialogButtonBox::Ok,this);

    button_box->setCenterButtons(true);
    button_box->setStyleSheet("background-color: black; color: white;");

    QVBoxLayout* vertical_layout = new QVBoxLayout(this);
    vertical_layout->setAlignment(Qt::AlignCenter);
    vertical_layout->setSpacing(10);

    vertical_layout->addWidget(choose_color_button);
    vertical_layout->addWidget(button_box);
    vertical_layout->addWidget(status);

    connect(choose_color_button,&QPushButton::clicked,this,&ConfigureColorWindow::on_choose_clicked);
    connect(button_box,&QDialogButtonBox::accepted,this,&ConfigureColorWindow::on_ok_clicked);
    connect(button_box,&QDialogButtonBox::rejected,this,&ConfigureColorWindow::on_cancel_clicked);

}
void ConfigureColorWindow::on_choose_clicked() {
    QColor _color = QColorDialog::getColor(Qt::white,this,"Выбор цвета для окна");

    if(_color.isValid()) {
        set_foreground_color(_color);
        set_background_color(_color);
    } else {
        status->showMessage("Неизвестный цвет",5000);
    }
}
void ConfigureColorWindow::on_ok_clicked() {
    if(color.isValid()) {
        accept();
        return;
    }

    status->showMessage("Невалидный цвет",5000);
}
void ConfigureColorWindow::on_cancel_clicked() {
    reject();
}
void ConfigureColorWindow::set_foreground_color(const QColor& configure_color) {
    const int threshold = 130;

    if(configure_color.lightness() > threshold)
        foreground_color = QColor(Qt::black).name();
    else
        foreground_color = QColor(Qt::white).name();
}
QString ConfigureColorWindow::get_foreground_color() const {
    return foreground_color;
}
void ConfigureColorWindow::set_background_color(QColor _color) {
    color = _color;
}
QString ConfigureColorWindow::get_background_color() const {
    return color.name();
}

