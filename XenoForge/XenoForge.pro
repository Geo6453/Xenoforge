QT     += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    clickablelabel.cpp \
    jsonmanager.cpp \
    main.cpp \
    mainwindow.cpp \
    settingsdialog.cpp

HEADERS += \
    clickablelabel.h \
    jsonmanager.h \
    mainwindow.h \
    settingsdialog.h

FORMS +=

TRANSLATIONS += \
    XenoForge_fr_FR.ts

CONFIG += lrelease
CONFIG += embed_translations

RC_ICONS = app_icon.ico

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc

# Copy resources during post-build
win32
{
    COPIES += resources
    resources.files = $$files(../data/*)
    resources.path = $$OUT_PWD/release/data
    QMAKE_EXTRA_TARGETS += resources
}
