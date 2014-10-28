#include "mywebpage.h"
#include <QDebug>
#include <QMessageBox>
#include <QMainWindow>
#include <QSettings>
myWebPage::myWebPage(QMainWindow *p_window,QWidget *parent) :
    QWebPage(parent)
{
    window= p_window;
}
void myWebPage::javaScriptAlert(QWebFrame *originatingFrame, const QString &msg)
{
    QMessageBox::warning(window, "警告",msg, QMessageBox::Yes , QMessageBox::Yes);
    if(msg == "反馈信息已成功提交，谢谢！")
    {
        window->close();
        QString tmpPath = "/tmp/";
        QSettings * settings= new QSettings(tmpPath + "ubuntukylin-feedback.conf",QSettings::IniFormat);
        settings->setIniCodec("UTF-8");
        settings->beginGroup("Setting");
        settings->setValue("isRunning",1);
        settings->endGroup();
    }
}
