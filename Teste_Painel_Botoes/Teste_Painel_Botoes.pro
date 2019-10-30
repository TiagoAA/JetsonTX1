#-------------------------------------------------
#
# Project created by QtCreator 2019-10-22T20:44:15
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Teste_Painel_Botoes
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    class_jetson_buttons.cpp \
    jetsonGPIO.cpp

HEADERS  += mainwindow.h \
    class_jetson_buttons.h \
    jetsonGPIO.h

FORMS    += mainwindow.ui
