#include "annotationsApp.h"
#include "ui_annotationsApp.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QDateTime>
#include <QFileDialog>
#include <QInputDialog>
#include <QPixmap>
#include <QGraphicsScene>
#include <QDebug>
//opencv headers
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc.hpp"

QString classFileName = "";
QString currentImageDir = "";
QRect currentImageSize {0,0,0,0};
bool imageloaded = false;


void AnnotationsApp::resizeImage(){
    QSize size = this->size();
    int newWidth = 0;
    int newHeight = 0;


        if((size.width()-350 >= currentImageSize.width())){
            newWidth = currentImageSize.width();
            ui->gvImage->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        } else {
            newWidth = size.width()-350;
            ui->gvImage->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        }

        if((size.height()-90 >= currentImageSize.height())){
            newHeight = currentImageSize.height();
            ui->gvImage->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        } else {
            newHeight = size.height()-90;
            ui->gvImage->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        }

        ui->gvImage->setGeometry(0,0,newWidth, newHeight);

}


AnnotationsApp::AnnotationsApp(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AnnotationsApp)
{
    ui->setupUi(this);

   
}

AnnotationsApp::~AnnotationsApp()
{
    delete ui;
}

void AnnotationsApp::resizeEvent(QResizeEvent* event)
{
    QMainWindow::resizeEvent(event);
    qDebug() << currentImageSize;
    if(imageloaded){
        resizeImage();
    }



    //ui->gvImage->fitInView(, Qt::KeepAspectRatio);
}

void AnnotationsApp::on_btnLoadImages_clicked()
{
    //get the file name of the class
    QStringList images = QFileDialog::getOpenFileNames(this, tr("Open Image File"), "", tr("Image Files (*.png *.jpg *.gif)"));

    if (images.isEmpty())
        return; //do nothing if the user selects nothing
    else {
        //reset the table
        ui->tblImages->clearContents();
        ui->tblImages->setRowCount(0);
        for ( const auto& image : images  ){
			currentImageDir = QFileInfo(image).path();
            QString filename = QFileInfo(image).fileName();
            QDateTime filedate = QFileInfo(image).lastModified();
            ui->tblImages->insertRow ( ui->tblImages->rowCount() );
            QTableWidgetItem *fname = new QTableWidgetItem(filename);
            fname->setFlags(fname->flags() ^ Qt::ItemIsEditable);
            ui->tblImages->setItem(ui->tblImages->rowCount()-1, 0, fname);
            QTableWidgetItem *fdate = new QTableWidgetItem(filedate.toString("dd/MM/yyyy hh:mm"));
            fdate->setFlags(fdate->flags() ^ Qt::ItemIsEditable);
            ui->tblImages->setItem(ui->tblImages->rowCount()-1, 1, fdate);
        };

    };
}

void AnnotationsApp::on_btnAddClass_clicked()
{
    if (classFileName.isEmpty()){
        //sanity check in case the class file hasn't been set
        QMessageBox::information(this, tr("Unable to open Class file"),"you must load a class file first");
        return;
    }

    bool ok; //bool to hold the return value from the dialog
    //create an input dialog asking for the class name
    QString newClassName = QInputDialog::getText(this, tr("QInputDialog::getText()"), tr("New Class name:"), QLineEdit::Normal, QDir::home().dirName(), &ok);

    if (ok && !newClassName.isEmpty()){
        QFile classFile(classFileName);
        if (!classFile.open(QIODevice::Append | QIODevice::Text)) {
            QMessageBox::information(this, tr("Unable to add Class"),
            classFile.errorString());
            return;
        } else {
            //append the class name to the end of the file
            QTextStream outStream(&classFile);
            outStream << "\n" << newClassName;
            classFile.close();
            //add the new class name to the table
            ui->tblClasses->insertRow ( ui->tblClasses->rowCount() );
            QTableWidgetItem *item = new QTableWidgetItem(newClassName);
            item->setFlags(item->flags() ^ Qt::ItemIsEditable);
            ui->tblClasses->setItem(ui->tblClasses->rowCount()-1, 0, item);
        }
    }
}

void AnnotationsApp::on_btnDeleteClass_clicked()
{
    if (classFileName.isEmpty()){
        //sanity check in case the class file hasn't been set
        QMessageBox::information(this, tr("Unable to open Class file"),"you must load a class file first");
        return;
    }

    QFile classFile(classFileName);
    if (!classFile.open(QIODevice::ReadWrite | QIODevice::Text)) {
        QMessageBox::information(this, tr("Unable to add Class"),
        classFile.errorString());
        return;
    } else {
        QModelIndex currentIndex = ui->tblClasses->currentIndex();
        QString outputString;
        QTextStream textStream(&classFile);
        while(!textStream.atEnd())
        {
            QString line = textStream.readLine();
            if(!line.contains(ui->tblClasses->item(currentIndex.row(), 0)->text())){
                outputString.append(line + "\n");
            } else {
                outputString.append("\n");
            }
        }
        classFile.resize(0);
        textStream << outputString;
        classFile.close();
    }
    int row = ui->tblClasses->currentRow();
    ui->tblClasses->removeRow(row);
}

void AnnotationsApp::on_btnLoadClasses_clicked()
{
    //get the file name of the class
    classFileName = QFileDialog::getOpenFileName(this, tr("Open Class File"), "", tr("Class Files (*.names)"));

    if (classFileName.isEmpty())
        return; //do nothing if the user selects nothing
    else {
        QFile classFile(classFileName);
        if (!classFile.open(QIODevice::ReadOnly)) {
            QMessageBox::information(this, tr("Unable to open file"), classFile.errorString());
            return;
        }

        //create a textstream to rtead the data from the file
        QTextStream in(&classFile);

        //reset the table
        ui->tblClasses->clearContents();
        ui->tblClasses->setRowCount(0);

        while (!in.atEnd()) {
            QString line = in.readLine();

            //create a new row in the table, set the flags to make it non-editable and populate with the line from the file
            ui->tblClasses->insertRow ( ui->tblClasses->rowCount() );
            QTableWidgetItem *item = new QTableWidgetItem(line);
            item->setFlags(item->flags() ^ Qt::ItemIsEditable);
            ui->tblClasses->setItem(ui->tblClasses->rowCount()-1, 0, item);
        }
        classFile.close();

        //classes are now loaded so enable the buttons to add or delete
        ui->btnAddClass->setEnabled(true);
        ui->btnDeleteClass->setEnabled(true);
    }
}

void AnnotationsApp::on_btnLoadAnnotations_clicked()
{
	QMessageBox::information(this, tr("Information"), "Not Implemented");
}

void AnnotationsApp::on_btnSaveAnnotations_clicked()
{
	QMessageBox::information(this, tr("Information"), "Not Implemented");
}

void AnnotationsApp::on_btnRectangle_clicked()
{
	QMessageBox::information(this, tr("Information"), "Not Implemented");
}

void AnnotationsApp::on_btnTriangle_clicked()
{
	QMessageBox::information(this, tr("Information"), "Not Implemented");
}

void AnnotationsApp::on_btnTrapezium_clicked()
{
	QMessageBox::information(this, tr("Information"), "Not Implemented");
}

void AnnotationsApp::on_btnPolygon_clicked()
{
	QMessageBox::information(this, tr("Information"), "Not Implemented");
}

void AnnotationsApp::on_actionExit_triggered()
{
    QMessageBox::information(this, tr("Information"), "Not Implemented");
}

void AnnotationsApp::on_tblImages_cellClicked(int row, int column)
{
    QModelIndex currentIndex = ui->tblImages->currentIndex();
    //QMessageBox::information(this, tr("Information"), currentImageDir + "/" +ui->tblImages->item(currentIndex.row(), 0)->text());
    QString imageToLoad = currentImageDir + "/" + ui->tblImages->item(currentIndex.row(), 0)->text();

    QGraphicsScene *scene =  new QGraphicsScene;
    QPixmap pix (imageToLoad);
    currentImageSize = {0,0,pix.width(),pix.height()};
    scene->setSceneRect(0,0,pix.width(),pix.height());
    scene->addPixmap(pix);
    ui->gvImage->setScene(scene);
    imageloaded = true;
    resizeImage();
}
