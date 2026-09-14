#include "TextObject.h"

TextObject::TextObject(QDialog* parent) : QDialog(parent) {
    setWindowTitle("Имя текстового объекта");
    setFixedSize(300,300);
    setStyleSheet("background-color: white; color: black;");
    setModal(true);

    QVBoxLayout* vertical_layout = new QVBoxLayout(this);
    vertical_layout->setAlignment(Qt::AlignCenter);
    vertical_layout->setSpacing(10);

    status = new QStatusBar();

    text_object_name = new QTextEdit();
    text_object_name->setPlaceholderText("Введите текст: ");

    create_text_object_button = new QPushButton("Создать текст");
    create_text_object_button->setStyleSheet("background-color: blue; color: white;");

    button_box = new QDialogButtonBox(
        QDialogButtonBox::Cancel | QDialogButtonBox::Ok,this);

    button_box->setCenterButtons(true);
    button_box->setStyleSheet("background-color: black; color: white;");

    vertical_layout->addWidget(text_object_name);
    vertical_layout->addWidget(create_text_object_button);
    vertical_layout->addWidget(button_box);
    vertical_layout->addWidget(status);

    QObject::connect(create_text_object_button,&QPushButton::clicked,[&](){
        if(text_object_name->toPlainText().isEmpty()) {
            status->showMessage("Напишите текст!",5000);
            return;
        }

        text = text_object_name->toPlainText();

    });

    QObject::connect(button_box,&QDialogButtonBox::accepted,this,&TextObject::on_ok_clicked);
    QObject::connect(button_box,&QDialogButtonBox::rejected,this,&TextObject::on_cancel_clicked);
}
void TextObject::on_ok_clicked() {
    if(!text.isEmpty()) {
        accept();
        return;
    }

    status->showMessage("Невалидный текстовой объект",5000);
}
void TextObject::on_cancel_clicked() {
    reject();
}
QString TextObject::get_text() const {
    return text;
}
