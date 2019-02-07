#-------------------------------------------------
#
# Project created by QtCreator 2018-06-24T20:39:57
#
#-------------------------------------------------

QT       += core gui opengl network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = parsian-graphical
TEMPLATE = app


SOURCES += main.cpp\
    gltext.cpp \
    soccerview.cpp \
    field_default_constants.cpp \
    field.cpp \
    packet.cpp \
    drawpacket.cpp

HEADERS  += \
    gltext.h \
    soccerview.h \
    timer.h \
    field_default_constants.h \
    geometry.h \
    field.h \
    bbox.h \
    geomalgo.h \
    gvector.h \
    pose.h \
    quaternion.h \
    range.h \
    util.h \
    packet.h \
    drawpacket.h
