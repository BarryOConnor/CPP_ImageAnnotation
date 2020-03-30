#include "graphicsscene.h"
#include <string>
#include <QDebug>
#include <QGraphicsEllipseItem>
#include <QGraphicsPathItem>
#include <QPainterPath>
#include <QMessageBox>


GraphicsScene::GraphicsScene(QObject *parent) :
    QGraphicsScene(parent)
{
    this->setBackgroundBrush(Qt::gray);
    linePen.setBrush(Qt::red);
    linePen.setWidth(2);
}

void GraphicsScene::newShape(){
    this->m_coords.clear();
}

void GraphicsScene::setMaxPoints(int points){
    this->maxPoints = points;
}

void GraphicsScene::setImageLoaded(bool loaded){
    this->imageLoaded = loaded;
}

void GraphicsScene::setCurrentImage(QPixmap image){
    this->currentImage = image;
}

void GraphicsScene::setCurrentClass(QString className){
    this->currentClass = className;
}
bool GraphicsScene::getImageLoaded(){
    return this->imageLoaded;
}

int GraphicsScene::pointExists(QGraphicsSceneMouseEvent * mouseEvent){
    if(m_coords.size() > 1){
        //loop through the points
        for (unsigned int loopCount = 0; loopCount < m_coords.size(); loopCount ++) {
            //check if within 5 pixels of a point (easier to "hit" the target with a mouse)
            if( mouseEvent->scenePos().x() -5 <= m_coords.at(loopCount).x()
                    && mouseEvent->scenePos().x() +5 >= m_coords.at(loopCount).x()
                    && mouseEvent->scenePos().y() -5 <= m_coords.at(loopCount).y()
                    && mouseEvent->scenePos().y() +5 >= m_coords.at(loopCount).y()
                    ){

                return loopCount;
            }
        }
    }
    return -1;
}

void GraphicsScene::redrawPoints(){


        //loop through the points
        m_points.clear();
        m_lines.clear();
        this->clear();
        this->setSceneRect(0,0,currentImage.width(),currentImage.height());
        this->addPixmap(currentImage);

        for (unsigned int loopCount = 0; loopCount < m_coords.size(); loopCount ++) {


            QGraphicsEllipseItem * ellipse = this->addEllipse(m_coords.at(loopCount).x() - radius, m_coords.at(loopCount).y() - radius, radius*2, radius*2);
            ellipse->setFlag( QGraphicsItem::ItemIsMovable );
            ellipse->setBrush(Qt::white);
            ellipse->setCursor(Qt::SizeAllCursor);
            m_points.push_back(ellipse);
            if(loopCount == 0){
                QGraphicsTextItem *text = this->addText(currentClass);
                text->setPos(m_coords.at(loopCount).x()-20, m_coords.at(loopCount).y()-20);
                text->setDefaultTextColor ( Qt::red );
                this->addItem(text);
            }
            if(loopCount > 0){
                qDebug() << "doing normal dot";
                QGraphicsLineItem *line = new QGraphicsLineItem(m_coords.at(loopCount-1).x(),m_coords.at(loopCount-1).y(),
                                                                m_coords.at(loopCount).x(),m_coords.at(loopCount).y());
                line->setPen(linePen);
                this->addItem(line);

                m_lines.push_back(line);

            }
        }
        qDebug() << "doing final dot";
        QGraphicsLineItem *line = new QGraphicsLineItem(m_coords.at(0).x(),m_coords.at(0).y(),
                                                            m_coords.at(m_coords.size()-1).x(),m_coords.at(m_coords.size()-1).y());

        line->setPen(linePen);
        this->addItem(line);
        m_lines.push_back(line);
}

void GraphicsScene::drawPoint(QPointF point){

        QGraphicsEllipseItem * ellipse = this->addEllipse(point.x() - radius, point.y() - radius, radius*2, radius*2);
        ellipse->setFlag( QGraphicsItem::ItemIsMovable );
        ellipse->setBrush(Qt::white);
        ellipse->setCursor(Qt::SizeAllCursor);
        m_points.push_back(ellipse);
        m_coords.push_back(point);
        if(m_coords.size() == 1){

            QGraphicsTextItem *text = this->addText(currentClass);
            text->setPos(point.x(), point.y()-20);
            text->setDefaultTextColor ( Qt::red );
            this->addItem(text);
        } else {
                QGraphicsLineItem *line = new QGraphicsLineItem(m_coords.at(m_coords.size()-2).x(),m_coords.at(m_coords.size()-2).y(),
                                                                m_coords.at(m_coords.size()-1).x(),m_coords.at(m_coords.size()-1).y());

                line->setPen(linePen);
                this->addItem(line);
                m_lines.push_back(line);

        }
        if(m_coords.size() == maxPoints ){
            QGraphicsLineItem *line = new QGraphicsLineItem(m_coords.at(0).x(),m_coords.at(0).y(),
                                                            m_coords.at(m_coords.size()-1).x(),m_coords.at(m_coords.size()-1).y());

            line->setPen(linePen);
            this->addItem(line);
            m_lines.push_back(line);

        }

}

void GraphicsScene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent * mouseEvent)
{
    //qDebug() << Q_FUNC_INFO << mouseEvent->scenePos();
    QGraphicsScene::mouseDoubleClickEvent(mouseEvent);
}

void GraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent * mouseEvent)
{
    //qDebug() << Q_FUNC_INFO << mouseEvent->scenePos();
    QGraphicsScene::mouseMoveEvent(mouseEvent);
}

void GraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent * mouseEvent)
{
    selectedPoint = pointExists(mouseEvent);

    if(imageLoaded){
        if(currentClass!=""){
            if(selectedPoint == -1){
                if(m_coords.size() <= maxPoints -1 ){
                    drawPoint(mouseEvent->scenePos());
                } else {
                    QMessageBox::information(nullptr, tr("Information"), "The maximum number of points is " + QString::number(maxPoints));
                }
            } else {
                m_points.at(selectedPoint)->setCursor(Qt::ClosedHandCursor);
            }
        } else {
            QMessageBox::information(nullptr, tr("Information"), "You must select a Class first");
        }
    } else {
        QMessageBox::information(nullptr, tr("Information"), "You must select an Image first");
    }
    QGraphicsScene::mousePressEvent(mouseEvent);
}

void GraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent * mouseEvent)
{
    if(selectedPoint != -1){
        m_points.at(selectedPoint)->setCursor(Qt::SizeAllCursor);
        m_coords.at(selectedPoint) = mouseEvent->scenePos();
        m_points.at(selectedPoint) = this->addEllipse(mouseEvent->scenePos().x() - radius, mouseEvent->scenePos().y() - radius, radius*2, radius*2);
        redrawPoints();

    }
    QGraphicsScene::mouseReleaseEvent(mouseEvent);
}
