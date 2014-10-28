#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QMovie>
#include <QLabel>
#include <QTimer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void closeEvent(QCloseEvent *);

   void  init();
   void getHtmlSogouUpdateContent(QString url);
public slots:
   void detectNetwork();

private:
    Ui::MainWindow *ui;
    QString updateContent;
    QString updateVersion;
    bool updateIsOK;
    bool netWorkIsOK;
    QTimer * Timer;
    QMovie * movie;
    QLabel *label_gif;
    QLabel *label_prompt;
};

#endif // MAINWINDOW_H
