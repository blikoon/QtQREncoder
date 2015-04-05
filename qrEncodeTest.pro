#-------------------------------------------------
#
# Project created by QtCreator 2015-03-29T17:44:41
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtQREncoder

TEMPLATE = app

#Msvc wasn't finding the "config.h" file in the project dir
#and this includepath takes care of that.

INCLUDEPATH += $$PWD

SOURCES += main.cpp\
    widget.cpp \
    qrencode/bitstream.c \
    qrencode/mask.c \
    qrencode/mmask.c \
    qrencode/mqrspec.c \
    qrencode/qrencode.c \
    qrencode/qrinput.c \
    qrencode/qrspec.c \
    qrencode/rscode.c \
    qrencode/split.c


HEADERS  += widget.h \
    qrencode/bitstream.h \
    qrencode/mask.h \
    qrencode/mmask.h \
    qrencode/mqrspec.h \
    qrencode/qrencode.h \
    qrencode/qrencode_inner.h \
    qrencode/qrinput.h \
    qrencode/qrspec.h \
    qrencode/rscode.h \
    qrencode/split.h \


FORMS    += widget.ui
