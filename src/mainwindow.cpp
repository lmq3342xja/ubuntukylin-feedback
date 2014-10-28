#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "curl_post.h"
#include <QDesktopWidget>
#include <QSettings>
#include <QMessageBox>
#include <QValidator>
#include <QRegExp>
#include <QRegExpValidator>
#include <QtWebKit>
#include <QWebPage>
#include <QDebug>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QTextCodec>
#include "mywebpage.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("优麒麟反馈");
    this->setWindowFlags(Qt::WindowStaysOnTopHint);
    QDesktopWidget* desktop = QApplication::desktop();
    move((desktop->width() - this->width())/2, (desktop->height() - this->height())/2);
    label_gif = new QLabel(this);
    label_prompt = new QLabel(this);
    movie = new QMovie(":/src/222.gif");
    Timer = new QTimer(this);
    //将定时器超时信号与槽(功能函数)联系起来
   connect( Timer, SIGNAL(timeout()), this, SLOT(detectNetwork()) );
    init();
}

void MainWindow::init()
{
    label_gif->setGeometry(220,60,35,35);
    label_prompt->setGeometry(200,110,100,30);
    label_prompt->setText("正在检测网络...");
    label_gif->setMovie(movie);
    movie->start();
    Timer->start(200);
}
void MainWindow::detectNetwork()
{
    Timer->stop();
    getHtmlSogouUpdateContent("http://www.ubuntukylin.com/feedback/sysfb.html");
    if(updateContent=="")
    {
        movie->stop();
        label_gif->hide();
        label_prompt->hide();

        QLabel *label_noNetWork1= new QLabel(this);
        QLabel *label_noNetWork2= new QLabel(this);
        label_noNetWork1->setText("网络连接失败!");
        label_noNetWork2->setText("请确认您的网络通畅后再尝试。");
        label_noNetWork1->setGeometry(200,100,200,20);
        label_noNetWork2->setGeometry(140,130,260,20);
        label_noNetWork1->show();
        label_noNetWork2->show();
    }
    else
    {
        if(netWorkIsOK)//检测有网络
        {
            qDebug()<<"检测有网络";
            movie->stop();
            label_gif->hide();
            label_prompt->hide();
            QWebView *view = new QWebView();
            myWebPage * webPage = new myWebPage(this,view);
            view->setPage(webPage);
            view->load(QUrl("http://www.ubuntukylin.com/feedback/sysfb.html"));
            view->setContextMenuPolicy(Qt::NoContextMenu);

            this->layout()->addWidget(view);
            this->layout()->activate();

        }
    else{//无网络

    }
    }
}

void MainWindow::getHtmlSogouUpdateContent(QString url)
{
    updateContent = "";
    QNetworkAccessManager *manager = new QNetworkAccessManager();
    QNetworkReply *reply = manager->get(QNetworkRequest(QUrl(url)));
    if(reply && reply->error() == QNetworkReply::NoError)
    {
        QTextCodec *codec = QTextCodec::codecForName("utf8");
        //使用utf8编码，这样才可以显示中文
        QEventLoop eventLoop;
        connect(manager, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));
        eventLoop.exec();       //block until finish
        QString all = codec->toUnicode(reply->readAll());
        if(all == "")
            return;
        updateContent = all;
        netWorkIsOK = true;
    }
    else
    {
        netWorkIsOK = false;
    }
    if(reply!=NULL)
    reply->deleteLater();   //最后要释放reply
}

MainWindow::~MainWindow()
{
    delete ui;
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
