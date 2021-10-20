#include "annotations.h"

#include <QDebug>
#include <QPolygonF>

Annotations::Annotations(){
    length = 0;
    head = nullptr;
    tail = nullptr;
}

Annotations::~Annotations(){
    delete this;
}

void Annotations::display(){
/****************************************************
 * display the contents of the linked List for debug
 ***************************************************/
    Annotation *temp=new Annotation;

    temp=head;

    while(temp!=nullptr)
    {
        qDebug() << temp->id << "\t";
        qDebug() << temp->classname << "\t";
        qDebug() << temp->image << "\t";
        qDebug() << temp->shape << "\t";
        qDebug() << temp->color << "\t";
        qDebug() << temp->coordinates << "\t";
        qDebug() << " " << "\t";
        temp=temp->next;

    }
}



void Annotations::appendAnnotation(Annotation *varAnnotation){
/****************************************************
 * dappend an annotation to the linkedlist
 ***************************************************/

    varAnnotation->next = nullptr;
    if(head == nullptr){
        head = varAnnotation;
        tail = varAnnotation;
        varAnnotation = nullptr;
    } else {
        tail->next = varAnnotation;
        tail = varAnnotation;
    }
    length++;

}


QVector<Annotation *> Annotations::searchByImage(const QString &varImage) {
/****************************************************
 * search the list for a given image
 ***************************************************/
    Annotation *currNode = new Annotation();
    QVector<Annotation*> annotationList;

    currNode = head;
    while (currNode != nullptr) {
        if(currNode->image == varImage) {
            annotationList.push_back(currNode);
        }
        currNode = currNode->next;
    }
    return annotationList;
}

bool Annotations::deleteWithId(int varId){
/****************************************************
 * delete an annotation with a specified ID
 ***************************************************/
    Annotation *currNode = new Annotation;
    Annotation *prevNode = new Annotation;

    currNode = head;
    for(int loopCount = 0; loopCount <= length; loopCount ++){
        if(varId == currNode->id){
            if (currNode == head) {
                head = currNode->next;
            } else if (currNode == tail) {
                tail = prevNode;
                prevNode->next = nullptr;
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
/****************************************************
 * update an annotation after it has been moved by a user
 ***************************************************/
    Annotation *currNode = new Annotation;

    currNode = head;
    for(int loopCount = 0; loopCount <= length; loopCount ++){
        if(varId == currNode->id){
            for(int loopCount = 0; loopCount < currNode->coordinates.size(); loopCount++){
                currNode->coordinates[loopCount].setX(varPosition[loopCount].x());
                currNode->coordinates[loopCount].setY(varPosition[loopCount].y());
            }
            return true;
        }
        currNode = currNode->next;
    }
    return false;
}


void Annotations::deleteAllAnnotations(){
/****************************************************
 * clear the list of all annotations
 ***************************************************/

    Annotation *currNode = new Annotation;
    Annotation *nextNode = new Annotation;

    currNode = head;

    while (currNode != nullptr)
    {
        nextNode = currNode->next;
        free(currNode);
        currNode = nextNode;
    }
    length = 0;
    head = nullptr;
}

