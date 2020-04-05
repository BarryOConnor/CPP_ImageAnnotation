#include "Model.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QPolygonF>
#include <QDebug>

Model::Model()
{
    classList = {};
    imageList = {};
    currentImage = "";
    currentClass = "";
    currentColor = 0;
    annotations = new Annotations();
    hasAnnotations = false;
}
void Model::setImages(QVector<QString> varImages){
    imageList = varImages;
}

QVector<QString> Model::getImages(){
    return imageList;
}

void Model::setClasses(QVector<QString> varClasses){
    classList = varClasses;
}

QVector<QString> Model::getClasses(){
    return classList;
};

void Model::setCurrentClass(QString varClass){
    currentClass = varClass;
}

QString Model::getCurrentClass(){
    return currentClass;
}

void Model::setCurrentImage(QString varImage){
    currentImage = varImage;
}

QString Model::getCurrentImage(){
    return currentImage;
}

void Model::setCurrentShape(int varShape)
{
    currentShape = varShape;
}

void Model::setCurrentColor(int varColor)
{
    currentColor = varColor;
}

QVector<Annotation *> Model::getAnnotationsForCurrentImage()
{
    return annotations->searchByImage(currentImage);
}

void Model::createAnnotation(Annotation *varNode){
    if(varNode->image == ""){
       varNode->image = currentImage;
    }
    annotations->appendAnnotation(varNode);
    hasAnnotations = true;
    //annotations->display();
}

QByteArray Model::saveAnnotations()
{
    QVector<QPair<QString, QVector<Annotation *>>> * jsonData;
    QVector<QString> * uniqueImages;

    uniqueImages = annotations->uniqueImages();
    qDebug() << uniqueImages;
    jsonData = annotations->getJSONAnnotations(uniqueImages);
    QJsonObject *finalJsonObject = new QJsonObject();
    finalJsonObject->insert("no_of_images", uniqueImages->size());

    QJsonArray *imageArray = new QJsonArray();
    for(int imageCount = 0; imageCount < uniqueImages->size(); imageCount++){
        QJsonObject *imageObject = new QJsonObject();
        imageObject->insert("image", uniqueImages->at(imageCount));

        for(int loopCount = 0; loopCount < uniqueImages->size(); loopCount++){
            QPair<QString, QVector<Annotation *>> currImage = jsonData->at(loopCount);

            if(currImage.first == uniqueImages->at(imageCount)){
                imageObject->insert("no_of_shapes", currImage.second.size());

                QJsonArray *shapeArray = new QJsonArray();
                for(int shapeCount = 0; shapeCount < currImage.second.size(); shapeCount++){
                    Annotation * currShape = currImage.second.at(shapeCount);
                    QJsonObject *shapeObject = new QJsonObject();

                    shapeObject->insert("shapetype", currShape->shape);
                    shapeObject->insert("color", currShape->color);
                    shapeObject->insert("id", currShape->id);
                    shapeObject->insert("class", currShape->classname);

                    QJsonArray *coordArray = new QJsonArray();
                    for(int coordCount = 0; coordCount < currShape->coordinates.size(); coordCount++){
                        QString coordString = QString::number(currShape->coordinates.at(coordCount).x()) + "," + QString::number(currShape->coordinates.at(coordCount).y());
                        coordArray->push_back(QJsonObject{{"Point_" + QString::number(coordCount+1), coordString}});
                    }
                    shapeObject->insert("coordinates", *coordArray);
                    shapeArray->push_back(*shapeObject);
                }
                imageObject->insert("shapes", *shapeArray);

                break;
            }


        }
        imageArray->push_back(*imageObject);
    }
    finalJsonObject->insert("images",*imageArray);
    QJsonDocument doc(*finalJsonObject);
    return doc.toJson();
}

void Model::loadAnnotations(QJsonDocument JSONdoc)
{
    QJsonObject JSONobj = JSONdoc.object();
    QVector<QPointF> newCoordinates = {};


    QJsonArray imageArray = JSONobj["images"].toArray();
    for(const QJsonValue& image: imageArray) {

        QJsonObject imageObj = image.toObject();


        QJsonArray shapeArray = imageObj["shapes"].toArray();
        for(const QJsonValue& shape: shapeArray) {
            Annotation *newAnnotation = new Annotation();
            QJsonObject shapeObj = shape.toObject();

            newAnnotation->image = imageObj["image"].toString();
            newAnnotation->id = shapeObj["id"].toInt();
            newAnnotation->classname = shapeObj["class"].toString();
            newAnnotation->shape = shapeObj["shape"].toInt();
            newAnnotation->color = shapeObj["color"].toInt();

            QJsonArray coordinateArray = shapeObj["coordinates"].toArray();
            int pointCount = 1;
            QString coordValues = "";
            for(const QJsonValue& coordinates: coordinateArray) {
                QJsonObject coordinateObj = coordinates.toObject();
                if(coordinateObj.contains("Point_"+QString::number(pointCount))){
                    coordValues = coordinateObj["Point_"+QString::number(pointCount)].toString();
                    QStringList values = coordValues.split(',');
                    newAnnotation->coordinates.push_back(QPointF(values[0].toInt(), values[1].toInt()));
                }
                pointCount++;
            }
            createAnnotation(newAnnotation);
        }
    }
}



void Model::deleteAnnotations(){
    annotations->deleteAllAnnotations();
    hasAnnotations = false;
}

void Model::deleteAnnotation(int varId)
{
    annotations->deleteWithId(varId);
}

void Model::updateAnnotation(int varId, QPolygonF varPosition)
{
    annotations->updateAnnotation(varId, varPosition);
}
