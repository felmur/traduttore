QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: {
    target.path = /usr/bin/
    doc.files = README.md
    doc.path = /usr/share/$${TARGET}/
    icon.files = icon.png
    icon.path = /usr/share/icons/$${TARGET}/
#    trans.files = *.qm
#    trans.path = /usr/share/$${TARGET}/translations
    desk.path = /usr/share/applications
    desk.files = traduttore.desktop
}

!isEmpty(target.path): INSTALLS += target doc icon desk


RESOURCES += \
    resource.qrc
