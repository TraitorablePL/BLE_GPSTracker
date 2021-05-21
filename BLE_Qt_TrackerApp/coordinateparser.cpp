#include "coordinateparser.h"
#include <iostream>
#include <QDir>

CoordinateParser::CoordinateParser(const QString &name) : file(name), coordinates_list()
{
    ParseCoords();
}

void CoordinateParser::ParseCoords()
{
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        return;
    }
    if (!file.exists()) {
        return;
    }

    while (!file.atEnd()) {
        QString line = file.readLine();
        coordinates_list.append(ReadCoordsFromString(line));
    }
}

QGeoCoordinate CoordinateParser::ReadCoordsFromString(const QString &line)
{
    QStringList coord_stringlist = line.split(' ');
    return QGeoCoordinate(coord_stringlist[0].toDouble(), coord_stringlist[1].toDouble());
}

QList<QGeoCoordinate> CoordinateParser::getCoordList()
{
    return coordinates_list;
}
