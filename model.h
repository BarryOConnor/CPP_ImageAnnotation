#ifndef MODEL_H
#define MODEL_H
#include "annotations.h"

#include <QObject>

class QJsonDocument;

//! Model class handles most elements of data within the application.
/*!
  The Model class handles most elements of data within the application
*/
class Model: public QObject
{
    Q_OBJECT

public:
    bool hasAnnotations; //!< Bool to show whether the model actually has any annotations
    Model(); //!< constructor for the class

    //! set the list of images
    /*!
      \param varImages a QVector of Qstrings containing the list of images.
    */
    void setImages(QVector<QString> varImages);

    //! get the list of images
    /*!
      \return a QVector of Qstrings containing the list of images.
    */
    QVector<QString> getImages();

    //! set the list of classes
    /*!
      \param varClasses a QVector of Qstrings containing the list of classes.
    */
    void setClasses(QVector<QString> varClasses);

    //! get the list of classes
    /*!
      \return a QVector of Qstrings containing the list of classes.
    */
    QVector<QString> getClasses();

    //! set the current class
    /*!
      \param varClass a Qstring containing the current class.
    */
    void setCurrentClass(QString varClass);

    //! get the current class
    /*!
      \return a Qstring containing the current class.
    */
    QString getCurrentClass();

    //! set the current image
    /*!
      \param varImage a Qstring containing the current image.
    */
    void setCurrentImage(QString varImage);

    //! get the current image
    /*!
      \return a Qstring containing the current image.
    */
    QString getCurrentImage();

    //! set the current shape
    /*!
      \param varShape an int containing the current shape value.
    */
    void setCurrentShape(int varShape);

    //! set the current color
    /*!
      \param varColor an int containing the current color value.
    */
    void setCurrentColor(int varColor);

    //! get the annotations associated with the current image
    /*!
      \return a QVector of annotations which are associated with the current image.
    */
    QVector<Annotation *> getAnnotationsForCurrentImage();

    //! create a new Annotation
    /*!
      \param varId an int containing the id of the new element.
      \param varCoordinates a QVector of QPoints which represent the shape that was drawn
    */
    void createAnnotation(int varId, QVector<QPointF> varCoordinates);

    //! create a new Annotation from full parameter list
    /*!
      \param varId an int containing the id of the new element.
      \param varClassName a QString containing the class name for the new Annotation.
      \param varImageName a QString containing the image name for the new Annotation.
      \param varShapeType an int containing the shape type for the new Annotation.
      \param varColor an int containing the color for the new Annotation.
      \param varCoordinates a QVector of QPoints which represent the shape that was drawn
    */
    void createAnnotation(int varId, QString varClassName, QString varImageName, int varShapeType, int varColor, QVector<QPointF> varCoordinates);

    //! create a new Annotation from an existing Annotation object
    /*!
      \param *varNode a pointer to an Annotation Object containing the new annotation
    */
    void createAnnotation(Annotation *varNode);

    //! Save annotations into a QByteArray ready to save to file
    /*!
      \return a QByteArray containing the JSON content ready to save to file
    */
    QByteArray saveAnnotations();

    //! Load annotations from a JSON formatted file
    /*!
      \param JSONDoc JSON format content representing the annotations
    */
    void loadAnnotations(const QJsonDocument &JSONdoc);

    //! deletes all annotations
    void deleteAnnotations();

    //! delete a specified annotation from the linked list
    /*!
      \param varId an integer ID number for the annotation to delete
    */
    void deleteAnnotation(int varId);

    //! update a specified annotation from the linked list
    /*!
      \param varId an integer ID number for the annotation to update
      \param varPosition new position for the updated Polygon
    */
    void updateAnnotation(int varId, QPolygonF varPosition);

public slots:
    //! recieves notification from the autosave thread that a new autosave is in progress
    void prepareAutosaveData();

signals:
    //! emits a signal to the autosave thread containing the data it needs to run
    /*!
      \param *uniqueImages QVector containing a list of all unique images in the linked list
      \param *jsonData A vector of pairs containing the name of the image and all corresponding annotations
    */
    void saveDataReady(QVector<QString> * uniqueImages, QVector<QPair<QString, QVector<Annotation *>>> *JSONData);

private:
    QVector<QString> classList; //!< List of class names stored as strings in a vector
    QVector<QString> imageList; //!< List of class images stored as strings in a vector
    QString currentImage; //!< the current image
    QString currentClass; //!< the current class
    Annotations* annotations; //!< pointer to a linked list containing the annotations
    int currentShape; //!< the current shape type
    int currentColor; //!< the current color

friend class Controller;
friend class AnnotationsApp;
};

#endif // MODEL_H
