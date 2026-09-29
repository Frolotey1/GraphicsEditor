#include "SaveInFileWindow.h"

SaveInFileWindow::SaveInFileWindow(QWidget * parent,QGraphicsScene* _scene, QString graphics_background_color)
    : QDialog(parent), scene(_scene), set_graphics_background_color(graphics_background_color) {
    setWindowTitle("Диалоговое окно");
    setStyleSheet("background-color: white; color: black;");
    setFixedSize(300,300);

    QVBoxLayout* vertical_layout = new QVBoxLayout(this);
    vertical_layout->setAlignment(Qt::AlignCenter);
    vertical_layout->setSpacing(10);

    status = new QStatusBar();

    save_in_file_button = new QPushButton("Сохранить в файл");
    save_in_file_button->setStyleSheet("background-color: blue; color: white;");

    button_box = new QDialogButtonBox(
        QDialogButtonBox::Cancel | QDialogButtonBox::Ok, this);

    button_box->setCenterButtons(true);
    button_box->setStyleSheet("background-color: black; color: white;");

    vertical_layout->addWidget(save_in_file_button);
    vertical_layout->addWidget(button_box);
    vertical_layout->addWidget(status);

    QObject::connect(save_in_file_button,&QPushButton::clicked,this,&SaveInFileWindow::on_button_clicked);
    QObject::connect(button_box,&QDialogButtonBox::accepted,this,&SaveInFileWindow::on_ok_clicked);
    QObject::connect(button_box,&QDialogButtonBox::rejected,this,&SaveInFileWindow::on_cancel_clicked);
}
void SaveInFileWindow::on_button_clicked() {
    QString file_path = QFileDialog::getSaveFileName(this,
                                                     "Сохранить в файл",
                                                     "",
                                                     "Изображения (*.jpg, *.png, *.svg)");

    if(file_path.isEmpty()) {
        status->showMessage("Неизвестный файл",5000);
        return;
    }

    if(set_graphics_background_color.isEmpty()) {
        status->showMessage("Не удалось считать цвет окна на сцене",5000);
        return;
    }

    QRectF scene_rect = scene->sceneRect();
    QSize scene_size = scene_rect.size().toSize();

    QImage image(scene_size,QImage::Format_ARGB32);

    if(set_graphics_background_color != "white") {
        image.fill(QColor(set_graphics_background_color));
    } else {
        image.fill(Qt::white);
    }

    QPainter painter(&image);
    scene->render(&painter);
    painter.end();

    image.save(file_path);

    save = true;
}
bool SaveInFileWindow::is_saved() const {
    return save;
}
void SaveInFileWindow::on_ok_clicked() {
    if(is_saved()) {
        accept();
        return;
    }

    status->showMessage("Не удалось сохранить изображение",5000);
}
void SaveInFileWindow::on_cancel_clicked() {
    reject();
}
