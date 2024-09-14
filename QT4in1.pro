QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# Uncomment the following line if you want to disable deprecated APIs.
# DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    currencyconverter.cpp \
    main.cpp \
    mainwindow.cpp \
    notetaking.cpp \
    passwordmanager.cpp \
    weatherforecast.cpp

HEADERS += \
    currencyconverter.h \
    mainwindow.h \
    notetaking.h \
    passwordmanager.h \
    weatherforecast.h

FORMS += \
    mainwindow.ui

# Include path for OpenSSL headers
INCLUDEPATH += "C:/Program Files/OpenSSL-Win64/include"

# Library path for OpenSSL libraries
LIBS += -L"C:/Program Files/OpenSSL-Win64/lib/VC/x64/MDd" -lssl -lcrypto

# Default rules for deployment
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
