#include "bubblesort.h"
#include <QDateTime>
#include <QDebug>

void bubbleSort(QVector<QPair<QString, QString>>& varContents, bool varDirection, int varColumn){
/****************************************************
 * perform a bubblesort on a given table
 ***************************************************/
    //check contents have been
    if(varContents.length() < 1 )
        throw std::invalid_argument("No contents in the vector to sort");




    QPair<QString, QString> tempStore; //temporary storage for swap item
    bool doSwap = false; // should we swap the items

    using size_type = QVector<QString>::size_type;

    for (size_type i = 1; i < varContents.size(); ++i) // for n-1 passes
    {
        for (size_type j = 0; j < (varContents.size() - 1); ++j)
        {
            doSwap = false;

            // variables need to be declared inside the if statements since we could be dealing with a comparison of a date or a string
            // sorting dates in string format just doesn't work correctly so we need to convert

            if (varColumn == 0) { // sorting by the first column
                QString compareFirst = varContents[j].first;
                QString compareSecond = varContents[j + 1].first;

                //if ascending comparison works one direction, descending the other direction
                if ((compareFirst > compareSecond && varDirection) || (compareFirst < compareSecond && !varDirection)) {
                    doSwap = true;
                }

            } else { //sorting by the second (date) column
                QDateTime compareFirst = QDateTime::fromString(varContents[j].second, "dd/MM/yyyy hh:mm");
                QDateTime compareSecond = QDateTime::fromString(varContents[j + 1].second, "dd/MM/yyyy hh:mm");

                //if ascending comparison works one direction, descending the other direction
                if ((compareFirst > compareSecond && varDirection) || (compareFirst < compareSecond && !varDirection)) {
                    doSwap = true;
                }
            }
            if(doSwap){
                tempStore = varContents[j];
                varContents[j] = varContents[j + 1];
                varContents[j + 1] = tempStore;
            }
        }
    }
}
