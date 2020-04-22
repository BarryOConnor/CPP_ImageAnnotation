#include "GraphicsPolygonItem.h"
#include "GraphicsScene.h"
#include "Global_Enums.h"
#include "GripHandle.h"

#include <QDebug>
#include <QPen>
#include <QPainter>
#include <QMenu>
#include <QAction>
#include <QGraphicsSceneContextMenuEvent>
#include <QStyleOptionGraphicsItem>


GraphicsPolygonItem::GraphicsPolygonItem(Annotation *varAnnotation, QMenu *varPopupMenu, GraphicsScene *varParent)
{

    //initialise from the annotation data
    label = varAnnotation->classname;
    id = varAnnotation->id;
    shapetype = varAnnotation->shape;
    popupMenu = varPopupMenu;
    color = varAnnotation->color;
    points = {};
    grips = {};

    //connect with the parent so it can notify the scene that it has been moved
    QObject::connect(this, &GraphicsPolygonItem::itemMoved, varParent, &GraphicsScene::itemMoved);

    //set up some basic information
    setZValue(10); // grip handles happen on z-index 11 so this needs to be beneath
    setAcceptHoverEvents(true);
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
    setCursor(QCursor(Qt::PointingHandCursor));
}

GraphicsPolygonItem::~GraphicsPolygonItem()=default;

int GraphicsPolygonItem::getId()
{
    return id;
}

int GraphicsPolygonItem::getShape()
{
    return shapetype;
}

int GraphicsPolygonItem::getColor()
{
    return color;
}

void GraphicsPolygonItem::setColor(int varColor)
{
    color = varColor;
    update();
}

QString GraphicsPolygonItem::getLabel()
{
    return label;
}

Annotation *GraphicsPolygonItem::getAnnotationInfo()
{
    Annotation *annotation = new Annotation(id, label, "", shapetype, color, getPolygon());
    return annotation;
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
    Q_UNUSED(varWidget);
    Q_UNUSED(varOption);
    varPainter->setPen(QPen(colorMap[color], 2, Qt::SolidLine, Qt::SquareCap, Qt::RoundJoin));
    varPainter->setBrush(Qt::transparent);
    varPainter->drawPolygon(polygon());
    QRectF measurements = boundingRect();
    varPainter->drawText(measurements.x(),measurements.y()-4,label);

    if (varOption->state & QStyle::State_Selected) {
        // specific rules for "selected" item
        varPainter->setPen(QPen(Qt::white, 1, Qt::DashLine, Qt::SquareCap, Qt::RoundJoin));
        varPainter->drawRect(boundingRect());
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

    if (varChange == QGraphicsItem::ItemPositionHasChanged) {
        for (int i = 0; i < points.length();i++){
            moveGrip(i,points[i]);
        }
    }

    return QGraphicsPolygonItem::itemChange(varChange, varValue);
}



void GraphicsPolygonItem::addPoint(QPointF point)
{
    points.append(point);
    setPolygon(QPolygonF(points));
    GripHandle *griphandle = new GripHandle(points.length()-1, this);
    griphandle->setParentItem(this);
    scene()->addItem(griphandle);
    grips.append(griphandle);
    griphandle->setPos(point);
    update();
    prepareGeometryChange();
}

void GraphicsPolygonItem::movePoint(int varIndex, QPointF varPoint)
{
    if (varIndex >= 0 && varIndex < points.length()){
         points[varIndex] = varPoint;
         setPolygon(QPolygonF(points));
         update();
    }
}

void GraphicsPolygonItem::moveGrip(int varIndex, QPointF varPoint)
{
    if (varIndex >= 0 && varIndex < grips.length()){
        GripHandle *item = grips[varIndex];
        item->setEnabled(false);
        item->setPos(varPoint);
        item->setEnabled(true);
        update();
        prepareGeometryChange();
    }
}

void GraphicsPolygonItem::addPoints(const QVector<QPointF> &varPoints)
{
    for(QPointF varPoint: varPoints){
        addPoint(varPoint);
    }
}

void GraphicsPolygonItem::hoverLeaveEvent(QGraphicsSceneHoverEvent * varEvent){
Q_UNUSED(varEvent);

    const int TRIANGLE_MAX_POINTS = 3;
    const int RECTANGLE_MAX_POINTS = 4;
    const int TRAPEZIUM_MAX_POINTS = 4;
    const int POLYGON_MAX_POINTS = 8;
    int maxPoints = 0;

    switch (shapetype) {
    case Triangle:
        maxPoints = TRIANGLE_MAX_POINTS;
        break;
    case Rectangle:
        maxPoints = RECTANGLE_MAX_POINTS;
        break;
    case Trapezium:
        maxPoints = TRAPEZIUM_MAX_POINTS;
        break;
    case Polygon:
        maxPoints = POLYGON_MAX_POINTS;
        break;
    default:
        break;
    }

    if(points.length() == maxPoints) {
       emit itemMoved(id);
    }

}






