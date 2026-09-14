#include "CreateInFormatWindow.h"

CreateInFormatWindow::CreateInFormatWindow(QWidget *parent, QString type_image)
    : QDialog(parent), set_type_image(type_image) {

    setWindowTitle("Диалоговое окно");
    setStyleSheet("background-color: white; color: black;");
    setFixedSize(300,300);

    QVBoxLayout* vertical_layout = new QVBoxLayout(this);
    vertical_layout->setAlignment(Qt::AlignCenter);
    vertical_layout->setSpacing(10);

    status = new QStatusBar();

    file_name = new QTextEdit();
    file_name->setPlaceholderText("Введите имя файла");
    file_name->setStyleSheet("background-color: darkgray: color: white;");

    create_file_button = new QPushButton("Создать файл");
    create_file_button->setStyleSheet("background-color: blue; color: white;");

    button_box = new QDialogButtonBox(
        QDialogButtonBox::Cancel | QDialogButtonBox::Ok,this);

    button_box->setCenterButtons(true);
    button_box->setStyleSheet("background-color: black; color: white;");

    vertical_layout->addWidget(file_name);
    vertical_layout->addWidget(create_file_button);
    vertical_layout->addWidget(button_box);
    vertical_layout->addWidget(status);

    QObject::connect(create_file_button,&QPushButton::clicked,[&](){
        QString text_file_name = file_name->toPlainText();

        if(text_file_name.isEmpty()) {
            status->showMessage("Введите название файла!",5000);
            return;
        }

        QRegularExpression forbidden_chars("\\[]{}%^:@!;',()-+&?*№=`~|/<>");

        if(text_file_name.contains(forbidden_chars)) {
            status->showMessage("Название файла не должно содержать посторонние знаки",5000);
            return;
        }

        QString corrected_file_name;

        int find_index = text_file_name.lastIndexOf('.');

        if(find_index == -1) {
            corrected_file_name = text_file_name + "." + set_type_image;
        } else {
            corrected_file_name = text_file_name.left(find_index + 1) + set_type_image;
        }

        if(QFile::exists(corrected_file_name)) {
            status->showMessage("Файл уже существует",5000);
            return;
        }

        QString desktop_path = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);

        QString full_path = desktop_path + "/" + corrected_file_name;

        QFile realise_file(full_path);

        if(!realise_file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            status->showMessage("Ошибка создания файла: " + text_file_name);
            return;
        }

        realise_file.close();
        create_file = true;
    });

    QObject::connect(button_box,&QDialogButtonBox::accepted,this,&CreateInFormatWindow::on_ok_clicked);
    QObject::connect(button_box,&QDialogButtonBox::rejected,this,&CreateInFormatWindow::on_cancel_clicked);
}
void CreateInFormatWindow::on_ok_clicked() {
    if(is_created()) {
        accept();
        return;
    }

    status->showMessage("Несозданный файл",5000);
}
void CreateInFormatWindow::on_cancel_clicked() {
    reject();
}
bool CreateInFormatWindow::is_created() const {
    return create_file;
}
