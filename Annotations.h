#ifndef ANNOTATIONS_H
#define ANNOTATIONS_H
#include "Annotation.h"

#include <QMutex>

class QPolygonF;

//!  Annotations class.
/*!
  Acts as a linked list containing annotations
*/
class Annotations  //LinkedList
{
    //! displays the contents of the list, used for debugging
    void display();

    //! append an annotation to the linked List
    /*!
      \param *varAnnotation pointer to an annotation object to append
    */
    void appendAnnotation(Annotation *varAnnotation);

    //! update the position of an annotation in the linked List
    /*!
      \param varId the Id number of the annotation to be updated
      \param varPosition the new positions for the annotation shape
    */
    bool updateAnnotation(int varId, QPolygonF varPosition);

    //! retrive the annotations relating to a given image
    /*!
      \param varImage the image to search by
      \return a vector containing the annotations relating to the image
    */
    QVector<Annotation *> searchByImage(QString varImage);

    //! retrieve the unique images from the linked list (for the file save)
    /*!
      \return a vector containing the list of unique images
    */
    QVector<QString> *uniqueImages();

    //! retrieve annotations in the correct format to create a JSON file
    /*!
      \return a vector containing the corretc format
    */
    QVector<QPair<QString, QVector<Annotation *>>> *getJSONAnnotations(QVector<QString> *varImages);

    //! delete all annotations with a given ID
    /*!
      \param varID an int containing the ID
      \return bool value for whether the process was successful
    */
    bool deleteWithId(int varId);

    //! delete all annotations within the linked list
    void deleteAllAnnotations();

    //! retrieve annotation with a given ID
    /*!
      \param varID an int containing the ID
    */
    Annotation * findById(int varId);

    //! default constructor for the class
    Annotations();
    //! destructor for the class
    ~Annotations();


    private:
        int length; //!< the length of the linked List
        Annotation *head; //!< pointer to the head of the linked list
        Annotation *tail; //!< pointer to the tail of the linked list
        QMutex *mutex;

    friend class Model;
    friend class Controller;
    friend class Autosave;
};

#endif // ANNOTATIONS_H
