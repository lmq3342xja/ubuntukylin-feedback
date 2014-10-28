#include "mainwindow.h"
#include <QApplication>

#include <QString>
#include <QDebug>
#include <QApplication>
#include <QTextCodec>
#include <qtextstream.h>
#include <QTranslator>
#include <QSettings>

int isRunning()
{
    QString tmpPath = "/tmp/";
    QSettings * settings= new QSettings(tmpPath + "ubuntukylin-feedback.conf",QSettings::IniFormat);
    settings->setIniCodec("UTF-8");
    settings->beginGroup("Setting");
    int isRunning = settings->value("isRunning",2).toInt();
    return isRunning;
}

int main(int argc, char *argv[])
{
    if (0 == isRunning()) {
        exit(1);
    }
    QTextCodec::setCodecForTr(QTextCodec::codecForLocale());
    QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    QTranslator translator;
    QString locale = QLocale::system().name();
    if(locale == "zh_CN") {
        if (translator.load("/usr/share/ubuntukylin-feedback/ubuntukylin_feedback_zh_CN.qm") == false)
             qDebug() << "load ubuntukylin_feedback_zh_CN.qm error.";
        if (translator.load("/usr/share/qt4/translations/qt_zh_CN.qm")==false)
            qDebug() << "load qt_zh_CN.qm error.";
    }
    QApplication app(argc, argv);
    app.installTranslator(&translator);
    app.setApplicationName("ubuntukylin-feedback");

    QString tmpPath = "/tmp/";
    QSettings * settings= new QSettings(tmpPath + "ubuntukylin-feedback.conf",QSettings::IniFormat);
    settings->setIniCodec("UTF-8");
    settings->beginGroup("Setting");
    settings->setValue("isRunning",0);
    settings->endGroup();
    MainWindow w;
    w.show();

    return app.exec();
}
