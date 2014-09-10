#ifndef ABOUTWINDOW_H
#define ABOUTWINDOW_H

#include <QDialog>

namespace Ui {
class aboutWindow;
}

class AboutWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AboutWindow(QWidget *parent = 0);
    ~AboutWindow();

private slots:
    void on_btnOpenWebsite_clicked();

    void on_btnOpenWebsite_2_clicked();

private:
    Ui::aboutWindow *ui;
};

#endif // ABOUTWINDOW_H
