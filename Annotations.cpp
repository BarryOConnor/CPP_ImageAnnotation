#include "Annotations.h"
#include <QDebug>
#include <QPolygonF>

Annotations::Annotations(){
    length = 0;
    head = NULL;
    tail = NULL;
}

Annotations::~Annotations(){
    delete this;
}

void Annotations::display(){
    Annotation *temp=new Annotation;

    temp=head;
    while(temp!=NULL)
    {
        qDebug() << temp->id << "\t";
        qDebug() << temp->classname << "\t";
        qDebug() << temp->image << "\t";
        qDebug() << temp->shape << "\t";
        qDebug() << temp->color << "\t";
        qDebug() << temp->coordinates << "\t";
        temp=temp->next;
    }
}



void Annotations::appendAnnotation(Annotation *varAnnotation){
    varAnnotation->next = NULL;
    if(head == NULL){
        head = varAnnotation;
        tail = varAnnotation;
        varAnnotation = NULL;
    } else {
        tail->next = varAnnotation;
        tail = varAnnotation;
    }
    length++;
}


QVector<Annotation *> Annotations::searchByImage(QString varImage) {
    Annotation *currNode = new Annotation();
    QVector<Annotation*> annotationList;

    currNode = head;
    while (currNode != NULL) {
        if(currNode->image == varImage) {
            annotationList.push_back(currNode);
        }
        currNode = currNode->next;
    }
    return annotationList;
}

QVector<QString> *Annotations::uniqueImages() {
    Annotation *currNode = new Annotation();
    QString prevImages = "";
    QVector<QString> *results = new QVector<QString>;

    currNode = head;
    while (currNode != NULL) {
        if(!prevImages.contains(currNode->image)){
            results->push_back(currNode->image);
            prevImages += currNode->image;
        }
        currNode = currNode->next;
    }
    return results;
}

QVector<QPair<QString, QVector<Annotation *>>> *Annotations::getJSONAnnotations(QVector<QString> *varImages) {
    Annotation *currNode = new Annotation();
    QString prevImages = "";
    QVector<QPair<QString, QVector<Annotation *>>> *results = new QVector<QPair<QString, QVector<Annotation *>>>;
    QPair<QString, QVector<Annotation *>> matches = QPair<QString, QVector<Annotation *>>();

    for(int loopCount = 0; loopCount < varImages->size(); loopCount++) {
        matches.first = varImages->at(loopCount);
        matches.second.clear();
        currNode = head;
        while (currNode != NULL) {
            if(currNode->image == varImages->at(loopCount)){
                matches.second.push_back(currNode);
                prevImages += currNode->image;
            }
            currNode = currNode->next;
        }
        results->push_back(matches);
    }
    return results;
}


bool Annotations::deleteWithId(int varId){
    Annotation *currNode = new Annotation;
    Annotation *prevNode = new Annotation;

    currNode = head;
    for(int loopCount = 0; loopCount <= length; loopCount ++){
        if(varId == currNode->id){
            if (currNode == head) {
                head = currNode->next;
            } else if (currNode == tail) {
                tail = prevNode->next;
            } else {
                prevNode->next = currNode->next;
            }
            free(currNode);
            length--;
            return true;
        }
        prevNode = currNode;
        currNode = currNode->next;
    }

    return false;
}

bool Annotations::updateAnnotation(int varId, QPolygonF varPosition){
    Annotation *currNode = new Annotation;
    Annotation *prevNode = new Annotation;

    currNode = head;
    for(int loopCount = 0; loopCount <= length; loopCount ++){
        if(varId == currNode->id){
            for(int loopCount = 0; loopCount < currNode->coordinates.size(); loopCount++){
                currNode->coordinates[loopCount].setX(varPosition[loopCount].x());
                currNode->coordinates[loopCount].setY(varPosition[loopCount].y());
            }
            return true;
        }
        prevNode = currNode;
        currNode = currNode->next;
    }
    return false;
}


void Annotations::deleteAllAnnotations()
{
    Annotation *currNode = new Annotation;
    Annotation *nextNode = new Annotation;

    currNode = head;

    while (currNode != NULL)
    {
        nextNode = currNode->next;
        free(currNode);
        currNode = nextNode;
    }
    length = 0;
    head = NULL;
}
