QT += core gui widgets opengl openglwidgets
greaterThan(QT_MAJOR_VERSION, 4): QT += core gui widgets opengl openglwidgets
include(QtGifImage/src/gifimage/qtgifimage.pri)
CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../../model/data.cpp \
    ../../controller/controller.cpp \
    ../../model/data_save.cpp \
    ../../model/parser.cpp \
    ../../model/transformer.cpp \
    main.cpp \
    mainwindow.cpp \
    opengl.cpp \
    settings.cpp

HEADERS += \
    ../../model/data.h \
    ../../controller/controller.h \
    ../../model/data_save.h \
    ../../model/parser.h \
    ../../model/transformer.h \
    mainwindow.h \
    opengl.h \
    settings.h

FORMS += \
    mainwindow.ui

LIBS += -lopengl32

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
