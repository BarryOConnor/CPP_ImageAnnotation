#ifndef GRIP_H
#define GRIP_H

#include <QPainterPath>
#include <QGraphicsPathItem>

#include "GraphicsPolygonItem.h"

class GraphicsPolygonItem;
//!  GripHandle class acts as adjustment handles for vectors in the GraphicsPolygonItem.
/*!
  subclasses QGraphicsPathItem and acts as a custom set of handles to adjust the vertices of a shape
*/
class GripHandle: public QGraphicsPathItem
{

public:

    //! Grip Constructor.
    /*!
      the main constructor used by the class
      allows for the addition of a parent and index value#

      \param varIndex the index of the grip (corresponds to the associated point)
      \param varParent pointer to the associated shape so that this class can update the positions of the parent
    */
    GripHandle(int varIndex, GraphicsPolygonItem *varParent);

private:
    //! Hover Enter Event
    /*!
      Highlights the active grip when hovered

      \param *varEvent QGraphicsSceneHoverEvent object which will handle the hover event
    */
    virtual void hoverEnterEvent(QGraphicsSceneHoverEvent * varEvent) override;

    //! Hover Leave Event
    /*!
      de-highlights the active grip when blurred

      \param *varEvent QGraphicsSceneHoverEvent object which will handle the hover event
    */
    virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent * varEvent) override;

    //! Mouse Release event
    /*!
      triggers when the user stops pressing the mouse, used to deactivate the selection of the object

      \param *varEvent QGraphicsSceneMouseEvent object which will handle the mouse event
    */
    void mouseReleaseEvent(QGraphicsSceneMouseEvent * varEvent) override;

    //! custom change event which updates the parent when each point is moved
    /*!
      \param varChange object containing the changes to the position of the grip
      \param &varOption reference to the QVariant containing the change
    */
    QVariant itemChange(GraphicsItemChange varChange, const QVariant &varValue) override;

    GraphicsPolygonItem * parent; //!< the parent GraphicsPolygonItem
    int index; //!< the current index of the grip
    QPainterPath circle; //!< the circle displays when not hovered
    QPainterPath square; //!< the square displays when not hovered



};

#endif // GRIP_H
