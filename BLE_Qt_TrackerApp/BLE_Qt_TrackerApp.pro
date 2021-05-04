QT += qml network quick positioning location

SOURCES += main.cpp

RESOURCES += qml.qrc

# TARGET = qml_location_mapviewer
# TEMPLATE = app

# Workaround for QTBUG-38735
QT_FOR_CONFIG += location-private
#qtConfig(geoservices_mapboxgl): QT += sql
#qtConfig(geoservices_osm): QT += concurrent
