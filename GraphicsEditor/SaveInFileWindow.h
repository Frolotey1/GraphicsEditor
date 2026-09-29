#ifndef SAVEINFILEWINDOW_H
#define SAVEINFILEWINDOW_H
#include "QDialog"
#include "QDialogButtonBox"
#include "QPushButton"
#include "QStatusBar"
#include "QFileDialog"
#include "QVBoxLayout"
#include "QGraphicsScene"
#include "QPainter"
#include "QImage"

class SaveInFileWindow : public QDialog {
public:
    SaveInFileWindow(QWidget* parent, QGraphicsScene* _scene, QString graphics_background_color = "white");
    bool is_saved() const;
private slots:
    void on_button_clicked();
    void on_ok_clicked();
    void on_cancel_clicked();
private:
    QPushButton* save_in_file_button = nullptr;
    QDialogButtonBox* button_box = nullptr;
    QStatusBar* status = nullptr;
    QGraphicsScene* scene = nullptr;
    QString set_graphics_background_color;
    bool save = false;
};

#endif // SAVEINFILEWINDOW_H
