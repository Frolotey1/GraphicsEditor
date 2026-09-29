#include "OpenFileWindow.h"

OpenFileWindow::OpenFileWindow(QWidget* parent,QGraphicsScene* _scene)
    : QDialog(parent), scene(_scene) {

    setWindowTitle("Диалоговое окно");
    setStyleSheet("background-color: white; color: black;");
    setFixedSize(300,300);

    QVBoxLayout* vertical_layout = new QVBoxLayout(this);
    vertical_layout->setAlignment(Qt::AlignCenter);
    vertical_layout->setSpacing(10);

    status = new QStatusBar();

    open_file_button = new QPushButton("Открыть файл");
    open_file_button->setStyleSheet("background-color: blue; color: white;");

    button_box = new QDialogButtonBox(
        QDialogButtonBox::Cancel | QDialogButtonBox::Ok, this);

    button_box->setCenterButtons(true);
    button_box->setStyleSheet("background-color: black; color: white;");

    vertical_layout->addWidget(open_file_button);
    vertical_layout->addWidget(button_box);
    vertical_layout->addWidget(status);

    QObject::connect(open_file_button,&QPushButton::clicked,this,&OpenFileWindow::on_button_clicked);
    QObject::connect(button_box,&QDialogButtonBox::accepted,this,&OpenFileWindow::on_ok_clicked);
    QObject::connect(button_box,&QDialogButtonBox::rejected,this,&OpenFileWindow::on_cancel_clicked);
}
void OpenFileWindow::on_button_clicked() {
    QString file_path = QFileDialog::getOpenFileName(this,
                                                     "Открыть изображение"
                                                     "",
                                                     "Изображения (*.jpg, *.png, *svg)");

    if(file_path.isEmpty()) {
        status->showMessage("Неизвестный файл",5000);
        return;
    }

    QPixmap pixmap(file_path);

    if(pixmap.isNull()) {
        status->showMessage("Не удалось загрузить изображение",5000);
        return;
    }

    set_pixmap_item(pixmap);
}
void OpenFileWindow::set_pixmap_item(QPixmap _pixmap) {
    QGraphicsPixmapItem* _pixmap_item = new QGraphicsPixmapItem(_pixmap);

    if(_pixmap.width() > 800 || _pixmap.height() > 500) {
        _pixmap_item->setScale(0.5);
    }

    _pixmap_item->setFlag(QGraphicsItem::ItemIsMovable);
    _pixmap_item->setFlag(QGraphicsItem::ItemIsFocusable);
    _pixmap_item->setFlag(QGraphicsItem::ItemIsSelectable);

    pixmap_item = _pixmap_item;
}
QGraphicsPixmapItem* OpenFileWindow::get_pixmap_item() const {
    return pixmap_item;
}
void OpenFileWindow::on_ok_clicked() {
    if(pixmap_item != nullptr) {
        accept();
        return;
    }

    status->showMessage("Невалидный графический объект",5000);
}
void OpenFileWindow::on_cancel_clicked() {
    reject();
}
