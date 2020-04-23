#include "griphandle.h"
#include "graphicspolygonitem.h"
#include <QColor>
#include <QBrush>
#include <QPen>
#include <QCursor>


GripHandle::GripHandle(int varIndex, GraphicsPolygonItem * varParent)
{
    parent = varParent;
    index = varIndex;
    circle.addEllipse(QRectF(-3, -3, 6, 6));
    square.addRect(QRectF(-3, -3, 6, 6));

    setPath(circle);
    setBrush(QBrush(Qt::darkGray));
    setPen(QPen(Qt::white, 1));
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
    setAcceptHoverEvents(true);
    setZValue(11);//draw the handles one layer above the shape
    setCursor(QCursor(Qt::PointingHandCursor));
}


void GripHandle::hoverEnterEvent(QGraphicsSceneHoverEvent *varEvent)
{
    setPath(square);
    setBrush(QBrush(Qt::darkGray));
    QGraphicsPathItem::hoverEnterEvent(varEvent);
}

void GripHandle::hoverLeaveEvent(QGraphicsSceneHoverEvent *varEvent)
{
    setPath(circle);
    setBrush(QBrush(Qt::darkGray));
    QGraphicsPathItem::hoverLeaveEvent(varEvent);
}

void GripHandle::mouseReleaseEvent(QGraphicsSceneMouseEvent *varEvent)
{
    setSelected(false);
    QGraphicsPathItem::mouseReleaseEvent(varEvent);
}

QVariant GripHandle::itemChange(QGraphicsItem::GraphicsItemChange varChange, const QVariant &varValue)
{
    if (varChange == QGraphicsItem::ItemPositionChange && isEnabled()){
        parent->movePoint(index, varValue.toPointF());
    }
    return QGraphicsPathItem::itemChange(varChange, varValue);
}
