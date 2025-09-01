QT = core
TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG += c++17 cmdline


SOURCES += \
        analista.cpp \
        empleado.cpp \
        gerente.cpp \
        main.cpp \
        programador.cpp

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    analista.h \
    empleado.h \
    gerente.h \
    programador.h
