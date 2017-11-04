/***************************************************************************
                          Node.h  -  description
                             -------------------
    copyright            : (C) 2004 by Marco Hugentobler
    email                : mhugent@geo.unizh.ch
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef NODE_H
#define NODE_H

#include "qgspoint.h"
#include "qgis_analysis.h"

#define SIP_NO_FILE

/**
 * \ingroup analysis
 * Node is a class used by Line3D. It represents a node in the single directed linked list. Associated QgsPoint objects are deleted when the node is deleted.
 * \note Not available in Python bindings
*/
class ANALYSIS_EXPORT Node
{
  protected:
    //! Pointer to the QgsPoint object associated with the node
    QgsPoint *mPoint = nullptr;
    //! Pointer to the next Node in the linked list
    Node *mNext = nullptr;
  public:
    Node();
    Node( const Node &n );
    ~Node();
    Node &operator=( const Node &n );
    //! Returns a pointer to the next element in the linked list
    Node *getNext() const;
    //! Returns a pointer to the QgsPoint object associated with the node
    QgsPoint *getPoint() const;
    //! Sets the pointer to the next node
    void setNext( Node *n );
    //! Sets a new pointer to an associated QgsPoint object
    void setPoint( QgsPoint *p );
};

#ifndef SIP_RUN


inline Node::Node()
{

}

inline Node::~Node()
{
  delete mPoint;
}

inline Node *Node::getNext() const
{
  return mNext;
}

inline QgsPoint *Node::getPoint() const
{
  return mPoint;
}

inline void Node::setNext( Node *n )
{
  mNext = n;
}

inline void Node::setPoint( QgsPoint *p )
{
  mPoint = p;
}

#endif
#endif
