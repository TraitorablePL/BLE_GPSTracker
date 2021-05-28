#include "markermodel.h"
#include "coordinateparser.h"
#include "device.h"

#include <QQmlApplicationEngine>
#include <QApplication>
#include <QQuickWidget>
#include <QQmlContext>
#include <QTabWidget>
#include <QtCore/QLoggingCategory>
#include <QGuiApplication>
#include <QQuickView>
#include <iostream>
#include <QMenuBar>


int main(int argc, char *argv[])
{
    //QLoggingCategory::setFilterRules(QStringLiteral("qt.bluetooth* = true"));

    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    QQmlContext* rootContext = engine.rootContext();

    QGeoCoordinate ge;
    MarkerModel model;
    Device d;
    rootContext->setContextProperty("device", &d);
    rootContext->setContextProperty("markerModel", &model);
    model.addMarker(ge);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return QGuiApplication::exec();
}
