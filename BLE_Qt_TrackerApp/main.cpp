#include "markermodel.h"
#include "coordinateparser.h"

#include <QQmlApplicationEngine>
#include <QApplication>
#include <QQuickWidget>
#include <QQmlContext>
#include <iostream>
#include <QMenuBar>
#include <QTabWidget>


int main(int argc, char *argv[])
{
    QGeoCoordinate ge;
    QApplication a(argc, argv);
    QQuickWidget w;
    MarkerModel model;
    w.rootContext()->setContextProperty("markerModel", &model);
    model.addMarker(ge);
    w.setSource(QUrl(QStringLiteral("qrc:/main.qml")));
    w.show();

    return a.exec();
}
