#ifndef OWNGRIDSIZEWINDOW_H
#define OWNGRIDSIZEWINDOW_H
#include "QDialog"
#include "QVBoxLayout"
#include "QDialogButtonBox"
#include "QPushButton"
#include "QLineEdit"
#include "QRegularExpression"
#include "QStatusBar"

class OwnGridSizeWindow : public QDialog {
    QPushButton* accept_grid_button;
    QDialogButtonBox* button_box;
    QStatusBar* status;
    QLineEdit* own_grid_text;
    bool set_accept = false;
public:
    OwnGridSizeWindow(QDialog* parent = nullptr);
    int get_own_grid_size() const;
    bool is_accepted() const;
private slots:
    void on_button_clicked();
    void on_ok_clicked();
    void on_cancel_clicked();
private:
    int own_grid_size;
};

#endif // OWNGRIDSIZEWINDOW_H
