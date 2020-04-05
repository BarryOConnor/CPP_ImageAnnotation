#include "GraphicsScene.h"
#include "Controller.h"
#include "Global_Enums.h"

#include <QMessageBox>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>

class controller;

GraphicsScene::GraphicsScene()
{
    imageLoaded = false;
    maxPoints = 0;
    radius = 2;
    movingShape = -1;
    currentClass = "";
    setBackgroundBrush(Qt::gray);
    isNewShape = true;
    coords.clear();
    currentId = 0;
    drawingMode = isMoving;
    currentColor = Red;


    childPopupMenu = new QMenu;
    deleteAction = new QAction(QIcon(":images/trashcan.png"), tr("&Delete"), this);
    deleteAction->setShortcut(tr("Delete"));
    deleteAction->setStatusTip(tr("Delete annotation shape"));
    copyAction = new QAction(QIcon(":images/copy.png"), tr("&Copy"), this);
    copyAction->setShortcut(tr("Copy"));
    copyAction->setStatusTip(tr("Copy annotation shape"));
    childPopupMenu->addAction(deleteAction);
    childPopupMenu->addAction(copyAction);
    connect(deleteAction, &QAction::triggered, this, &GraphicsScene::deleteItem);
    connect(copyAction, &QAction::triggered, this, &GraphicsScene::copyItem);

}

GraphicsScene::~GraphicsScene()
{
    delete this;
}

void GraphicsScene::setShape(int varShape){

    const int TRIANGLE_MAX_POINTS = 3;
    const int RECTANGLE_MAX_POINTS = 4;
    const int TRAPEZIUM_MAX_POINTS = 4;
    const int POLYGON_MAX_POINTS = 8;


    coords.clear();
    isNewShape = true;
    drawingMode = isDrawing;

    switch (varShape) {
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
}

void GraphicsScene::setColor(int varColor){

    currentColor = varColor;

}

void GraphicsScene::setMode(Modes varMode){
    this->drawingMode = varMode;
}

void GraphicsScene::updateAnnotations(QVector<Annotation*> varAnnotationList)
{
    for(int loopCount = 0; loopCount < varAnnotationList.size(); loopCount ++){
        Annotation *annotation = varAnnotationList[loopCount];
        currentPolygon = new GraphicsPolygonItem(annotation, childPopupMenu, this);
        currentPolygon->setPen(QPen(colorMap[currentColor], 2));
        addItem(currentPolygon);
        currentPolygon->update();
        update();
    }
}

void GraphicsScene::setImageLoaded(bool varLoaded){
    this->imageLoaded = varLoaded;
}

void GraphicsScene::setCurrentImage(QPixmap varImage){
    this->currentImage = varImage;
}

void GraphicsScene::setCurrentClass(QString varClass){
    this->currentClass = varClass;
}
bool GraphicsScene::getImageLoaded(){
    return this->imageLoaded;
}

void GraphicsScene::reset()
{
    clear();
    setSceneRect(0,0,currentImage.width(),currentImage.height());
    addPixmap(currentImage);
}

void GraphicsScene::drawLine(QPointF varStart, QPointF varEnd)
{
    line = new QGraphicsLineItem(QLineF(varStart, varEnd));
    line->setPen(QPen(colorMap[currentColor], 2));
    addItem(line);
    lines.push_back(line);
}

void GraphicsScene::drawPolygon(Annotation *newAnnotation)
{
    currentPolygon = new GraphicsPolygonItem(newAnnotation, childPopupMenu, this);
    currentPolygon->setPen(QPen(colorMap[newAnnotation->color], 2));
    addItem(currentPolygon);
    currentPolygon->update();
    update();

    emit annotationReady(newAnnotation);
}

void GraphicsScene::removeLines()
{
    for (int loopCount = 0; loopCount < lines.size(); loopCount ++) {
        delete lines[loopCount];
    }
    lines.clear();
}

void GraphicsScene::deleteItem()
{

    QList<QGraphicsItem *> allSelectedItems = selectedItems();
    for (QGraphicsItem *item : qAsConst(allSelectedItems)) {
        GraphicsPolygonItem * selectedPoly = qgraphicsitem_cast<GraphicsPolygonItem *>(item);
        emit annotationDeleted(selectedPoly->getId());
        removeItem(item);
        delete item;
    }
    update();
}

void GraphicsScene::copyItem()
{
    QList<QGraphicsItem *> selectedItems = this->selectedItems();
    Annotation *annotation = new Annotation();

    for (QGraphicsItem *item : qAsConst(selectedItems)) {
        if (item->type() == GraphicsPolygonItem::Type){
        GraphicsPolygonItem * selectedPoly = qgraphicsitem_cast<GraphicsPolygonItem *>(item);
            annotation->id = currentId;
            currentId ++;
            annotation->classname = selectedPoly->getLabel();
            annotation->image = "";
            annotation->color = selectedPoly->getColor();
            annotation->shape = currentShape;
            annotation->coordinates = selectedPoly->getPolygon();

            drawPolygon(annotation);
         }
    }
    update();
}

void GraphicsScene::itemMoved(int varId)
{
   movingShape = varId;
}

void GraphicsScene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent * varEvent)
{
    QGraphicsScene::mouseDoubleClickEvent(varEvent);
}

void GraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent * varEvent)
{
    if(varEvent->buttons() == Qt::LeftButton)
           update();
    QGraphicsScene::mouseMoveEvent(varEvent);
}

void GraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent * varEvent)
{
    if(!imageLoaded) { QMessageBox::information(nullptr, tr("Information"), "You must select an Image first"); return; }
    if(currentClass=="" && drawingMode==isDrawing) { QMessageBox::information(nullptr, tr("Information"), "You must select a Class first"); return; }
    if(coords.size() > maxPoints ) { QMessageBox::information(nullptr, tr("Information"), "The maximum number of points is " + QString::number(maxPoints)); return; }
    if(varEvent->buttons() != Qt::LeftButton) return;


    if(drawingMode==isDrawing){
        if(isNewShape){
            isNewShape = false;
            drawLine(varEvent->scenePos(), varEvent->scenePos());
        } else {
            drawLine(coords[coords.size()-1], varEvent->scenePos());
        }

        coords.push_back(varEvent->scenePos());
        if(coords.size() == maxPoints){
            removeLines();
            Annotation *annotation = new Annotation();
            annotation->id = currentId;
            currentId ++;
            annotation->classname = currentClass;
            annotation->image = "";
            annotation->color = currentColor;
            annotation->shape = currentShape;
            annotation->coordinates = coords;

            drawPolygon(annotation);
            setMode(isMoving);
        }
    }


    QGraphicsScene::mousePressEvent(varEvent);
}

void GraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent * varEvent){
    if(movingShape!= -1){
        QList<QGraphicsItem *> selectedItems = this->selectedItems();

        for (QGraphicsItem *item : qAsConst(selectedItems)) {
            if (item->type() == GraphicsPolygonItem::Type){
                GraphicsPolygonItem * selectedPoly = qgraphicsitem_cast<GraphicsPolygonItem *>(item);
                QPolygonF mypoly = selectedPoly->polygon();
                for(int loopCount = 0; loopCount < mypoly.size(); loopCount++){
                    mypoly[loopCount] = selectedPoly->mapToScene(selectedPoly->polygon()[loopCount]);
                    qDebug() << mypoly[loopCount].x() + selectedPoly->scenePos().x();
                    qDebug() << mypoly[loopCount].y() + selectedPoly->scenePos().y();
                }
                emit updateItem(selectedPoly->getId(), mypoly);
            }
        }
        movingShape= -1;
    }

    QGraphicsScene::mouseReleaseEvent(varEvent);
}

