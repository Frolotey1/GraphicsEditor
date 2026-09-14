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
    QPushButton* save_in_file_button;
    QDialogButtonBox* button_box;
    QStatusBar* status;
    QGraphicsScene* scene;
    bool save = false;
public:
    SaveInFileWindow(QWidget* parent, QGraphicsScene* _scene);
    bool is_saved() const;
private slots:
    void on_button_clicked();
    void on_ok_clicked();
    void on_cancel_clicked();
};

#endif // SAVEINFILEWINDOW_H
