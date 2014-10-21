#-------------------------------------------------
#
# Project created by QtCreator 2014-10-18T10:24:04
#
#-------------------------------------------------

ARCH      = x86

inst1.files += ubuntukylin_feedback.png
inst1.path = /usr/share/pixmaps
inst2.files += ubuntukylin-feedback.desktop
inst2.path = /usr/share/applications
inst3.files += po/ubuntukylin_feedback_zh_CN.qm
inst3.path = /usr/share/ubuntukylin-feedback

target.source += $$TARGET
target.path = /usr/bin
INSTALLS += inst1 \
    inst2 \
    inst3 \
    target
QT       += core gui
LIBS += -lcurl
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ubuntukylin-feedback
TEMPLATE = app


SOURCES += src/main.cpp \
    src/mainwindow.cpp \
    src/curl_post.cpp

HEADERS  += src/mainwindow.h \
    src/curl_post.h

FORMS    += src/mainwindow.ui
