#include "Controller.h"
#include "ui_AnnotationsApp.h"
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


Controller::Controller(){
    classFileName = "";
    annotationFileName = "";
    currentImageDir = "";
    model = new Model();
}

Controller::~Controller(){
    delete this;
}

void Controller::bubbleSort(QVector<QPair<QString, QString>>& varContents, bool varDirection, int varColumn){

    typedef QVector<QString>::size_type size_type;
    for (size_type i = 1; i < varContents.size(); ++i) // for n-1 passes
    {
        for (size_type j = 0; j < (varContents.size() - 1); ++j)
        {
            if (varDirection) { //ascending
                QString compareFirst = "";
                QString compareSecond = "";
                if (varColumn == 0) {
                    compareFirst = varContents[j].first;
                    compareSecond = varContents[j + 1].first;
                }
                else {
                    compareFirst = varContents[j].second;
                    compareSecond = varContents[j + 1].second;
                }
                if (compareFirst > compareSecond) {
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
                if (varColumn == 0) {
                    compareFirst = varContents[j].first;
                    compareSecond = varContents[j + 1].first;
                }
                else {
                    compareFirst = varContents[j].second;
                    compareSecond = varContents[j + 1].second;
                }
                if (compareFirst < compareSecond) {
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
    //reset the table
    varTable->clearContents();
    varTable->setRowCount(0);
    int columns = varTable->columnCount();

    for (int loopCount = 0; loopCount < varContents.size(); loopCount++) {
        varTable->insertRow(varTable->rowCount());
        QTableWidgetItem* firstItem = new QTableWidgetItem(varContents[loopCount].first);
        firstItem->setFlags(firstItem->flags() ^ Qt::ItemIsEditable);
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
    //get the file name of the class
    QStringList images = QFileDialog::getOpenFileNames(nullptr, "Open Image File", "", "Image Files (*.png *.jpg *.gif)");

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



void Controller::btnAddClass_clicked(){
    if (classFileName.isEmpty()){
        //sanity check in case the class file hasn't been set
        QMessageBox::information(nullptr, "Unable to open Class file","you must load a class file first");
        return;
    }

    bool ok; //bool to hold the return value from the dialog
    //create an input dialog asking for the class name
    QString newClassName = QInputDialog::getText(nullptr, "QInputDialog::getText()", "New Class name:", QLineEdit::Normal, QDir::home().dirName(), &ok);

    if (ok && !newClassName.isEmpty()){
        QFile classFile(classFileName);
        if (!classFile.open(QIODevice::Append | QIODevice::Text)) {
            QMessageBox::information(nullptr, "Unable to add Class", classFile.errorString());
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
    if (classFileName.isEmpty()){
        //sanity check in case the class file hasn't been set
        QMessageBox::information(nullptr, "Unable to open Class file","you must load a class file first");
        return;
    }

    QFile classFile(classFileName);
    if (!classFile.open(QIODevice::ReadWrite | QIODevice::Text)) {
        QMessageBox::information(nullptr, "Unable to add Class", classFile.errorString());
        return;
    } else {
        QModelIndex currentIndex = view->tblClasses->currentIndex();
        QString outputString;
        QTextStream textStream(&classFile);
        while(!textStream.atEnd())
        {
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
    //get the file name of the class
    classFileName = QFileDialog::getOpenFileName(nullptr, "Open Class File", "", "Class Files (*.names)");

    if (classFileName.isEmpty())
        return; //do nothing if the user selects nothing
    else {
        QFile classFile(classFileName);
        if (!classFile.open(QIODevice::ReadOnly)) {
            QMessageBox::information(nullptr, "Unable to open file", classFile.errorString());
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
    //get the file name of the class
    annotationFileName = QFileDialog::getOpenFileName(nullptr, "Open Annotation file", "", "Annotation Files (*.annotations)");

    if (annotationFileName.isEmpty())
        return; //do nothing if the user selects nothing

    QString val;
    QFile file;
    file.setFileName(annotationFileName);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    val = file.readAll();
    file.close();

    if(model->hasAnnotations){
        QMessageBox msgBox;
        msgBox.setText(tr("You have existing Annotations. Do you want to discard these or append them to the imported Annotations?"));
        msgBox.addButton(tr("Append"), QMessageBox::YesRole);
        QAbstractButton* pButtonNo = msgBox.addButton(tr("Discard"), QMessageBox::NoRole);

        msgBox.exec();

        if (msgBox.clickedButton()==pButtonNo) {
             model->deleteAnnotations();
             view->mainScene->update();
             view->mainScene->reset();
        }
    }

    model->loadAnnotations(QJsonDocument::fromJson(val.toUtf8()));

    view->mainScene->updateAnnotations(model->getAnnotationsForCurrentImage());
}



void Controller::btnSaveAnnotations_clicked(){
    QString saveAs = "myfile.annotations";

    if (annotationFileName != "") saveAs = annotationFileName;
    QString fileName = QFileDialog::getSaveFileName(nullptr, tr("Save File"),saveAs,
                               tr("Annotation Files (*.annotations)"));
    QFile file(fileName);
          if(file.open(QIODevice::WriteOnly | QIODevice::Text))
          {

              QTextStream stream(&file);

              stream << model->saveAnnotations();

              file.close();

          }
}

void Controller::btnTriangle_clicked()
{
    view->mainScene->setShape(Triangle);
    view->btnTriangle->setChecked(true);
    model->setCurrentShape(Triangle);
}

void Controller::btnRectangle_clicked()
{
    view->mainScene->setShape(Rectangle);
    view->btnRectangle->setChecked(true);
    model->setCurrentShape(Rectangle);
}

void Controller::btnTrapezium_clicked()
{
    view->mainScene->setShape(Trapezium);
    view->btnTrapezium->setChecked(true);
    model->setCurrentShape(Trapezium);
}

void Controller::btnPolygon_clicked()
{
    view->mainScene->setShape(Polygon);
    view->btnPolygon->setChecked(true);
    model->setCurrentShape(Polygon);
}


void Controller::initialise(Ui::AnnotationsApp *varView){
    view = varView;
}


void Controller::tblImages_cellClicked(int varRow){

    QString imageToLoad = currentImageDir + "/" + view->tblImages->item(varRow, 0)->text();
    model->setCurrentImage(view->tblImages->item(varRow, 0)->text());
    QPixmap pix (imageToLoad);
    view->mainScene->clear();
    view->mainScene->setSceneRect(0,0,pix.width(),pix.height());
    view->mainScene->addPixmap(pix);
    view->mainScene->setImageLoaded(true);
    view->mainScene->setCurrentImage(pix);
    view->gvImage->setAlignment(Qt::AlignTop|Qt::AlignLeft);
    if (model->hasAnnotations){
        view->mainScene->updateAnnotations(model->getAnnotationsForCurrentImage());
    }
}



void Controller::cboColor_currentIndexChanged(int varIndex){

    view->mainScene->setColor(varIndex);
    model->setCurrentColor(varIndex);

}



void Controller::tblClasses_cellClicked(int varRow){
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
    model->createAnnotation(varAnnotation);
    view->btnTriangle->setChecked(false);
    view->btnRectangle->setChecked(false);
    view->btnTrapezium->setChecked(false);
    view->btnPolygon->setChecked(false);
}

void Controller::annotationDeleted(int varId)
{
    model->deleteAnnotation(varId);
}

void Controller::updateItem(int varId, QPolygonF varPosition)
{
    model->updateAnnotation(varId, varPosition);
}


