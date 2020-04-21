#ifndef GRIP_H
#define GRIP_H

#include <QPainterPath>
#include <QGraphicsPathItem>

#include "GraphicsPolygonItem.h"

class GraphicsPolygonItem;

class GripHandle: public QGraphicsPathItem
{

public:
    GripHandle();
    GripHandle(int varIndex, GraphicsPolygonItem *varParent);
    GripHandle(const GripHandle& );//cctor
    GripHandle& operator=(const GripHandle& );//operator=
    GraphicsPolygonItem * parent;
    int index;
    QPainterPath circle;
    QPainterPath square;

    virtual void hoverEnterEvent(QGraphicsSceneHoverEvent * varEvent) override;
    virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent * varEvent) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent * varEvent) override;
    QVariant itemChange(GraphicsItemChange varChange, const QVariant &varValue) override;

};

#endif // GRIP_H
