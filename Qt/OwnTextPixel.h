#ifndef OWNTEXTPIXEL_H
#define OWNTEXTPIXEL_H
#include "QDialog"
#include "QDialogButtonBox"
#include "QVBoxLayout"
#include "QPushButton"
#include "QString"
#include "QStatusBar"
#include "QLineEdit"

class OwnTextPixel : public QDialog {
    QLineEdit* text_pixel;
    QPushButton* create_pixel_button;
    QStatusBar* status;
    QDialogButtonBox* button_box;
    QString pixel;
public:
    OwnTextPixel(QDialog* parent = nullptr);
    QString get_text_pixel() const;
private:
    void set_text_pixel(QString _pixel);
private slots:
    void on_button_clicked();
    void on_ok_clicked();
    void on_cancel_clicked();
};

#endif // OWNTEXTPIXEL_H
