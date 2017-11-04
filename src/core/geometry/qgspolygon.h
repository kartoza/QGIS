/***************************************************************************
                         qgspolygon.h
                         -------------------
    begin                : September 2014
    copyright            : (C) 2014 by Marco Hugentobler
    email                : marco at sourcepole dot ch
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef QGSPOLYGONV2_H
#define QGSPOLYGONV2_H

#include "qgis_core.h"
#include "qgis.h"
#include "qgscurvepolygon.h"

/**
 * \ingroup core
 * \class QgsPolygonV2
 * \brief Polygon geometry type.
 * \since QGIS 2.10
 */
class CORE_EXPORT QgsPolygonV2: public QgsCurvePolygon
{
  public:
    QgsPolygonV2();

    QString geometryType() const override;
    QgsPolygonV2 *clone() const override SIP_FACTORY;
    void clear() override;
    bool fromWkb( QgsConstWkbPtr &wkb ) override;
    QByteArray asWkb() const override;
    QgsPolygonV2 *surfaceToPolygon() const override SIP_FACTORY;

    /**
     * Returns the geometry converted to the more generic curve type QgsCurvePolygon
     \returns the converted geometry. Caller takes ownership*/
    QgsCurvePolygon *toCurveType() const override SIP_FACTORY;

    void addInteriorRing( QgsCurve *ring SIP_TRANSFER ) override;
    //overridden to handle LineString25D rings
    void setExteriorRing( QgsCurve *ring SIP_TRANSFER ) override;

    QgsAbstractGeometry *boundary() const override SIP_FACTORY;

    /**
     * Returns the distance from a point to the boundary of the polygon (either the
     * exterior ring or any closer interior rings). The returned distance will be
     * negative if the point lies outside the polygon.
     * \since QGIS 3.0
     */
    double pointDistanceToBoundary( double x, double y ) const;

#ifndef SIP_RUN

    /**
     * Cast the \a geom to a QgsPolygonV2.
     * Should be used by qgsgeometry_cast<QgsPolygonV2 *>( geometry ).
     *
     * \note Not available in Python. Objects will be automatically be converted to the appropriate target type.
     * \since QGIS 3.0
     */
    inline const QgsPolygonV2 *cast( const QgsAbstractGeometry *geom ) const
    {
      if ( !geom )
        return nullptr;

      QgsWkbTypes::Type flatType = QgsWkbTypes::flatType( geom->wkbType() );

      if ( flatType == QgsWkbTypes::Polygon
           || flatType == QgsWkbTypes::Triangle )
        return static_cast<const QgsPolygonV2 *>( geom );
      return nullptr;
    }
#endif
};
#endif // QGSPOLYGONV2_H
