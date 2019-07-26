#-------------------------------------------------
#
# Project created by QtCreator 2018-04-07T15:14:21
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CityTrafficSimulator
TEMPLATE = app

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    RoadUser.cpp \
    Car.cpp \
    Pedestrian.cpp \
    Camera.cpp \
    Controller.cpp \
    cityconstructorwidget.cpp \
    citytrafficsimulatorwidget.cpp \
    ExtendedGraphicsView.cpp \
    Main.cpp \
    MainWindow.cpp \
    CityObject.cpp \
    StreetElement.cpp \
    Pavement.cpp \
    StraightStreet.cpp \
    TurnStreet.cpp \
    DivisionStreet.cpp \
    CrossingStreet.cpp \
    PedestrianCrossing.cpp \
    TrafficLight.cpp

HEADERS += \
    RoadUser.h \
    Car.h \
    Pedestrian.h \
    Camera.h \
    Controller.h \
    Constants.h \
    ExtendedGraphicsView.h \
    MainWindow.h \
    citytrafficsimulatorwidget.h \
    cityconstructorwidget.h \
    CityObject.h \
    StreetElement.h \
    Pavement.h \
    StraightStreet.h \
    TurnStreet.h \
    DivisionStreet.h \
    CrossingStreet.h \
    PedestrianCrossing.h \
    TrafficLight.h

FORMS += \
    mainwindow.ui

RESOURCES += \
    images.qrc
