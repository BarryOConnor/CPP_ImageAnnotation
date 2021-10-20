#include "binarysearch.h"
#include "bubblesort.h"
#include <QDebug>

QString binarySearch(QVector<QPair<QString, QString>> *varContents, const QString &searchTerm){
/****************************************************
 * perform a binary search on the images list
 ***************************************************/
    int startPos = 0 ;
    int endPos = varContents->length() - 1;

    for(int i = 0; i < varContents->size(); i++)
    {
         //qDebug() << varContents->at(i).first << ", " << varContents->at(i).second << endl;
    }

    bubbleSort(*varContents,true,0);
    //qDebug() << "after sorting";
    for(int i = 0; i < varContents->size(); i++)
    {
         //qDebug() << varContents->at(i).first << ", " << varContents->at(i).second << endl;
    }

    while (startPos <= endPos)
    {
        int midPos = startPos + (endPos - startPos) / 2;
        int result = varContents->at(midPos).first.indexOf(searchTerm);
        //qDebug() << startPos << " : " << varContents->at(midPos).first;
                // Check if x is present at mid
        if (result != -1) { return varContents->at(midPos).first; }

        // If x greater, ignore left half
        if (searchTerm > varContents->at(midPos).first) { startPos = midPos + 1;}

        // If x is smaller, ignore right half
        else { endPos = midPos - 1; }
    }
    return "no match";
}

