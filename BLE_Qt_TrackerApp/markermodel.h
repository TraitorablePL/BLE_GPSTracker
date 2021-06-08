#ifndef MARKERMODEL_H
#define MARKERMODEL_H

#include <QAbstractListModel>
#include <QGeoCoordinate>
#include "coordinateparser.h"
#include <iostream>

class MarkerModel : public QAbstractListModel
{
    Q_OBJECT

public:
    using QAbstractListModel::QAbstractListModel;
    enum MarkerRoles{positionRole = Qt::UserRole + 1};

//    Q_INVOKABLE void addMarker(const QGeoCoordinate &coordinate){
//        beginInsertRows(QModelIndex(), rowCount(), rowCount());
//        m_coordinates.append(coordinate);
//        endInsertRows();
//    }

    Q_INVOKABLE void addMarker(const QGeoCoordinate &coordinate){
        Q_UNUSED(coordinate);
//        static bool a = false;
//        if(!a) {
//            a = true;
            CoordinateParser p("GPS_Coords.txt");
            std::cout << rowCount() << std::endl;
            beginInsertRows(QModelIndex(), 0, rowCount());
            m_coordinates = p.getCoordList();
            endInsertRows();
//        } else {
//            for (int i = 0; i < m_coordinates.size(); ++i)
//                 std::cout << qPrintable(m_coordinates.at(i).toString(QGeoCoordinate::Degrees)) << std::endl;
//        }
    }

    int rowCount(const QModelIndex &parent = QModelIndex()) const override{
        Q_UNUSED(parent)
        return m_coordinates.count();
    }

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override{
        std::cout << "row: " << index.row() << " col: " << index.column() << " role: " << role << std::endl;
        if (index.row() < 0 || index.row() >= m_coordinates.count())
            return QVariant();
        if(role== MarkerModel::positionRole)
            return QVariant::fromValue(m_coordinates[index.row()]);
        return QVariant();
    }

    QHash<int, QByteArray> roleNames() const{
        QHash<int, QByteArray> roles;
        roles[positionRole] = "position";
        return roles;
    }


private:
    QList<QGeoCoordinate> m_coordinates;

};

#endif // MARKERMODEL_H
