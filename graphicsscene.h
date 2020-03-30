#ifndef GRAPHICSSCENE_H
#define GRAPHICSSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPointF>
#include <vector>
#include <QGraphicsItem>
#include <QPen>

class GraphicsScene : public QGraphicsScene
{
    Q_OBJECT
public:

    void setMaxPoints(int points);
    void setImageLoaded(bool loaded);
    void setCurrentImage(QPixmap image);
    void setCurrentClass(QString className);
    bool getImageLoaded();
    void newShape();


    explicit GraphicsScene(QObject *parent = 0);
    virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent * mouseEvent);
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent * mouseEvent);
    virtual void mousePressEvent(QGraphicsSceneMouseEvent * mouseEvent);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent * mouseEvent);
signals:

public slots:

private:
    std::vector<QPointF> m_coords;
    std::vector<QGraphicsItem *> m_points;
    std::vector<QGraphicsItem *> m_lines;
    bool imageLoaded = false;
    QPen linePen;
    unsigned int maxPoints = 8;
    int selectedPoint;
    int radius = 2;
    QPixmap currentImage;
    QString currentClass;

    int pointExists(QGraphicsSceneMouseEvent * mouseEvent);
    void movePoint(QGraphicsSceneMouseEvent * mouseEvent);
    void redrawPoints();
    void drawPoint(QPointF point);
};

#endif // GRAPHICSSCENE_H


