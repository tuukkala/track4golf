#-------------------------------------------------
#
# Project created by QtCreator 2012-04-15T11:42:17
#
#-------------------------------------------------

QT       += sql testlib

QT       -= gui

TARGET = testdbmanager
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

include(../domain/domain.pri)

SOURCES += testdbmanager.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

OTHER_FILES += \
    qtc_packaging/debian_harmattan/rules \
    qtc_packaging/debian_harmattan/README \
    qtc_packaging/debian_harmattan/manifest.aegis \
    qtc_packaging/debian_harmattan/copyright \
    qtc_packaging/debian_harmattan/control \
    qtc_packaging/debian_harmattan/compat \
    qtc_packaging/debian_harmattan/changelog
