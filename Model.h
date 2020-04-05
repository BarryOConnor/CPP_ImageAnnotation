#ifndef MODEL_H
#define MODEL_H
#include "Annotations.h"

class QJsonDocument;

class Model
{
public:
    bool hasAnnotations;
    Model();

    void setImages(QVector<QString> varImages);
    QVector<QString> getImages();
    void setClasses(QVector<QString> varClasses);
    QVector<QString> getClasses();
    void setCurrentClass(QString varClass);
    QString getCurrentClass();
    void setCurrentImage(QString varImage);
    QString getCurrentImage();
    void setCurrentShape(int varShape);
    void setCurrentColor(int varColor);
    QVector<Annotation *> getAnnotationsForCurrentImage();

    void createAnnotation(int varId, QVector<QPointF> varCoordinates);
    void createAnnotation(int varId, QString varClassName, QString varImageName, int varShapeType, int varColor, QVector<QPointF> varCoordinates);
    void createAnnotation(Annotation *varNode);
    QByteArray saveAnnotations();
    void loadAnnotations(QJsonDocument JSONdoc);
    void deleteAnnotations();
    void deleteAnnotation(int varId);
    void updateAnnotation(int varId, QPolygonF varPosition);





private:
    QVector<QString> classList;
    QVector<QString> imageList;
    QString currentImage;
    QString currentClass;
    Annotations* annotations;
    int currentShape;
    int currentColor;

friend class Controller;
};

#endif // MODEL_H
