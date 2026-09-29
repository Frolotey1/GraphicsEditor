#include "OwnTextPixel.h"

OwnTextPixel::OwnTextPixel(QDialog* parent) : QDialog(parent) {
    setWindowTitle("Собственное кол-во пикселей");
    setStyleSheet("background-color: white; color: black;");
    setModal(true);

    text_pixel = new QLineEdit();
    text_pixel->setPlaceholderText("Введите собственное кол-во пикселей: ");
    text_pixel->setStyleSheet("background-color: darkgray; color: white;");

    QVBoxLayout* vertical_layout = new QVBoxLayout(this);
    vertical_layout->setAlignment(Qt::AlignCenter);
    vertical_layout->setSpacing(10);

    status = new QStatusBar();

    create_pixel_button = new QPushButton("Выбрать");
    create_pixel_button->setStyleSheet("background-color: blue; color: white;");

    button_box = new QDialogButtonBox(
        QDialogButtonBox::Cancel | QDialogButtonBox::Ok, this);

    button_box->setCenterButtons(true);
    button_box->setStyleSheet("background-color: black; color: white;");

    QObject::connect(create_pixel_button,&QPushButton::clicked,this,&OwnTextPixel::on_button_clicked);
    QObject::connect(button_box,&QDialogButtonBox::accepted,this,&OwnTextPixel::on_ok_clicked);
    QObject::connect(button_box,&QDialogButtonBox::rejected,this,&OwnTextPixel::on_cancel_clicked);

    vertical_layout->addWidget(text_pixel);
    vertical_layout->addWidget(create_pixel_button);
    vertical_layout->addWidget(button_box);
    vertical_layout->addWidget(status);
}
void OwnTextPixel::on_button_clicked() {
    QString text = text_pixel->text();

    if(text.isEmpty()) {
        status->showMessage("Введите кол-во пикселей!",5000);
        return;
    }

    if(!text.endsWith("px")) text += "px";

    QStringList divide_text = text.split('.');

    bool ok = false;
    int pixel_number = divide_text[0].toInt(&ok);

    if(!ok) {
        status->showMessage("Не удалось обработать текст с пикселями");
        return;
    }

    if(pixel_number < 0) {
        status->showMessage("Невалидное кол-во пикселей");
        return;
    }

    set_text_pixel(text);
    accept();
}
void OwnTextPixel::on_ok_clicked() {
    if(!pixel.isEmpty()) {
        accept();
        return;
    }

    status->showMessage("Невалидный текст",5000);
}
void OwnTextPixel::on_cancel_clicked() {
    reject();
}
void OwnTextPixel::set_text_pixel(QString _pixel) {
    pixel = _pixel;
}
QString OwnTextPixel::get_text_pixel() const {
    return pixel;
}
