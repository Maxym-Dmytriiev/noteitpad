#-------------------------------------------------
#
# Project created by QtCreator 2014-09-08T00:38:46
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = NoteItPad_Editor
TEMPLATE = app


SOURCES += main.cpp\
        editorwindow.cpp \
    aboutwindow.cpp

HEADERS  += editorwindow.h \
    aboutwindow.h

FORMS    += editorwindow.ui \
    aboutwindow.ui

RESOURCES += \
    resources.qrc
