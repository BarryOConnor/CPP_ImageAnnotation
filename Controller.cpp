#include "Controller.h"
#include "View.h"
#include "Model.h"
#include "Global_Enums.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QMessageBox>
#include <QInputDialog>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <QDebug>

Controller::Controller(View *varView, QWidget *varParent){
    classFileName = "";
    annotationFileName = "autosave.annotations";
    currentImageDir = "";
    model = new Model();

    view = varView; // pointer to the application UI
    parent = varParent; // pointer to the parent application
}

Controller::~Controller(){
    delete this;
}

void Controller::binarySearch(QVector<QPair<QString, QString>> *varContents, QString searchTerm){
/****************************************************
 * perform a binary search on the images list
 ***************************************************/
    int startPos = 0 ;
    int endPos = view->tblImages->rowCount() - 1;

    bubbleSort(*varContents,true,0);

    while (startPos <= endPos)
    {
        int midPos = startPos + (endPos - startPos) / 2;
        int result = varContents->at(midPos).first.indexOf(searchTerm);
                // Check if x is present at mid
        if (result != -1) { view->tblImages->selectRow(midPos); tblImages_cellClicked(midPos);return; }

        // If x greater, ignore left half
        if (searchTerm > varContents->at(midPos).first) { startPos = midPos + 1; }

        // If x is smaller, ignore right half
        else { endPos = midPos - 1; }
    }

    QMessageBox::information(parent, "Information","Unable to find Search term. Try searching for the beginning of the filename.");

}

void Controller::bubbleSort(QVector<QPair<QString, QString>>& varContents, bool varDirection, int varColumn){
/****************************************************
 * perform a bubblesort on a given table
 ***************************************************/
    typedef QVector<QString>::size_type size_type;
    for (size_type i = 1; i < varContents.size(); ++i) // for n-1 passes
    {
        for (size_type j = 0; j < (varContents.size() - 1); ++j)
        {
            if (varDirection) { //ascending
                QString compareFirst = "";
                QString compareSecond = "";
                if (varColumn == 0) { // sorting the first column
                    compareFirst = varContents[j].first;
                    compareSecond = varContents[j + 1].first;
                }
                else { //sorting the second column
                    compareFirst = varContents[j].second;
                    compareSecond = varContents[j + 1].second;
                }
                if (compareFirst > compareSecond) {
                    //swap items as needed
                    QPair<QString, QString> temp = { varContents[j].first, varContents[j].second };
                    varContents[j].first = varContents[j + 1].first;
                    varContents[j].second = varContents[j + 1].second;
                    varContents[j + 1].first = temp.first;
                    varContents[j + 1].second = temp.second;
                }
            }
            else {  //descending
                QString compareFirst = "";
                QString compareSecond = "";
                if (varColumn == 0) {// sorting the first column
                    compareFirst = varContents[j].first;
                    compareSecond = varContents[j + 1].first;
                }
                else {//sorting the second column
                    compareFirst = varContents[j].second;
                    compareSecond = varContents[j + 1].second;
                }
                if (compareFirst < compareSecond) {
                    //swap items as needed
                    QPair<QString, QString> temp = { varContents[j].first, varContents[j].second };
                    varContents[j].first = varContents[j + 1].first;
                    varContents[j].second = varContents[j + 1].second;
                    varContents[j + 1].first = temp.first;
                    varContents[j + 1].second = temp.second;
                }
            }
        }
    }
}

void Controller::populateTableView(QTableWidget* varTable, QVector<QPair<QString, QString>> varContents) {
 /****************************************************
 * populate a given tableview with content
 ***************************************************/

    //reset the table
    varTable->clearContents();
    varTable->setRowCount(0);
    int columns = varTable->columnCount();

    for (int loopCount = 0; loopCount < varContents.size(); loopCount++) {
        varTable->insertRow(varTable->rowCount()); //insert a row at the end of the list
        QTableWidgetItem* firstItem = new QTableWidgetItem(varContents[loopCount].first); //create an item to house the content
        firstItem->setFlags(firstItem->flags() ^ Qt::ItemIsEditable); //make sure the user can't edit the contents
        varTable->setItem(varTable->rowCount() - 1, 0, firstItem);
        if (columns > 1) {
            //add second col if it's the Images control
            QTableWidgetItem* secondItem = new QTableWidgetItem(varContents[loopCount].second);
            secondItem->setFlags(secondItem->flags() ^ Qt::ItemIsEditable);
            varTable->setItem(varTable->rowCount() - 1, 1, secondItem);
        }

    }
}


void Controller::tableHeading_clicked(QTableWidget* varTable, bool varDirection, int varColumn){
/****************************************************
 * handle the clicking of headers which allows the user to sort
 ***************************************************/

    QVector<QPair<QString, QString>> contents;  //vector of pairs to store contents

    //read the contents of the current QTableView into a vector for sorting
    int rows = varTable->rowCount();
    int columns = varTable->columnCount();

    for (int row = 0; row < rows; ++row) {
        if(columns > 1){
            contents.push_back({ varTable->item(row, 0)->text(),varTable->item(row, 1)->text() });
        } else {
            contents.push_back({ varTable->item(row, 0)->text(),"" });
        }
    }

    bubbleSort(contents, varDirection, varColumn);
    populateTableView(varTable, contents);
}



/*******************************
 *
 * SLOTS FROM AnnotationsApp
 *
 *******************************/


void Controller::btnLoadImages_clicked(){
/****************************************************
 * loads images from the computer into the application
 ***************************************************/

    //get the file name of the class
    QStringList images = QFileDialog::getOpenFileNames(parent, "Open Image File", "", "Image Files (*.png *.jpg *.gif)");

    if (images.isEmpty())
        return; //do nothing if the user selects nothing
    else {
        //reset the table
        view->tblImages->clearContents();
        view->tblImages->setRowCount(0);
        QVector<QPair<QString, QString>> contents;

        for ( const auto& image : images  ){
            currentImageDir = QFileInfo(image).path();
            QString filename = QFileInfo(image).fileName();
            QDateTime filedate = QFileInfo(image).lastModified();

            contents.push_back({ filename,filedate.toString("dd/MM/yyyy hh:mm") });
        }

        //populate the table
        populateTableView(view->tblImages, contents);

    }
}

void Controller::btnSearch_clicked(){
/****************************************************
 * perform a search on the images list on a given table
 ***************************************************/


    int rows = view->tblImages->rowCount();

    QVector<QPair<QString, QString>> *contents = new QVector<QPair<QString, QString>>;

    for (int row = 0; row < rows; ++row) {
        contents->push_back({ view->tblImages->item(row, 0)->text(),QString::number(row)});
    }

    binarySearch(contents, view->txtSearch->text());
}



void Controller::btnAddClass_clicked(){
/****************************************************
 * add classes to the class file
 ***************************************************/

    if (classFileName.isEmpty()){
        //sanity check in case the class file hasn't been set
        QMessageBox::information(parent, "Unable to open Class file","you must load a class file first");
        return;
    }

    bool ok; //bool to hold the return value from the dialog
    //create an input dialog asking for the class name
    QString newClassName = QInputDialog::getText(parent, "QInputDialog::getText()", "New Class name:", QLineEdit::Normal, QDir::home().dirName(), &ok);

    if (ok && !newClassName.isEmpty()){
        QFile classFile(classFileName);
        if (!classFile.open(QIODevice::Append | QIODevice::Text)) {
            QMessageBox::information(parent, "Unable to add Class", classFile.errorString());
            return;
        } else {
            //append the class name to the end of the file
            QTextStream outStream(&classFile);
            outStream << "\n" << newClassName;
            classFile.close();
            //add the new class name to the table
            view->tblClasses->insertRow ( view->tblClasses->rowCount() );
            QTableWidgetItem *item = new QTableWidgetItem(newClassName);
            item->setFlags(item->flags() ^ Qt::ItemIsEditable);
            view->tblClasses->setItem(view->tblClasses->rowCount()-1, 0, item);
        }
    }
}



void Controller::btnDeleteClass_clicked(){
/****************************************************
 * delete the selected class
 ***************************************************/

    if (classFileName.isEmpty()){
        //sanity check in case the class file hasn't been set
        QMessageBox::information(parent, "Unable to open Class file","you must load a class file first");
        return;
    }

    QFile classFile(classFileName);
    if (!classFile.open(QIODevice::ReadWrite | QIODevice::Text)) {
        QMessageBox::information(parent, "Unable to add Class", classFile.errorString());
        return;
    } else {
        QModelIndex currentIndex = view->tblClasses->currentIndex();
        QString outputString;
        QTextStream textStream(&classFile);
        while(!textStream.atEnd())
        {
            // check if the text is the deleted class
            QString line = textStream.readLine();
            if(!line.contains(view->tblClasses->item(currentIndex.row(), 0)->text())){
                outputString.append(line + "\n");
            } else {
                outputString.append("\n");
            }
        }
        classFile.resize(0);
        textStream << outputString;
        classFile.close();
    }
    int row = view->tblClasses->currentRow();
    view->tblClasses->removeRow(row);
    view->btnDeleteClass->setEnabled(false);
}



void Controller::btnLoadClasses_clicked(){
/****************************************************
 * import classes from a file into the application
 ***************************************************/

    //get the file name of the class
    classFileName = QFileDialog::getOpenFileName(parent, "Open Class File", "", "Class Files (*.names)");

    if (classFileName.isEmpty())
        return; //do nothing if the user selects nothing
    else {
        QFile classFile(classFileName);
        if (!classFile.open(QIODevice::ReadOnly)) {
            QMessageBox::information(parent, "Unable to open file", classFile.errorString());
            return;
        }

        //create a textstream to read the data from the file
        QTextStream in(&classFile);

        //reset the table

        view->tblClasses->clearContents();
        view->tblClasses->setRowCount(0);
        QVector<QPair<QString, QString>> contents;

        while (!in.atEnd()) {
            QString line = in.readLine();

            //add the contents of the file to the vector
            contents.push_back({ line,"" });
        }
        classFile.close();

        //populate the table
        populateTableView(view->tblClasses, contents);
        //model->setClasses(contents);

        //classes are now loaded so enable the buttons to add or delete
        view->btnAddClass->setEnabled(true);
    }
}



void Controller::btnLoadAnnotations_clicked(){
/****************************************************
 * load annotations from a file into the application
 ***************************************************/
    //get the file name of the class
    annotationFileName = QFileDialog::getOpenFileName(parent, "Open Annotation file", "", "Annotation Files (*.annotations)");

    if (annotationFileName.isEmpty())
        return; //do nothing if the user selects nothing

    QString val;
    QFile file;
    file.setFileName(annotationFileName);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    val = file.readAll();
    file.close();

    // if there are existing annotations, ask what the user wants to do with them
    if(model->hasAnnotations){
        QMessageBox msgBox;
        msgBox.setText(tr("You have existing Annotations. Do you want to discard these or append them to the imported Annotations?"));
        msgBox.addButton(tr("Append"), QMessageBox::YesRole);
        QAbstractButton* pButtonNo = msgBox.addButton(tr("Discard"), QMessageBox::NoRole);

        msgBox.exec();

        if (msgBox.clickedButton()==pButtonNo) { // user wants to disgard the existing annotations
            //empty the linked list and GraphicsScene before sontinuing
             model->deleteAnnotations();
             view->mainScene->update();
             view->mainScene->reset();
        }
    }

    model->loadAnnotations(QJsonDocument::fromJson(val.toUtf8()));

    view->mainScene->updateAnnotations(model->getAnnotationsForCurrentImage());
}



void Controller::btnSaveAnnotations_clicked(){
/****************************************************
 * save existing annotations to a file
 ***************************************************/
    QString saveAs = "myfile.annotations";
    if(model->hasAnnotations){
        if (annotationFileName != "autosave.annotations") saveAs = annotationFileName;
        QString fileName = QFileDialog::getSaveFileName(parent, "Save File",saveAs, "Annotation Files (*.annotations)");

        QFile file(fileName);
          if(file.open(QIODevice::WriteOnly | QIODevice::Text))
          {

              QTextStream stream(&file);

              // collect the required data from the model which stores the annotations list
              stream << model->saveAnnotations();

              file.close();

          }
          annotationFileName = fileName;
    }
}

void Controller::btnTriangle_clicked(){
/****************************************************
 * handle the click for the Triangle button
 ***************************************************/
    view->mainScene->setShape(Triangle);
    view->btnTriangle->setChecked(true);
    model->setCurrentShape(Triangle);
}

void Controller::btnRectangle_clicked(){
/****************************************************
 * handle the click for the Rectangle button
 ***************************************************/
    view->mainScene->setShape(Rectangle);
    view->btnRectangle->setChecked(true);
    model->setCurrentShape(Rectangle);
}

void Controller::btnTrapezium_clicked(){
/****************************************************
 * handle the click for the Trapezium button
 ***************************************************/
    view->mainScene->setShape(Trapezium);
    view->btnTrapezium->setChecked(true);
    model->setCurrentShape(Trapezium);
}

void Controller::btnPolygon_clicked(){
/****************************************************
 * handle the click for the Polygon button
 ***************************************************/
    view->mainScene->setShape(Polygon);
    view->btnPolygon->setChecked(true);
    model->setCurrentShape(Polygon);
}


void Controller::tblImages_cellClicked(int varRow){
/****************************************************
 * handles the display of images and loading associated annotations
 * when a user selects an image
 ***************************************************/

    QString imageToLoad = currentImageDir + "/" + view->tblImages->item(varRow, 0)->text();
    model->setCurrentImage(view->tblImages->item(varRow, 0)->text());

    //create a pixmap to send to the Graphics Scene
    QPixmap pix (imageToLoad);
    view->mainScene->clear();
    view->mainScene->setSceneRect(0,0,pix.width(),pix.height());
    view->mainScene->addPixmap(pix);
    view->mainScene->setImageLoaded(true);
    view->mainScene->setCurrentImage(pix);
    view->gvImage->setAlignment(Qt::AlignTop|Qt::AlignLeft);
    if (model->hasAnnotations){
        // load annotations
        view->mainScene->updateAnnotations(model->getAnnotationsForCurrentImage());
    }
}



void Controller::cboColor_currentIndexChanged(int varIndex){
/****************************************************
 * handle the user changing the color
 ***************************************************/

    view->mainScene->setColor(varIndex);
    model->setCurrentColor(varIndex);

}



void Controller::tblClasses_cellClicked(int varRow){
/****************************************************
 * the user has changed the class
 ***************************************************/
    QString className = view->tblClasses->item(varRow, 0)->text();
    model->setCurrentClass(className);
    view->btnDeleteClass->setEnabled(true);
    view->mainScene->setCurrentClass(className);
}


/*******************************
 *
 * SLOTS FROM GraphicsScene
 *
 *******************************/

void Controller::annotationReady(Annotation * varAnnotation){
/****************************************************
 * Signal from the GraphicsScene signalling that the user
 * has finished drawing a new annotation so store the
 * annotation in the linked list
 ***************************************************/
    model->createAnnotation(varAnnotation);
    view->btnTriangle->setChecked(false);
    view->btnRectangle->setChecked(false);
    view->btnTrapezium->setChecked(false);
    view->btnPolygon->setChecked(false);
}

void Controller::annotationDeleted(int varId){
/****************************************************
 * Signal from the GraphicsScene signalling that the user
 * has deleted an annotation so remove it from the linked list
 ***************************************************/

    model->deleteAnnotation(varId);
}

void Controller::updateItem(int varId, QPolygonF varPosition){
/****************************************************
 * Signal from the GraphicsScene signalling that the user
 * has moved a shape so update the position in the linked list
 ***************************************************/
    model->updateAnnotation(varId, varPosition);
}


