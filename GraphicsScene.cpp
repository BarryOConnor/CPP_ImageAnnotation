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
    movingShape = -1;
    currentClass = "";
    setBackgroundBrush(Qt::gray);
    isNewShape = true;
    coords.clear();
    currentId = 0;
    drawingMode = isMoving;
    currentColor = Red;
    currentShape = -1;
    currentPolygon = {};


    //handle the popup menu so that it can be used by the shapes
    childPopupMenu = new QMenu;

    //delete a shape
    deleteAction = new QAction(QIcon(":images/trashcan.png"), tr("&Delete"), this);
    deleteAction->setStatusTip(tr("Delete annotation shape"));
    childPopupMenu->addAction(deleteAction);

    // copy a shape
    copyAction = new QAction(QIcon(":images/copy.png"), tr("&Copy"), this);
    copyAction->setStatusTip(tr("Copy annotation shape"));
    childPopupMenu->addAction(copyAction);

    // paint a shape
    paintAction = new QAction(QIcon(":images/paint.png"), tr("&Paint"), this);
    paintAction->setStatusTip(tr("repaint using the current colour"));
    childPopupMenu->addAction(paintAction);

    //connect the signals from the popup menu to the Graphics Scene which handles them
    connect(deleteAction, &QAction::triggered, this, &GraphicsScene::deleteItem);
    connect(copyAction, &QAction::triggered, this, &GraphicsScene::copyItem);
    connect(paintAction, &QAction::triggered, this, &GraphicsScene::paintItem);

}

GraphicsScene::~GraphicsScene()
{
    delete this;
}

void GraphicsScene::setShape(int varShape){
//format the coordinates of each shape
    const int TRIANGLE_MAX_POINTS = 3;
    const int RECTANGLE_MAX_POINTS = 4;
    const int TRAPEZIUM_MAX_POINTS = 4;
    const int POLYGON_MAX_POINTS = 8;


    coords.clear();
    isNewShape = true;
    drawingMode = isDrawing;
    currentShape = varShape;

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

void GraphicsScene::updateAnnotations(const QVector<Annotation*> &varAnnotationList)
{
    for(Annotation* annotation: varAnnotationList){
        //create a new polygon with the information, add it to the scene and update the points
        currentPolygon = new GraphicsPolygonItem(annotation, childPopupMenu, this);
        addItem(currentPolygon);
        currentPolygon->addPoints(annotation->coordinates);

        //update the scene
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


void GraphicsScene::deleteItem()
{

    QList<QGraphicsItem *> allSelectedItems = selectedItems();
    for (QGraphicsItem *item : qAsConst(allSelectedItems)) {
        GraphicsPolygonItem * selectedPoly = qgraphicsitem_cast<GraphicsPolygonItem *>(item);
        emit annotationDeleted(selectedPoly->getId());
        removeItem(selectedPoly);
        delete selectedPoly;
    }
    update();
}

void GraphicsScene::copyItem()
{
    QList<QGraphicsItem *> selectedItems = this->selectedItems();

    for (QGraphicsItem *item : qAsConst(selectedItems)) {
        if (item->type() == GraphicsPolygonItem::Type){
            GraphicsPolygonItem * selectedPoly = qgraphicsitem_cast<GraphicsPolygonItem *>(item);

            // get the annotation info out of the selected poly
            Annotation * annotation = selectedPoly->getAnnotationInfo();

            //update ID
            annotation->id = currentId;
            currentId ++;

            //create a new polygon with the information, add it to the scene and update points
            currentPolygon = new GraphicsPolygonItem(annotation, childPopupMenu, this);
            addItem(currentPolygon);
            currentPolygon->addPoints(annotation->coordinates); // need to add the points after the item is added to the scene

            // update the polygon and scene
            currentPolygon->update();
            update();

            //signal that a new shape has been completed
            emit annotationReady(annotation);
        }
    }

}

void GraphicsScene::paintItem()
{
    QList<QGraphicsItem *> selectedItems = this->selectedItems();

    for (QGraphicsItem *item : qAsConst(selectedItems)) {
        if (item->type() == GraphicsPolygonItem::Type){
            GraphicsPolygonItem * selectedPoly = qgraphicsitem_cast<GraphicsPolygonItem *>(item);

            selectedPoly->setColor(currentColor);
            selectedPoly->update();
            update();

        }
    }
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

            Annotation *annotation = new Annotation(currentId,currentClass, "",currentShape, currentColor,{});

            currentId ++;
            currentPolygon = new GraphicsPolygonItem(annotation, childPopupMenu, this);
            addItem(currentPolygon);
            isNewShape = false;
        }
        currentPolygon->addPoint( varEvent->scenePos());
        currentPolygon->update();
        update();

        coords.push_back(varEvent->scenePos());
        if(coords.size() == maxPoints){
            isNewShape = true;
            emit annotationReady(currentPolygon->getAnnotationInfo());
            setMode(isMoving);
        }
    }


    QGraphicsScene::mousePressEvent(varEvent);
}

void GraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent * varEvent){

    if(movingShape!= -1){

        QList<QGraphicsItem *> selectedItems = this->items();

        for (QGraphicsItem *item : qAsConst(selectedItems)) {
            if (item->type() == GraphicsPolygonItem::Type){
                GraphicsPolygonItem * selectedPoly = qgraphicsitem_cast<GraphicsPolygonItem *>(item);
                if(selectedPoly->getId()==movingShape){
                    QPolygonF mypoly = selectedPoly->polygon();
                    for(int loopCount = 0; loopCount < mypoly.size(); loopCount++){
                        mypoly[loopCount] = selectedPoly->mapToScene(selectedPoly->polygon()[loopCount]);
                        //qDebug() << mypoly;
                    }
                    emit updateItem(selectedPoly->getId(), mypoly);
                }
            }
        }
        movingShape= -1;
    }

    QGraphicsScene::mouseReleaseEvent(varEvent);
}

