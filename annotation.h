#ifndef ANNOTATION_H
#define ANNOTATION_H

//#include <QString>
#include <QVector>
#include <QPointF>

//!  Annotation class.
/*!
  Stores the base information used to create an annotation, also used to pass shapes across the application since a shape contains
  all the same variables except the pointer to next so it makes a handy container
*/
class Annotation  //Node
{
public:

    Annotation* next; //!< pointer to the next annotation
    QString image; //!< string containing the image the annotation is about
    QString classname; //!< string containing the class name of the object
    int id; //!< int value containing ID
    int shape; //!< the type of shape
    int color; //!< the color of the shape
    QVector<QPointF> coordinates;  //!< the coordinates that form the shape

    //! default constructor
    Annotation();

    //! constructor for use with seperate values for fields
    /*!
      \param varId int containing the ID of the annotation
      \param varClass string containing the class label for the shape
      \param varImage string containing the image for the shape
      \param varShape int containing the type of shape being drawn
      \param varColor int containing the color of the shape being drawn
      \param varCoordinates the coordinates that form the shape
    */
    Annotation(int varId, QString varClass, QString varImage, int varShape, int varColor, QVector<QPointF> varCoordinates);

    //! destructor for the class
    ~Annotation();
};

#endif // ANNOTATION_H
