#-------------------------------------------------
#
# Project created by QtCreator 2017-07-11T09:32:00
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DecisionTool
TEMPLATE = app

INCLUDEPATH += src/
INCLUDEPATH += depend/

SOURCES += src/main.cpp\
        src/decisiontool.cpp\
        depend/mylcm_lidarObjInfor.c\
        depend/mylcm_myBroadcast.c\
        depend/Point.c\
        depend/Trajectory.c\
        depend/TrajectoryFrame.c \
        src/collisionweiget.cpp \
    src/data_center.cpp

HEADERS  += src/decisiontool.h\
        depend/mylcm_lidarObjInfor.h\
        depend/mylcm_myBroadcast.h\
        depend/Point.h\
        depend/Trajectory.h\
        depend/TrajectoryFrame.h\
        src/collisionweiget.h \
    src/data_center.h

FORMS    += decisiontool.ui

LIBS += -llcm
