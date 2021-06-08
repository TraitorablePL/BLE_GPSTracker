QT += quick
QT += positioning
QT += widgets
QT += quickwidgets
QT += widgets
QT += bluetooth
QT += qml
QT += quickcontrols2

CONFIG += c++11
CONFIG += qmltypes

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        coordinateparser.cpp \
        main.cpp \
        characteristicinfo.cpp \
        device.cpp \
        deviceinfo.cpp \
        serviceinfo.cpp

RESOURCES += qml.qrc

OTHER_FILES +=Main.qml
            MapViewer.qml
            Bluetooth.qml
            Characteristics.qml
            ContactPage.qml
            ConversationPage.qml
            Dialog.qml
            Header.qml
            Label.qml
            MapViewer.qml
            Menu.qml
            Services.qml


# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

QML_IMPORT_NAME = io.qt.examples.backend
QML_IMPORT_MAJOR_VERSION = 1
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    coordinateparser.h \
    markermodel.h \
    characteristicinfo.h \
    device.h \
    deviceinfo.h \
    serviceinfo.h

DISTFILES += \
    Bluetooth.qml \
    Characteristics.qml \
    ContactPage.qml \
    ConversationPage.qml \
    CoordDisp.qml \
    Dialog.qml \
    Header.qml \
    Label.qml \
    Main.qml \
    MapViewer.qml \
    Menu.qml \
    Services.qml
