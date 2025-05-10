QT += core gui sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

INCLUDE_DIR = $$PWD/include
SRC_DIR = $$PWD/src
RESOURCES_DIR = $$PWD/resources

INCLUDEPATH += \
    $$INCLUDE_DIR \
    $$INCLUDE_DIR/ui

HEADERS += \
    $$INCLUDE_DIR/ui/mainwindow.h \
    $$INCLUDE_DIR/ui/task_dialog.h

SOURCES += \
    $$SRC_DIR/main.cpp \
    $$SRC_DIR/ui/mainwindow.cpp \
    $$SRC_DIR/ui/task_dialog.cpp

RESOURCES += $$RESOURCES_DIR/resources.qrc

# Default rules for deployment
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

