#include "aboutwindow.h"
#include "ui_aboutwindow.h"
#include <QDesktopServices>
#include <QUrl>

AboutWindow::AboutWindow(QWidget *parent) :
    QDialog(parent, Qt::WindowSystemMenuHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint),
    ui(new Ui::aboutWindow)
{
    ui->setupUi(this);
    setFixedSize(width(), height());
}

AboutWindow::~AboutWindow()
{
    delete ui;
}

void AboutWindow::on_btnOpenBitbucket_clicked()
{
    QDesktopServices::openUrl(QUrl("https://bitbucket.org/mdmitriev/noteitpad"));
}

void AboutWindow::on_btnOpenGithub_clicked()
{
    QDesktopServices::openUrl(QUrl("https://github.com/Maxym-Dmytriiev/noteitpad"));
}
