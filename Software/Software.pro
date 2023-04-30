#-------------------------------------------------
#
# Project created by QtCreator 2011-10-05T23:59:02
#
#-------------------------------------------------

QT       += core gui
QT      +=  webkit network

CONFIG += qwt

TARGET = Software
TEMPLATE = app


SOURCES += main.cpp\
        xcontrolador.cpp \
    grafica.cpp \
    curve.cpp \
    pidprofesional.cpp \
    file.cpp \
    puertoserie.cpp \
    rs232.c \
    loadedfile.cpp \
    ayuda.cpp

HEADERS  += xcontrolador.h \
    grafica.h \
    curve.h \
    pidprofesional.h \
    file.h \
    puertoserie.h \
    rs232.h \
    loadedfile.h \
    ayuda.h

FORMS    += xcontrolador.ui \
    loadedfile.ui \
    ayuda.ui

RESOURCES += \
    myResource.qrc
