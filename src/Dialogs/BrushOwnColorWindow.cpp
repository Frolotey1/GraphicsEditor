#include "include/Dialogs/BrushOwnColorWindow.h"

BrushOwnColorWindow::BrushOwnColorWindow(QDialog* parent)
    : QDialog(parent) {

    setWindowTitle("Диалоговое окно");
    setFixedSize(300,300);
    setStyleSheet("background-color: white; color: black;");
    setModal(true);

    QVBoxLayout* vertical_layout = new QVBoxLayout(this);
    vertical_layout->setSpacing(10);
    vertical_layout->setAlignment(Qt::AlignCenter);

    create_color_button = new QPushButton("Создать свой цвет");
    create_color_button->setStyleSheet("background-color: blue; color: white;");
    status = new QStatusBar();

    button_box = new QDialogButtonBox(
        QDialogButtonBox::Cancel | QDialogButtonBox::Ok,this
    );

    button_box->setCenterButtons(true);
    button_box->setStyleSheet("background-color: black; color: white;");

    vertical_layout->addWidget(create_color_button);
    vertical_layout->addWidget(button_box);
    vertical_layout->addWidget(status);

    QObject::connect(create_color_button,&QPushButton::clicked,this,&BrushOwnColorWindow::on_button_clicked);
    QObject::connect(button_box,&QDialogButtonBox::accepted,this,&BrushOwnColorWindow::on_ok_clicked);
    QObject::connect(button_box,&QDialogButtonBox::rejected,this,&BrushOwnColorWindow::on_cancel_clicked);

}
void BrushOwnColorWindow::on_button_clicked() {
    QColor create_color = QColorDialog::getColor(Qt::white,this,"Выберите цвет для заливки");

    if(create_color.isValid()) {
        color = create_color;
    } else {
        status->showMessage("Неизвестный цвет для заливки",5000);
    }
}
void BrushOwnColorWindow::on_ok_clicked() {
    if(color.isValid()) {
        accept();
        return;
    }

    status->showMessage("Невалидный цвет для окна",5000);
}
void BrushOwnColorWindow::on_cancel_clicked() {
    reject();
}
QString BrushOwnColorWindow::get_brush_color() const {
    return color.name();
}
