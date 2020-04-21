#include "AutoSave.h"
#include <QTimer>
#include <QDebug>
#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QDate>
#include <QDir>
#include <QMessageBox>
#include <QPushButton>

AutoSave::AutoSave()
{

    filename = "autosave.annotations";
    timer = new QTimer(0); //parent must be null
    overwrite = false;
    QObject::connect(timer, &QTimer::timeout, this, &AutoSave::getSaveData);
    timer->setInterval(60000);
    timer->start();
}

void AutoSave::saveDataReady( QVector<QString> * uniqueImages, QVector<QPair<QString, QVector<Annotation *> > > *jsonData)
{

        QJsonObject *finalJsonObject = new QJsonObject();
        //format the number of images in the linked list
        finalJsonObject->insert("no_of_images", uniqueImages->size());

        QJsonArray *imageArray = new QJsonArray();
        for(int imageCount = 0; imageCount < uniqueImages->size(); imageCount++){
            QJsonObject *imageObject = new QJsonObject();
            //format information about the image
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



            QFile file(QDate::currentDate().toString("yyyy-MM-dd") + filename);
              if(file.open(QIODevice::WriteOnly | QIODevice::Text))
              {

                  QTextStream stream(&file);

                  // collect the required data from the model which stores the annotations list
                  stream << doc.toJson();

                  file.close();

              }


}



