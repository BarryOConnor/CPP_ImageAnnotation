#ifndef CUSTOMPOLYGON_H
#define CUSTOMPOLYGON_H
#include "Annotation.h"
#include "GripHandle.h"
#include <QGraphicsPolygonItem>

class GraphicsScene;
class GripHandle;
//!  Model class.
/*!
  subclasses QGraphicsPolygonItem and acts as a custom container for polygon shapes drawn in the application
*/
class GraphicsPolygonItem : public QObject, public QGraphicsPolygonItem
{
    Q_OBJECT

public:

    //! constructor for use with a pre-constructed annotation object
    /*!
      \param *varAnnotation pointer to an Annotation object containing the relevant data
      \param *varPopupMenu pointer to the popup menu item used by the shape
      \param *varParent pointer to the GraphicsScene the item is being drawn on
    */
    GraphicsPolygonItem(Annotation *varAnnotation, QMenu *varPopupMenu, GraphicsScene *varParent);

    //! destructor for the class
    ~GraphicsPolygonItem();

    //! retrieves the Id of the object
    /*!
      \return int value containing the ID
    */
    int getId();

    //! retrieves the Shape of the object
    /*!
      \return int value containing the Shape type
    */
    int getShape();

    //! retrieves the Color of the object
    /*!
      \return int value containing the color value
    */
    int getColor();

    //! retrieves the Label associated with the object
    /*!
      \return QString value containing the Label
    */
    QString getLabel();

    Annotation * getAnnotationInfo();

    //! retrieves the current shape as a polygon
    /*!
      \return QPolygonF object containing the shape
    */
    QPolygonF getPolygon() const;

    //! custom paint event overriding the original to handle drawing both the shape and the label in one object
    /*!
      \param *varPainter pointer to a QPainter object which handles the "paint" of the class
      \param *varOption pointer to the QStyleOptionGraphicsItem containing the paint event options
      \param *varWidget pointer to a QWidget object (not used but required by the underlying function)
    */
    void paint(QPainter *varPainter, const QStyleOptionGraphicsItem *varOption, QWidget *varWidget) override;

    //! custom change event overriding the original to handle changes to the object. Used to highlight that an item is being moved by the user
    /*!
      \param varChange object containing the changes to the drawing
      \param &varOption reference to the QVariant containing the change
    */
    QVariant itemChange(GraphicsItemChange varChange, const QVariant &varValue) override;

    //! override the default to allow for bounding box to neatly hug the shape instead of being a large square
    /*!
      \return QPainterPath with the shape's new bounding box
    */
    QPainterPath shape() const override;

    void addPoint(QPointF varPoint);
    void movePoint(int varIndex, QPointF varPoint);
    void moveGrip(int varIndex, QPointF varPoint);

    void addPoints(QVector<QPointF> varPoints);


signals:
    //! signal emitted when the shape's position has been changed by the user
    /*!
      \param varId int containing the ID of the moving shape
    */
    void itemMoved(int varId);

protected:
    //! override the default to allow for a custom context menu for the shape
    /*!
      \return *varEvent QGraphicsSceneContextMenuEvent object which will handle the popup menu event
    */
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *varEvent) override;

private:
    QMenu * popupMenu; //!< pointer to a popup menu for the shape
    QString label; //!< the text label for the shape
    int color; //!< the color for the shape
    int id; //!< the id for the shape
    int shapetype; //!< the type of shape represented
    QGraphicsScene *parent;
    bool editMode;
    QVector<QPointF> points;
    QVector<GripHandle*> grips;


    void hoverLeaveEvent(QGraphicsSceneHoverEvent * varEvent) override;
};

#endif // CUSTOMPOLYGON_H
