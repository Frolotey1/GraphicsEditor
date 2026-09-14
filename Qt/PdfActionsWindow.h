#ifndef PDFACTIONSWINDOW_H
#define PDFACTIONSWINDOW_H
#include "QDialog"
#include "QDialogButtonBox"
#include "QPushButton"
#include "QVBoxLayout"
#include "QStatusBar"
#include "QFileDialog"
#include "QFile"
#include "QPdfWriter"
#include "QPdfDocument"
#include "QImage"
#include "QGraphicsPixmapItem"
#include "QGraphicsScene"
#include "QPainter"
#include "QStringList"
#include "QPixmap"

class PDFActionsWindow : public QDialog {
    QDialogButtonBox* button_box;
    QPushButton* action_button;
    QStatusBar* status;
    QString set_type_action;
    QGraphicsScene* scene;
    QGraphicsPixmapItem* pixmap_item;
    bool _import = false;
    bool _export = false;
public:
    PDFActionsWindow(QWidget* parent,QString type_action,QGraphicsScene* _scene);
    bool is_exported() const;
    bool is_imported() const;
    QGraphicsPixmapItem* get_pixmap_item() const;
private:
    void set_export(QString& file_path);
    void set_import(QString& file_path);
    void set_pixmap_item(QPixmap& _pixmap);
private slots:
    void on_button_clicked();
    void on_ok_clicked();
    void on_cancel_clicked();
};

#endif // PDFACTIONSWINDOW_H
