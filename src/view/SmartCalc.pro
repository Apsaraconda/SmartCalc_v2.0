QT       += core gui
QT    += widgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../controller.cc \
    ../model/model.cc \
    ../model/brackets_check.cc \
    ../model/calculate.cc \
    ../model/delete_button.cc \
    ../model/input_translator.cc \
    ../model/insert_x.cc \
    ../model/polish_translator.cc \
    main.cc \
    view.cc \
    plot_window.cc \
    qcustomplot.cpp

HEADERS += \
    ../controller.h \
    ../model.h \
    ../model/calculator.h \
    view.h \
    plot_window.h \
    qcustomplot.h

FORMS += \
    view.ui \
    plot_window.ui

CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
