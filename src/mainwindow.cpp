#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "curl_post.h"
#include <QDesktopWidget>
#include <QSettings>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle(tr("ubuntukylin feedback"));
    this->setWindowFlags(Qt::WindowStaysOnTopHint);
    QDesktopWidget* desktop = QApplication::desktop();
    move((desktop->width() - this->width())/2, (desktop->height() - this->height())/2);
    ui->lineEdit_name->setFocus();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_submit_released()
{
    QString suggestion_info;
    suggestion_info.append(ui->textEdit_suggestion->toPlainText());
    if(ui->lineEdit_name->text()=="")
    {
        QMessageBox::warning(this, "warning", tr("Please input your name !"), QMessageBox::Yes , QMessageBox::Yes);
        return;
    }
    if(ui->lineEdit_email->text()=="")
    {
        QMessageBox::warning(this, "warning", tr("Please input your Email !"), QMessageBox::Yes , QMessageBox::Yes);
        return;
    }
    if(suggestion_info =="")
    {
        QMessageBox::warning(this, "warning", tr("Please input your suggestion !"), QMessageBox::Yes , QMessageBox::Yes);
        return;
    }
    QString feedbackInfo = "name="+ui->lineEdit_name->text()+"&email="+ui->lineEdit_email->text()+
            "&location="+ui->lineEdit_location->text()+"&telephone="+ui->lineEdit_telephone->text()+
            "&suggestion="+suggestion_info;
    sendPost(feedbackInfo);
    this->close();
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
