QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Run_GMT_CMD.cpp \
    check_gmt_version.cpp \
    gmt_b_option.cpp \
    gmt_custom.cpp \
    gmt_j_option.cpp \
    gmt_psbasemap.cpp \
    gmt_pscoast.cpp \
    gmt_pssac.cpp \
    gmt_pstext.cpp \
    gmt_psxy.cpp \
    gmt_r_option.cpp \
    gmt_set.cpp \
    main.cpp \
    mainwindow.cpp \
    new_ps_file.cpp \
    waiting_thread.cpp

HEADERS += \
    Run_GMT_CMD.h \
    check_gmt_version.h \
    gmt_b_option.h \
    gmt_custom.h \
    gmt_j_option.h \
    gmt_psbasemap.h \
    gmt_pscoast.h \
    gmt_pssac.h \
    gmt_pstext.h \
    gmt_psxy.h \
    gmt_r_option.h \
    gmt_set.h \
    mainwindow.h \
    new_ps_file.h \
    waiting_thread.h

FORMS += \
    check_gmt_version.ui \
    gmt_b_option.ui \
    gmt_custom.ui \
    gmt_j_option.ui \
    gmt_psbasemap.ui \
    gmt_pscoast.ui \
    gmt_pssac.ui \
    gmt_pstext.ui \
    gmt_psxy.ui \
    gmt_r_option.ui \
    gmt_set.ui \
    mainwindow.ui \
    new_ps_file.ui \
    waiting_thread.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
