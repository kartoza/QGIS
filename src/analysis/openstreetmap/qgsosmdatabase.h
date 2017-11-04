/***************************************************************************
  qgsosmdatabase.h
  --------------------------------------
  Date                 : January 2013
  Copyright            : (C) 2013 by Martin Dobias
  Email                : wonder dot sk at gmail dot com
 ***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef OSMDATABASE_H
#define OSMDATABASE_H

#include <QString>
#include "qgis_sip.h"
#include <QStringList>

#include "qgsosmbase.h"

#include "qgsgeometry.h"
#include "qgis_analysis.h"

class QgsOSMNodeIterator;
class QgsOSMWayIterator;

typedef QPair<QString, int> QgsOSMTagCountPair;

/**
 * \ingroup analysis
 * Class that encapsulates access to OpenStreetMap data stored in a database
 * previously imported from XML file.
 *
 * Internal database structure consists of the following tables:
 * - nodes
 * - nodes_tags
 * - ways
 * - ways_tags
 * - ways_nodes
 *
 * The topology representation can be translated to simple features representation
 * using exportSpatiaLite() method into SpatiaLite layers (tables). These can be
 * easily used in QGIS like any other layers.
 */
class ANALYSIS_EXPORT QgsOSMDatabase
{
  public:
    explicit QgsOSMDatabase( const QString &dbFileName = QString() );
    ~QgsOSMDatabase();

    //! QgsOSMDatabase cannot be copied.
    QgsOSMDatabase( const QgsOSMDatabase &rh ) = delete;
    //! QgsOSMDatabase cannot be copied.
    QgsOSMDatabase &operator=( const QgsOSMDatabase &rh ) = delete;

    //! Setter for the SpatiaLite database.
    void setFileName( const QString &dbFileName ) { mDbFileName = dbFileName; }
    QString filename() const { return mDbFileName; }
    bool isOpen() const;

    bool open();
    bool close();

    QString errorString() const { return mError; }

    // data access

    int countNodes() const;
    int countWays() const;

    //! \note not available in Python bindings
    QgsOSMNodeIterator listNodes() const SIP_SKIP;

    //! \note not available in Python bindings
    QgsOSMWayIterator listWays() const SIP_SKIP;

    QgsOSMNode node( QgsOSMId id ) const;
    QgsOSMWay way( QgsOSMId id ) const;
    //OSMRelation relation( OSMId id ) const;

    QgsOSMTags tags( bool way, QgsOSMId id ) const;

    /**
     * \note not available in Python bindings
     * SIP does not seem to handle this return type - strange
     */
    QList<QgsOSMTagCountPair> usedTags( bool ways ) const SIP_SKIP;

    QgsPolyline wayPoints( QgsOSMId id ) const;

    // export to SpatiaLite

    enum ExportType { Point, Polyline, Polygon };
    bool exportSpatiaLite( ExportType type, const QString &tableName,
                           const QStringList &tagKeys = QStringList(),
                           const QStringList &noNullTagKeys = QStringList() );

  protected:
    bool prepareStatements();
    int runCountStatement( const char *sql ) const;

    /**
     * \note not available in Python bindings
     */
    void deleteStatement( sqlite3_stmt *&stmt ) SIP_SKIP;

    void exportSpatiaLiteNodes( const QString &tableName, const QStringList &tagKeys, const QStringList &notNullTagKeys = QStringList() );
    void exportSpatiaLiteWays( bool closed, const QString &tableName, const QStringList &tagKeys, const QStringList &notNullTagKeys = QStringList() );
    bool createSpatialTable( const QString &tableName, const QString &geometryType, const QStringList &tagKeys );
    bool createSpatialIndex( const QString &tableName );

    QString quotedIdentifier( QString id );
    QString quotedValue( QString value );

  private:

#ifdef SIP_RUN
    QgsOSMDatabase( const QgsOSMDatabase &rh );
#endif

    //! database file name
    QString mDbFileName;

    QString mError;

    //! pointer to sqlite3 database that keeps OSM data
    sqlite3 *mDatabase = nullptr;

    sqlite3_stmt *mStmtNode = nullptr;
    sqlite3_stmt *mStmtNodeTags = nullptr;
    sqlite3_stmt *mStmtWay = nullptr;
    sqlite3_stmt *mStmtWayNode = nullptr;
    sqlite3_stmt *mStmtWayNodePoints = nullptr;
    sqlite3_stmt *mStmtWayTags = nullptr;

};


/**
 * \ingroup analysis
 * Encapsulate iteration over table of nodes/
 * \note not available in Python bindings
*/
#ifndef SIP_RUN
class ANALYSIS_EXPORT QgsOSMNodeIterator // clazy:exclude=rule-of-three
{
  public:
    ~QgsOSMNodeIterator();

    QgsOSMNode next();
    void close();

  protected:

    /**
     * \note not available in Python bindings
     */
    QgsOSMNodeIterator( sqlite3 *handle ) SIP_SKIP;

    sqlite3_stmt *mStmt = nullptr;

    friend class QgsOSMDatabase;

};
#endif // SIP_RUN



/**
 * \ingroup analysis
 * Encapsulate iteration over table of ways
 * \note not available in Python bindings
 */
#ifndef SIP_RUN
class ANALYSIS_EXPORT QgsOSMWayIterator // clazy:exclude=rule-of-three
{
  public:
    ~QgsOSMWayIterator();

    QgsOSMWay next();
    void close();

  protected:

    /**
     * \note not available in Python bindings
     */
    QgsOSMWayIterator( sqlite3 *handle ) SIP_SKIP;

    sqlite3_stmt *mStmt = nullptr;

    friend class QgsOSMDatabase;

};
#endif // SIP_RUN



#endif // OSMDATABASE_H
