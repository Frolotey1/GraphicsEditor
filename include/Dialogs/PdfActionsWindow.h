#ifndef PDFACTIONSWINDOW_H
#define PDFACTIONSWINDOW_H
#include "QDialog"
#include "QDialogButtonBox"
#include "QPushButton"
#include "QVBoxLayout"
#include "QPageSize"
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
public:
    PDFActionsWindow(QWidget* parent,QString type_action,QGraphicsScene* _scene, QString _page_size = "800x600");
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
private:
    QDialogButtonBox* button_box = nullptr;
    QPushButton* action_button = nullptr;
    QStatusBar* status = nullptr;
    QString set_type_action;
    QGraphicsScene* scene = nullptr;
    QGraphicsPixmapItem* pixmap_item = nullptr;
    QString page_size;
    bool _import = false;
    bool _export = false;
};

#endif // PDFACTIONSWINDOW_H
