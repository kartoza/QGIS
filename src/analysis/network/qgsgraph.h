/***************************************************************************
  qgsgraph.h
  --------------------------------------
  Date                 : 2011-04-01
  Copyright            : (C) 2010 by Yakushev Sergey
  Email                : YakushevS <at> list.ru
****************************************************************************
*                                                                          *
*   This program is free software; you can redistribute it and/or modify   *
*   it under the terms of the GNU General Public License as published by   *
*   the Free Software Foundation; either version 2 of the License, or      *
*   (at your option) any later version.                                    *
*                                                                          *
***************************************************************************/

/*
 * This file describes the built-in QGIS classes for modeling a mathematical graph.
 * Vertices are identified by their geographic coordinates and have no additional
 * properties. Number of strategies for calculating edge cost is not limited.
 * Graph may have incidence edges.
 *
 * \file qgsgraph.h
 */

#ifndef QGSGRAPH_H
#define QGSGRAPH_H

#include <QList>
#include <QVector>
#include <QVariant>

#include "qgspointxy.h"
#include "qgis_analysis.h"

class QgsGraphVertex;

/**
 * \ingroup analysis
 * \class QgsGraphEdge
 * \since QGIS 3.0
 * \brief This class implements a graph edge
 */
class ANALYSIS_EXPORT QgsGraphEdge
{
  public:

    /**
     * Constructor for QgsGraphEdge.
     */
    QgsGraphEdge() = default;

    /**
     * Returns edge cost calculated using specified strategy
     * \param strategyIndex strategy index
     */
    QVariant cost( int strategyIndex ) const;

    /**
     * Returns array of available strategies
     */
    QVector< QVariant > strategies() const;

    /**
     * Returns index of the outgoing vertex
     */
    int outVertex() const;

    /**
     * Returns index of the incoming vertex
     */
    int inVertex() const;

  private:

    QVector< QVariant > mStrategies;

    int mOut = 0;
    int mIn = 0;

    friend class QgsGraph;
};


typedef QList< int > QgsGraphEdgeIds;

/**
 * \ingroup analysis
 * \class QgsGraphVertex
 * \brief This class implements a graph vertex
 */
class ANALYSIS_EXPORT QgsGraphVertex
{
  public:

    /**
     * Default constructor. It is needed for Qt's container, e.g. QVector
     */
    QgsGraphVertex() {}

    /**
     * This constructor initializes QgsGraphVertex object and associates a vertex with a point
     */

    QgsGraphVertex( const QgsPointXY &point );

    /**
     * Returns outgoing edges ids
     */
    QgsGraphEdgeIds outEdges() const;

    /**
     * Return incoming edges ids
     */
    QgsGraphEdgeIds inEdges() const;

    /**
     * Returns point associated with graph vertex
     */
    QgsPointXY point() const;

  private:
    QgsPointXY mCoordinate;
    QgsGraphEdgeIds mOutEdges;
    QgsGraphEdgeIds mInEdges;

    friend class QgsGraph;
};

/**
 * \ingroup analysis
 * \class QgsGraph
 * \brief Mathematical graph representation
 */

class ANALYSIS_EXPORT QgsGraph
{
  public:

    /**
     * Constructor for QgsGraph.
     */
    QgsGraph() = default;

    // Graph constructing methods

    /**
     * Add a vertex to the graph
     */
    int addVertex( const QgsPointXY &pt );

    /**
     * Add an edge to the graph
     */
    int addEdge( int outVertexIdx, int inVertexIdx, const QVector< QVariant > &strategies );

    /**
     * Returns number of graph vertices
     */
    int vertexCount() const;

    /**
     * Returns vertex at given index
     */
    const QgsGraphVertex &vertex( int idx ) const;

    /**
      * Returns number of graph edges
      */
    int edgeCount() const;

    /**
     * Returns edge at given index
     */
    const QgsGraphEdge &edge( int idx ) const;

    /**
     * Find vertex by associated point
     * \returns vertex index
     */
    int findVertex( const QgsPointXY &pt ) const;

  private:
    QVector<QgsGraphVertex> mGraphVertices;

    QVector<QgsGraphEdge> mGraphEdges;
};

#endif // QGSGRAPH_H
