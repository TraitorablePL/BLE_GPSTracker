#include "markermodel.h"

#include <QApplication>
#include <QQuickWidget>
#include <QQmlContext>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QQuickWidget w;
    MarkerModel model;
    w.rootContext()->setContextProperty("markerModel", &model);
    w.setSource(QUrl(QStringLiteral("qrc:/main.qml")));
    w.show();

    return a.exec();
}

//#include <QGuiApplication>
//#include <QQmlApplicationEngine>

//#include "backend.h"

//int main(int argc, char *argv[])
//{
//    QGuiApplication app(argc, argv);

//    qmlRegisterType<BackEnd>("io.qt.examples.backend", 1, 0, "BackEnd");

//    QQmlApplicationEngine engine;
//    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

//    return app.exec();
//}
