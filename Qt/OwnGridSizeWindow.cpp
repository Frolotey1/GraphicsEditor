#include "OwnGridSizeWindow.h"

OwnGridSizeWindow::OwnGridSizeWindow(QDialog *parent) : QDialog(parent) {
    setWindowTitle("Диалоговое окно");
    setFixedSize(300,300);
    setStyleSheet("background-color: white; color: black;");

    QVBoxLayout* vertical_layout = new QVBoxLayout(this);
    vertical_layout->setAlignment(Qt::AlignCenter);
    vertical_layout->setSpacing(10);

    button_box = new QDialogButtonBox(
        QDialogButtonBox::Cancel | QDialogButtonBox::Ok,this);

    button_box->setCenterButtons(true);
    button_box->setStyleSheet("background-color: black; color: white;");

    accept_grid_button = new QPushButton("Задать свой размер для сетки");
    accept_grid_button->setStyleSheet("background-color: blue; color: white;");

    own_grid_text = new QLineEdit();
    own_grid_text->setPlaceholderText("Введите размер для сетки");
    own_grid_text->setStyleSheet("background-color: darkgray; color: white;");

    vertical_layout->addWidget(own_grid_text);
    vertical_layout->addWidget(accept_grid_button);
    vertical_layout->addWidget(button_box);

    connect(accept_grid_button,&QPushButton::clicked,this,&OwnGridSizeWindow::on_button_clicked);
    connect(button_box,&QDialogButtonBox::accepted,this,&OwnGridSizeWindow::on_ok_clicked);
    connect(button_box,&QDialogButtonBox::rejected,this,&OwnGridSizeWindow::on_cancel_clicked);

}
void OwnGridSizeWindow::on_button_clicked() {
    QString own_text = own_grid_text->text();

    if(!own_text.isEmpty()) {
        bool converted = false;
        int size = own_text.toInt(&converted);

        if(converted) {
            if(size > 0) {
                QRegularExpression chars("\\[]{}%^:@!;',()-+&?*№=`~|/<>.");

                if(!own_text.contains(chars)) {
                    set_accept = true;
                }
            }
        }
    }
}
void OwnGridSizeWindow::on_ok_clicked() {
    if(is_accepted())
        accept();
}
void OwnGridSizeWindow::on_cancel_clicked() {
    reject();
}
int OwnGridSizeWindow::get_own_grid_size() const {
    return own_grid_size;
}
bool OwnGridSizeWindow::is_accepted() const {
    return set_accept;
}
