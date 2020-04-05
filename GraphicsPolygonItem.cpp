#include "GraphicsPolygonItem.h"
#include "GraphicsScene.h"
#include "Global_Enums.h"

#include <QDebug>
#include <QPen>
#include <QPainter>
#include <QMenu>
#include <QAction>
#include <QGraphicsSceneContextMenuEvent>
#include <QStyleOptionGraphicsItem>


GraphicsPolygonItem::GraphicsPolygonItem(QPolygonF varPolygon, QString varLabel, int varId, int varShape, int varColor, QMenu *varPopupMenu, GraphicsScene *varParent)
{
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
    label = varLabel;
    id = varId;
    shapetype = varShape;
    setPolygon(varPolygon);
    popupMenu = varPopupMenu;
    color = varColor;

    QObject::connect(this, &GraphicsPolygonItem::itemMoved, varParent, &GraphicsScene::itemMoved);
}

GraphicsPolygonItem::GraphicsPolygonItem(Annotation *varAnnotation, QMenu *varPopupMenu, GraphicsScene *varParent)
{
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
    label = varAnnotation->classname;
    id = varAnnotation->id;
    shapetype = varAnnotation->shape;
    setPolygon(QPolygonF(varAnnotation->coordinates));
    popupMenu = varPopupMenu;
    color = varAnnotation->color;

    QObject::connect(this, &GraphicsPolygonItem::itemMoved, varParent, &GraphicsScene::itemMoved);
}



int GraphicsPolygonItem::getId()
{
    return id;
}

int GraphicsPolygonItem::getColor()
{
    return color;
}

QString GraphicsPolygonItem::getLabel()
{
    return label;
}

QPolygonF GraphicsPolygonItem::getPolygon() const
{
    return polygon();
}

QPainterPath GraphicsPolygonItem::shape() const
{
    QPainterPath path;

    path.addPolygon(polygon());

    return path;
}

void GraphicsPolygonItem::paint(QPainter *varPainter, const QStyleOptionGraphicsItem *varOption, QWidget *varWidget)
{
    QPen pen;

    varPainter->setPen(QPen(colorMap[color], 2, Qt::SolidLine, Qt::SquareCap, Qt::RoundJoin));
    varPainter->drawPolygon(polygon());

    QRectF measurements = boundingRect();
    varPainter->drawText(measurements.x(),measurements.y()-4,label);

    if (varOption->state & QStyle::State_Selected)
        {

             varPainter->setPen(QPen(Qt::white, 1, Qt::DashLine, Qt::SquareCap, Qt::RoundJoin));
             varPainter->drawPolygon(polygon());
        }


}

void GraphicsPolygonItem::contextMenuEvent(QGraphicsSceneContextMenuEvent *varEvent)
{
    scene()->clearSelection();
    setSelected(true);
    popupMenu->exec(varEvent->screenPos());
}

QVariant GraphicsPolygonItem::itemChange(GraphicsItemChange varChange, const QVariant & varValue)
{

    if (varChange == QGraphicsItem::ItemPositionChange) {
        emit this->itemMoved(id);
    }

    return varValue;

}




