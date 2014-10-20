#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDesktopWidget>
#include <QSettings>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle(tr("ubuntukylin feedback"));
    this->setWindowFlags(Qt::WindowStaysOnTopHint);
    QDesktopWidget* desktop = QApplication::desktop();
    move((desktop->width() - this->width())/2, (desktop->height() - this->height())/2);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_submit_released()
{

}
void MainWindow::closeEvent(QCloseEvent *)
{
    QString tmpPath = "/tmp/";
    QSettings * settings= new QSettings(tmpPath + "ubuntukylin-feedback.conf",QSettings::IniFormat);
    settings->setIniCodec("UTF-8");
    settings->beginGroup("Setting");
    settings->setValue("isRunning",1);
    settings->endGroup();
}
