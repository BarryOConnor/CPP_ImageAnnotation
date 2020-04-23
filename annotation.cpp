#include "annotation.h"

Annotation::Annotation()
{
    next = nullptr;
    image = "";
    classname = "";
    id = -1;
    shape = -1;
    color = -1;
    coordinates = {};

}
Annotation::Annotation(int varId, QString varClass, QString varImage, int varShape, int varColor, QVector<QPointF> varCoordinates){
    next = nullptr;
    image = varImage;
    classname = varClass;
    id = varId;
    shape = varShape;
    color = varColor;
    coordinates = varCoordinates;
}

Annotation::~Annotation(){
    delete this;
}
