#include "graphicsscene.h"
#include "controller.h"
#include "global-enums.h"

#include <QMessageBox>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>

class controller;



GraphicsScene::GraphicsScene()
{
    //initialise properties
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

    //set up the system to show we are drawing a new shape
    coords.clear();
    isNewShape = true;
    drawingMode = isDrawing;
    currentShape = varShape;

    //set the max numbeer of vertices
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
    // change the colour
    currentColor = varColor;

}

void GraphicsScene::setMode(Modes varMode){
    //set the drawing mode
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
    //find the currently selected item in the graphics scene
    QList<QGraphicsItem *> allSelectedItems = selectedItems();
    for (QGraphicsItem *item : qAsConst(allSelectedItems)) {
        GraphicsPolygonItem * selectedPoly = qgraphicsitem_cast<GraphicsPolygonItem *>(item);
        //let the controller know we are deleting it so it can update annotations
        emit annotationDeleted(selectedPoly->getId());
        // remove the item from the graphics scene
        removeItem(selectedPoly);
        delete selectedPoly;
    }
    //revert back to a new shape
    isNewShape = true;
    setMode(isMoving);
    update();
}

void GraphicsScene::copyItem()
{
    QList<QGraphicsItem *> selectedItems = this->selectedItems();

    //find the currently selected item in the graphics scene
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
            isNewShape = true;
            setMode(isMoving);
            //signal that a new shape has been completed
            emit annotationReady(annotation);
        }
    }

}

void GraphicsScene::paintItem()
{
    QList<QGraphicsItem *> selectedItems = this->selectedItems();
    //find the currently selected item in the graphics scene
    for (QGraphicsItem *item : qAsConst(selectedItems)) {
        if (item->type() == GraphicsPolygonItem::Type){
            GraphicsPolygonItem * selectedPoly = qgraphicsitem_cast<GraphicsPolygonItem *>(item);

               //update the colour of the current item to match the currently selected colour
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
    if(varEvent->buttons() == Qt::LeftButton){
        update();
    }
    QGraphicsScene::mouseMoveEvent(varEvent);
}

void GraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent * varEvent)
{
    //some checks to make sure a class and image is selected before clicking and that the user is not right clicking
    if(!imageLoaded) { QMessageBox::information(nullptr, tr("Information"), "You must select an Image first"); return; }
    if(currentClass=="" && drawingMode==isDrawing) { QMessageBox::information(nullptr, tr("Information"), "You must select a Class first"); return; }
    if(coords.size() > maxPoints ) { QMessageBox::information(nullptr, tr("Information"), "The maximum number of points is " + QString::number(maxPoints)); return; }
    if(varEvent->buttons() != Qt::LeftButton) return;


    // make sure we are in drawing mode and not just moving a shape
    if(drawingMode==isDrawing){
        if(isNewShape){
            //if it's a new shape, create a new shape
            Annotation *annotation = new Annotation(currentId,currentClass, "",currentShape, currentColor,{});

            currentId ++;
            currentPolygon = new GraphicsPolygonItem(annotation, childPopupMenu, this);
            //add to the scene (draw it)
            addItem(currentPolygon);

            //signal that the annotation is ready to be stored
            emit annotationReady(currentPolygon->getAnnotationInfo());
            isNewShape = false;
        }
        //if not new, just add a point to the current shape
        currentPolygon->addPoint( varEvent->scenePos());
        currentPolygon->update();
        update();
        //let the controller know we have updated the annotation
        emit updateItem(currentPolygon->getId(), currentPolygon->getPolygon());

        coords.push_back(varEvent->scenePos());
        if(coords.size() == maxPoints){
            isNewShape = true;
            setMode(isMoving);
        }
    }


    QGraphicsScene::mousePressEvent(varEvent);
}

void GraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent * varEvent){

    if(movingShape!= -1){
        //if a shape has indicated that it is being moved, do this

        QList<QGraphicsItem *> selectedItems = this->items();
        //find the currently selected item in the graphics scene
        for (QGraphicsItem *item : qAsConst(selectedItems)) {
            if (item->type() == GraphicsPolygonItem::Type){
                GraphicsPolygonItem * selectedPoly = qgraphicsitem_cast<GraphicsPolygonItem *>(item);
                if(selectedPoly->getId()==movingShape){
                    QPolygonF mypoly = selectedPoly->polygon();
                    for(int loopCount = 0; loopCount < mypoly.size(); loopCount++){
                        //get the new positions of the vertices
                        mypoly[loopCount] = selectedPoly->mapToScene(selectedPoly->polygon()[loopCount]);

                    }
                    //let the controller know we need to update this shape
                    emit updateItem(selectedPoly->getId(), mypoly);
                }
            }
        }
        movingShape= -1;
    }

    QGraphicsScene::mouseReleaseEvent(varEvent);
}

