QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    dblinkedlist.cpp \
    dblistnode.cpp \
    dynamicarray.cpp \
    expandablelinkedhashtable.cpp \
    hashmap.cpp \
    main.cpp \
    mainwindow.cpp \
    singlenode.cpp

HEADERS += \
    dblinkedlist.h \
    dblistnode.h \
    dynamicarray.h \
    expandablelinkedhashtable.h \
    hashmap.h \
    mainwindow.h \
    singlenode.h
 

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
