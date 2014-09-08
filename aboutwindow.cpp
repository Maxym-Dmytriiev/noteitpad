#include "aboutwindow.h"
#include "ui_aboutwindow.h"
#include <QDesktopServices>
#include <QUrl>

AboutWindow::AboutWindow(QWidget *parent) :
    QDialog(parent, Qt::WindowSystemMenuHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint),
    ui(new Ui::aboutWindow)
{
    ui->setupUi(this);
    setFixedSize(290, 240);
}

AboutWindow::~AboutWindow()
{
    delete ui;
}

void AboutWindow::on_btnOpenWebsite_clicked()
{
    QDesktopServices::openUrl(QUrl("https://bitbucket.org/mdmitriev/noteitpad"));
}
