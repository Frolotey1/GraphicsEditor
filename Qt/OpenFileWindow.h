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
    QPushButton* open_file_button;
    QStatusBar* status;
    QDialogButtonBox* button_box;
    QGraphicsScene* scene;
    QGraphicsPixmapItem* pixmap_item;
public:
    OpenFileWindow(QWidget* parent,QGraphicsScene* _scene);
    QGraphicsPixmapItem* get_pixmap_item() const;
private:
    void set_pixmap_item(QPixmap _pixmap);
private slots:
    void on_button_clicked();
    void on_ok_clicked();
    void on_cancel_clicked();
};

#endif // OPENFILEWINDOW_H
