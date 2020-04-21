#ifndef GRAPHICSSCENE_H
#define GRAPHICSSCENE_H
#include "GraphicsPolygonItem.h"
#include "Annotation.h"
#include <QGraphicsScene>
#include <QAction>

//!  Model class.
/*!
  subclasses QGraphicsScene and acts as a custom drawing surface for all the graphical items
*/
class GraphicsScene : public QGraphicsScene
{
    Q_OBJECT

public:
    enum Modes { isDrawing, isMoving };//!< enum showing the various modes the GraphicsScene can be in

    //! sets the value of the imageLoaded property
    /*!
      \param varLoaded the new boolean value for the property
    */
    void setImageLoaded(bool varLoaded);

    //! sets the current image as a pixmap so it can be loaded quickly
    /*!
      \param varImage the new image as a pixmap
    */
    void setCurrentImage(QPixmap varImage);

    //! sets the value of the currentClass property
    /*!
      \param varClass the new value value for the property
    */
    void setCurrentClass(QString varClass);

    //! gets the value of the property ImageLoaded
    /*!
      \return a boolean with the current value of the property
    */
    bool getImageLoaded();

    //! resets the GraphicsScene completely removing all items
    void reset();

    //! sets the value of the currentShape property
    /*!
      \param varShape the new value value for the property
    */
    void setShape(int varShape);

    //! sets the value of the currentColor property
    /*!
      \param varColor the new color value for the property
    */
    void setColor(int varColor);

    //! sets the mode of the drawingMode property
    /*!
      \param varClass the new mode value for the property
    */
    void setMode(Modes newMode);

    //! used to update the annotations in the GraphicsScene when loaded from file
    /*!
      \param varAnnotationsList a vector of annotation objects to be displayed on the scene
    */
    void updateAnnotations(QVector<Annotation*> varAnnotationList);

    //! double click event for the GraphicsScene (not currently used)
    /*!
      \param *varEvent pointer to a mouse event object
    */
    virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent * varEvent);

    //! mouse move event for the GraphicsScene used to move a shape
    /*!
      \param *varEvent pointer to a mouse event object
    */
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent * varEvent);

    //! double click event for the GraphicsScene used to draw points of a shape
    /*!
      \param *varEvent pointer to a mouse event object
    */
    virtual void mousePressEvent(QGraphicsSceneMouseEvent * varEvent);

    //! Mouse Release event for the GraphicsScene (not currently used)
    /*!
      \param *varEvent pointer to a mouse event object
    */
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent * varEvent);

    //! constructor for the class
    GraphicsScene();

    //! destructor for the class
    ~GraphicsScene();


signals:
    //! emitted when a shape has been completed by the user
    /*!
      \param *varAnnotation pointer to a completed annotation object ready to be added to the linked list
    */
    void annotationReady(Annotation *varAnnotation);

    //! emitted when a shape has been deleted so that the linked list can be updated
    /*!
      \param varId the Id of the item to be deleted
    */
    void annotationDeleted(int varId);

    //! emitted when a shape has changed position so that the linked list can be updated
    /*!
      \param varId the Id of the item to be updated
      \param varPosition the new position of the item
    */
    void updateItem(int varId, QPolygonF varPosition);

public slots:
    //! slot for the delete signal from the popup menu. deletes the selected item
    void deleteItem();

    //! slot for the copy signal from the popup menu. copies the selected item
    void copyItem();

    //! slot for when an item is moved. indicates that the item has been moved
    /*!
      \param varId Id of the shape that has been moved
    */
    void itemMoved(int varId);

private:
    const int radius = 2; //!< const holding a set radius value

    QVector<QPointF> coords; //!< A vector containing points for the current shape as it's drawn
    QVector<QGraphicsLineItem *> lines; //!< a vector of lines for the current shape as it's drawn
    GraphicsPolygonItem *currentPolygon; //!< pointer to a PolygonItem for the current shape
    QGraphicsLineItem *line; //!< pointer to a line object containing the most recent line as it's drawn
    QPixmap currentImage; //!< the current image
    QString currentClass; //!< the current class
    bool imageLoaded; //!< has an image been loaded?
    bool isNewShape; //!< is this a new shape being drawn?
    int maxPoints; //!< maximum number of points allowed for the shape

    int currentId; //!< int counter holding the current ID value
    int currentColor; //!< the current color
    int currentShape; //!< the current shape
    int movingShape; //!< id if the shape that's currently being repositioned
    Modes drawingMode; //!< the current mode the Graphics Scene is in


    QMenu *childPopupMenu; //!< a pointer to the menu object to use as a popup menu
    QAction *deleteAction; //!< pointer to the "delete" option on the popup menu
    QAction *copyAction; //!< pointer to the "copy" option on the popup menu

};

#endif // GRAPHICSSCENE_H


