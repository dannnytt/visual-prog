QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += $$PWD/include

SOURCES += \
    src/authorwindow.cpp \
    src/clicked-label.cpp \
    src/input_area-window.cpp \
    src/main.cpp \
    src/mainwindow.cpp

HEADERS += \
    include/authorwindow.h \
    include/clicked-label.h \
    include/input_area-window.h \
    include/mainwindow.h \
    include/shape.h


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
