#include "include/Dialogs/PdfActionsWindow.h"

PDFActionsWindow::PDFActionsWindow(QWidget *parent, QString type_action, QGraphicsScene* _scene, QString _page_size)
    : QDialog(parent), set_type_action(type_action), scene(_scene), page_size(_page_size) {

    setWindowTitle("Диалоговое окно");
    setFixedSize(300,300);
    setStyleSheet("background-color: white; color: black;");

    QVBoxLayout* vertical_layout = new QVBoxLayout(this);
    vertical_layout->setAlignment(Qt::AlignCenter);
    vertical_layout->setSpacing(10);

    status = new QStatusBar();

    action_button = new QPushButton(set_type_action);
    action_button->setStyleSheet("background-color: blue; color: white;");

    button_box = new QDialogButtonBox(
        QDialogButtonBox::Cancel | QDialogButtonBox::Ok,this);

    button_box->setCenterButtons(true);
    button_box->setStyleSheet("background-color: black; color: white;");

    vertical_layout->addWidget(action_button);
    vertical_layout->addWidget(button_box);
    vertical_layout->addWidget(status);

    connect(action_button,&QPushButton::clicked,this,&PDFActionsWindow::on_button_clicked);
    connect(button_box,&QDialogButtonBox::accepted,this,&PDFActionsWindow::on_ok_clicked);
    connect(button_box,&QDialogButtonBox::rejected,this,&PDFActionsWindow::on_cancel_clicked);
}
void PDFActionsWindow::on_button_clicked() {
    QString file_path = QFileDialog::getSaveFileName(this,
                                                     set_type_action,
                                                     "",
                                                     "Файлы (*.pdf)");

    if(file_path.isEmpty()) {
        status->showMessage("Неизвестный файл",5000);
        return;
    }

    if(!file_path.endsWith("pdf",Qt::CaseInsensitive)) {
        if(file_path.contains('.')) {
            QStringList divide_file_path = file_path.split('.');
            file_path.replace(divide_file_path[1],"pdf");
        } else {
            file_path += ".pdf";
        }
    }

    if(set_type_action == "Экспорт") set_export(file_path);
    if(set_type_action == "Импорт") set_import(file_path);
}
void PDFActionsWindow::set_export(QString& file_path) {
    QPdfWriter pdf_writer(file_path);

    QStringList divide_page_size = page_size.split('x');

    QSizeF set_page_size;

    if(divide_page_size.size() != 2) {
        set_page_size = QSizeF(800,600);
    } else {

        bool converted_width = false, converted_height = false;

        int w = divide_page_size[0].toInt(&converted_width);
        int h = divide_page_size[1].toInt(&converted_height);

        set_page_size = QSizeF(w,h);
    }

    QPageSize configure_page_size(set_page_size,QPageSize::Point,"Custom");

    pdf_writer.setPageSize(configure_page_size);
    pdf_writer.setResolution(300);

    QPainter painter(&pdf_writer);
    scene->render(&painter);
    painter.end();

    _export = true;
}
void PDFActionsWindow::set_import(QString& file_path) {
    QPdfDocument pdf_doc;

    QPdfDocument::Error error = pdf_doc.load(file_path);

    if(error != QPdfDocument::Error::None) {
        status->showMessage("Не удалось открыть PDF-файл",5000);
        return;
    }

    QSize page_point_size = pdf_doc.pagePointSize(0).toSize();
    QImage image = pdf_doc.render(0,page_point_size);

    if(image.isNull()) {
        status->showMessage("Не удалось считать изображение",5000);
    }

    QPixmap pixmap = QPixmap::fromImage(image);

    _import = true;
    set_pixmap_item(pixmap);
}
void PDFActionsWindow::set_pixmap_item(QPixmap &_pixmap) {
    QGraphicsPixmapItem* _pixmap_item = new QGraphicsPixmapItem(_pixmap);

    if(_pixmap.width() > 800 || _pixmap.height() > 500) {
        _pixmap_item->setScale(0.5);
    }

    _pixmap_item->setFlag(QGraphicsItem::ItemIsMovable);
    _pixmap_item->setFlag(QGraphicsItem::ItemIsSelectable);
    _pixmap_item->setFlag(QGraphicsItem::ItemIsFocusable);

    pixmap_item = _pixmap_item;
}
QGraphicsPixmapItem* PDFActionsWindow::get_pixmap_item() const {
    return pixmap_item;
}
bool PDFActionsWindow::is_exported() const {
    return _export;
}
bool PDFActionsWindow::is_imported() const {
    return _import;
}
void PDFActionsWindow::on_ok_clicked() {
    accept();
}
void PDFActionsWindow::on_cancel_clicked() {
    reject();
}
