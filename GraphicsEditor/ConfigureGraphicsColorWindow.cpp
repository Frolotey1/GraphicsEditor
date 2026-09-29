#include "ConfigureGraphicsColorWindow.h"

ConfigureGraphicsColorWindow::ConfigureGraphicsColorWindow(QDialog* parent)
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

    connect(choose_color_button,&QPushButton::clicked,this,&ConfigureGraphicsColorWindow::on_choose_clicked);
    connect(button_box,&QDialogButtonBox::accepted,this,&ConfigureGraphicsColorWindow::on_ok_clicked);
    connect(button_box,&QDialogButtonBox::rejected,this,&ConfigureGraphicsColorWindow::on_cancel_clicked);

}
void ConfigureGraphicsColorWindow::on_choose_clicked() {
    QColor _color = QColorDialog::getColor(Qt::white,this,"Выбор цвета для окна");

    if(_color.isValid()) {
        set_graphics_background_color(_color);
    } else {
        status->showMessage("Неизвестный цвет",5000);
    }
}
void ConfigureGraphicsColorWindow::on_ok_clicked() {
    if(color.isValid()) {
        accept();
        return;
    }

    status->showMessage("Невалидный цвет",5000);
}
void ConfigureGraphicsColorWindow::on_cancel_clicked() {
    reject();
}
void ConfigureGraphicsColorWindow::set_graphics_background_color(QColor& _color) {
    color = _color;
}
QString ConfigureGraphicsColorWindow::get_graphics_background_color() const {
    return color.name();
}

