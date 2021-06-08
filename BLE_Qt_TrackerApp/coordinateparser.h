#ifndef COORDINATEPARSER_H
#define COORDINATEPARSER_H

#include <QGeoCoordinate>
#include <QFile>

class CoordinateParser
{
public:
    CoordinateParser(const QString &name);
    void ParseCoords();
    QGeoCoordinate ReadCoordsFromString(const QString &line);
    QList<QGeoCoordinate> getCoordList();


private:
    QFile file;
    QList<QGeoCoordinate> coordinates_list;
};

#endif // COORDINATEPARSER_H
