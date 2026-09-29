#ifndef OPENFILEWINDOW_H
#define OPENFILEWINDOW_H
#include "QDialog"
#include "QDialogButtonBox"
#include "QPushButton"
#include "QVBoxLayout"
#include "QStatusBar"
#include "QFileDialog"
#include "QPixmap"
#include "QGraphicsPixmapItem"

class OpenFileWindow : public QDialog {
public:
    OpenFileWindow(QWidget* parent,QGraphicsScene* _scene);
    QGraphicsPixmapItem* get_pixmap_item() const;
private:
    void set_pixmap_item(QPixmap _pixmap);
private slots:
    void on_button_clicked();
    void on_ok_clicked();
    void on_cancel_clicked();
private:
    QPushButton* open_file_button = nullptr;
    QStatusBar* status = nullptr;
    QDialogButtonBox* button_box = nullptr;
    QGraphicsScene* scene = nullptr;
    QGraphicsPixmapItem* pixmap_item = nullptr;
};

#endif // OPENFILEWINDOW_H
