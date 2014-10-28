#ifndef MYWEBPAGE_H
#define MYWEBPAGE_H

#include <QWebPage>
#include <QMainWindow>
class myWebPage : public QWebPage
{
    Q_OBJECT
public:
    explicit myWebPage(QMainWindow *p_window,QWidget *parent = 0);
    void javaScriptAlert(QWebFrame *originatingFrame, const QString &msg);
    QMainWindow *window;
signals:

public slots:

};

#endif // MYWEBPAGE_H
