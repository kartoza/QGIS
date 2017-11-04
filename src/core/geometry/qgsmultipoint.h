/***************************************************************************
                        qgsmultipoint.h
  -------------------------------------------------------------------
Date                 : 29 Oct 2014
Copyright            : (C) 2014 by Marco Hugentobler
email                : marco.hugentobler at sourcepole dot com
 ***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef QGSMULTIPOINTV2_H
#define QGSMULTIPOINTV2_H

#include "qgis_core.h"
#include "qgis.h"
#include "qgsgeometrycollection.h"

/**
 * \ingroup core
 * \class QgsMultiPointV2
 * \brief Multi point geometry collection.
 * \since QGIS 2.10
 */
class CORE_EXPORT QgsMultiPointV2: public QgsGeometryCollection
{
  public:
    QgsMultiPointV2();

    QString geometryType() const override;
    QgsMultiPointV2 *clone() const override SIP_FACTORY;
    QgsMultiPointV2 *toCurveType() const override SIP_FACTORY;
    bool fromWkt( const QString &wkt ) override;
    void clear() override;
    QDomElement asGML2( QDomDocument &doc, int precision = 17, const QString &ns = "gml" ) const override;
    QDomElement asGML3( QDomDocument &doc, int precision = 17, const QString &ns = "gml" ) const override;
    QString asJSON( int precision = 17 ) const override;
    int nCoordinates() const override;
    bool addGeometry( QgsAbstractGeometry *g SIP_TRANSFER ) override;
    bool insertGeometry( QgsAbstractGeometry *g SIP_TRANSFER, int index ) override;
    QgsAbstractGeometry *boundary() const override SIP_FACTORY;

#ifndef SIP_RUN

    /**
     * Cast the \a geom to a QgsLineString.
     * Should be used by qgsgeometry_cast<QgsLineString *>( geometry ).
     *
     * \note Not available in Python. Objects will be automatically be converted to the appropriate target type.
     * \since QGIS 3.0
     */
    inline const QgsMultiPointV2 *cast( const QgsAbstractGeometry *geom ) const
    {
      if ( geom && QgsWkbTypes::flatType( geom->wkbType() ) == QgsWkbTypes::MultiPoint )
        return static_cast<const QgsMultiPointV2 *>( geom );
      return nullptr;
    }
#endif
  protected:

    bool wktOmitChildType() const override;

};

// clazy:excludeall=qstring-allocations

#endif // QGSMULTIPOINTV2_H
