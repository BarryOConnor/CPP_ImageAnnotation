#ifndef ANNOTATION_H
#define ANNOTATION_H

//#include <QString>
#include <QVector>
#include <QPointF>

class Annotation  //Node
{
public:

    Annotation* next;
    QString image;
    QString classname;
    int id;
    int shape;
    int color;
    QVector<QPointF> coordinates;
    Annotation();
    Annotation(int varId, QString varClass, QString varImage, int varShape, int varColor, QVector<QPointF> varCoordinates);
    ~Annotation();
};

#endif // ANNOTATION_H
