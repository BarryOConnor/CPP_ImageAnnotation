#ifndef ANNOTATIONS_H
#define ANNOTATIONS_H
#include "Annotation.h"

class QPolygonF;

class Annotations  //LinkedList
{
    void display();

    void appendAnnotation(Annotation *varAnnotation);
    bool updateAnnotation(int varId, QPolygonF varPosition);
    QVector<Annotation *> searchByImage(QString varImage);
    QVector<QString> *uniqueImages();
    QVector<QPair<QString, QVector<Annotation *>>> *getJSONAnnotations(QVector<QString> *varImages);
    bool deleteWithId(int varId);
    void deleteAllAnnotations();
    Annotation * findById(int varId);
    Annotations();
    ~Annotations();


    private:
        int length;
        Annotation *head, *tail;

    friend class Model;
    friend class Controller;
};

#endif // ANNOTATIONS_H
