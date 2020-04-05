#ifndef GRAPHICSSCENE_H
#define GRAPHICSSCENE_H
#include "GraphicsPolygonItem.h"
#include "Annotation.h"
#include <QGraphicsScene>
#include <QAction>

class GraphicsScene : public QGraphicsScene
{
    Q_OBJECT

public:
    enum Modes { isDrawing, isMoving };

    void setImageLoaded(bool varLoaded);
    void setCurrentImage(QPixmap varImage);
    void setCurrentClass(QString varClass);
    bool getImageLoaded();
    void reset();
    void setShape(int varShape);
    void setColor(int varColor);
    void setMode(Modes newMode);
    void updateAnnotations(QVector<Annotation*> varAnnotationList);

    GraphicsScene();
    ~GraphicsScene();

    virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent * varEvent);
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent * varEvent);
    virtual void mousePressEvent(QGraphicsSceneMouseEvent * varEvent);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent * varEvent);

signals:
    void annotationReady(Annotation *varAnnotation);
    void annotationDeleted(int varId);
    void updateItem(int varId, QPolygonF varPosition);

public slots:
    void deleteItem();
    void copyItem();
    void itemMoved(int varId);

private:

    QVector<QPointF> coords;
    QVector<QGraphicsLineItem *> lines;
    GraphicsPolygonItem *currentPolygon;
    QGraphicsLineItem *line;
    QPixmap currentImage;
    QString currentClass;
    bool imageLoaded;
    bool isNewShape;
    int maxPoints;
    int radius;
    int currentId;
    int currentColor;
    int currentShape;
    int movingShape;
    Modes drawingMode;


    QMenu *childPopupMenu;
    QAction *deleteAction, *copyAction;

    void drawLine(QPointF varStart, QPointF varEnd);
    void drawPolygon(Annotation *varAnnotation);
    void removeLines();

};

#endif // GRAPHICSSCENE_H


