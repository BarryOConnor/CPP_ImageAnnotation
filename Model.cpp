#include "Model.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QPolygonF>


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
}

QByteArray Model::saveAnnotations(){
/****************************************************
 * uses QT classes for JSOn to create a JSON formatted
 * QByteArray which we can save to file and therefore save the
 * annotations
 ***************************************************/

    QVector<QPair<QString, QVector<Annotation *>>> * jsonData;
    QVector<QString> * uniqueImages;

    //get a list of the unique images since the JSON top element consists of this
    uniqueImages = annotations->uniqueImages();

    //get all the relevant annotations for each of the images
    jsonData = annotations->getJSONAnnotations(uniqueImages);
    QJsonObject *finalJsonObject = new QJsonObject();
    //format the number of images in the linked list
    finalJsonObject->insert("no_of_images", uniqueImages->size());

    QJsonArray *imageArray = new QJsonArray();
    for(int imageCount = 0; imageCount < uniqueImages->size(); imageCount++){
        QJsonObject *imageObject = new QJsonObject();
        //format information abotu the image
        imageObject->insert("image", uniqueImages->at(imageCount));

        for(int loopCount = 0; loopCount < uniqueImages->size(); loopCount++){
            QPair<QString, QVector<Annotation *>> currImage = jsonData->at(loopCount);

            if(currImage.first == uniqueImages->at(imageCount)){
                //format the number of shapes associated with the image
                imageObject->insert("no_of_shapes", currImage.second.size());

                QJsonArray *shapeArray = new QJsonArray();
                for(int shapeCount = 0; shapeCount < currImage.second.size(); shapeCount++){
                    Annotation * currShape = currImage.second.at(shapeCount);
                    QJsonObject *shapeObject = new QJsonObject();

                    //format the data for each shape
                    shapeObject->insert("shapetype", currShape->shape);
                    shapeObject->insert("color", currShape->color);
                    shapeObject->insert("id", currShape->id);
                    shapeObject->insert("class", currShape->classname);

                    //format the coordinates of each shape
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

    //pass the final content back tot he controller so it can be saved to file
    return doc.toJson();
}



void Model::loadAnnotations(QJsonDocument JSONdoc){
/****************************************************
 * Loads an annotation file and uses the Qt JSON handling
 * classes to convert that information into a linked List
 ***************************************************/

    QJsonObject JSONobj = JSONdoc.object();
    QVector<QPointF> newCoordinates = {};

    //convert the "images" tag to an array
    QJsonArray imageArray = JSONobj["images"].toArray();
    for(const QJsonValue& image: imageArray) {

        //create each element as an object for further parsing
        QJsonObject imageObj = image.toObject();

        //create an array containing the contents of the shapes element
        QJsonArray shapeArray = imageObj["shapes"].toArray();
        for(const QJsonValue& shape: shapeArray) {
            Annotation *newAnnotation = new Annotation();
            QJsonObject shapeObj = shape.toObject();

            //use an annotation object to store the variables
            newAnnotation->image = imageObj["image"].toString();
            newAnnotation->id = shapeObj["id"].toInt();
            newAnnotation->classname = shapeObj["class"].toString();
            newAnnotation->shape = shapeObj["shape"].toInt();
            newAnnotation->color = shapeObj["color"].toInt();

            QJsonArray coordinateArray = shapeObj["coordinates"].toArray();
            int pointCount = 1;
            QString coordValues = "";

            //add each coordinate to the coordinates vector
            for(const QJsonValue& coordinates: coordinateArray) {
                QJsonObject coordinateObj = coordinates.toObject();
                if(coordinateObj.contains("Point_"+QString::number(pointCount))){
                    coordValues = coordinateObj["Point_"+QString::number(pointCount)].toString();
                    QStringList values = coordValues.split(',');
                    newAnnotation->coordinates.push_back(QPointF(values[0].toInt(), values[1].toInt()));
                }
                pointCount++;
            }

            //add the completed annotation to the linked list
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
    annotations->display();
}

void Model::prepareAutosaveData()
{
    QVector<QPair<QString, QVector<Annotation *>>> * jsonData;
    QVector<QString> * uniqueImages;

    if(hasAnnotations){
    //get a list of the unique images since the JSON top element consists of this
    uniqueImages = annotations->uniqueImages();

    //get all the relevant annotations for each of the images
    jsonData = annotations->getJSONAnnotations(uniqueImages);
    emit saveDataReady(uniqueImages, jsonData);
    }
}
