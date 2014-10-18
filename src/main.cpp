#include "mainwindow.h"
#include <QApplication>

#include <QString>
#include <QDebug>
#include <QApplication>
#include <QTextCodec>
#include <qtextstream.h>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QTextCodec::setCodecForTr(QTextCodec::codecForLocale());
    QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    QTranslator translator;
    QString locale = QLocale::system().name();
    if(locale == "zh_CN") {
        if (translator.load("/usr/share/ubuntukylin-feedback/ubuntukylin_feedback_zh_CN.qm") == false)
             qDebug() << "load ubuntukylin_feedback_zh_CN.qm error.";
    }
    QApplication app(argc, argv);
    app.installTranslator(&translator);
    app.setApplicationName("ubuntukylin-feedback");

    MainWindow w;
    w.show();

    return app.exec();
}
