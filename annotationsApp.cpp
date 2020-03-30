#include "annotationsApp.h"
#include "ui_annotationsApp.h"
#include "graphicsscene.h"

#include <QHeaderView>
#include <QTableView>
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
bool imageLoaded = false;

bool classSort = false;
bool imageSortCol1 = false;
bool imageSortCol2 = false;


void populateTableView(QTableWidget* thisTable, std::vector<std::pair<QString, QString>> contents, bool hasSecondCol) {
	//reset the table
	thisTable->clearContents();
	thisTable->setRowCount(0);

    for (unsigned int loopCount = 0; loopCount < contents.size(); loopCount++) {
		thisTable->insertRow(thisTable->rowCount());
		QTableWidgetItem* firstItem = new QTableWidgetItem(contents[loopCount].first);
		firstItem->setFlags(firstItem->flags() ^ Qt::ItemIsEditable);
		thisTable->setItem(thisTable->rowCount() - 1, 0, firstItem);
		if (hasSecondCol) {
			//add second col if it's the Images control
			QTableWidgetItem* secondItem = new QTableWidgetItem(contents[loopCount].second);
			secondItem->setFlags(secondItem->flags() ^ Qt::ItemIsEditable);
			thisTable->setItem(thisTable->rowCount() - 1, 1, secondItem);
		}

	}
}

void bubbleSort(std::vector<std::pair<QString, QString>>& contents, bool ascending, int column){

	typedef std::vector<std::string>::size_type size_type;
	for (size_type i = 1; i < contents.size(); ++i) // for n-1 passes
	{
		for (size_type j = 0; j < (contents.size() - 1); ++j)
		{
			if (ascending) {
				QString compareFirst = "";
				QString compareSecond = "";
				if (column == 0) {
					compareFirst = contents[j].first;
					compareSecond = contents[j + 1].first;
				}
				else {
					compareFirst = contents[j].second;
					compareSecond = contents[j + 1].second;
				}
				if (compareFirst > compareSecond) {
					std::pair<QString, QString> temp = { contents[j].first, contents[j].second };
					contents[j].first = contents[j + 1].first;
					contents[j].second = contents[j + 1].second;
					contents[j + 1].first = temp.first;
					contents[j + 1].second = temp.second;
				}
			}
			else {
				QString compareFirst = "";
				QString compareSecond = "";
				if (column == 0) {
					compareFirst = contents[j].first;
					compareSecond = contents[j + 1].first;
				}
				else {
					compareFirst = contents[j].second;
					compareSecond = contents[j + 1].second;
				}
				if (compareFirst < compareSecond) {
					std::pair<QString, QString> temp = { contents[j].first, contents[j].second };
					contents[j].first = contents[j + 1].first;
					contents[j].second = contents[j + 1].second;
					contents[j + 1].first = temp.first;
					contents[j + 1].second = temp.second;
				}
			}
		}
	}
}


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

        ui->gvImage->setGeometry(337,35,newWidth, newHeight);

}


AnnotationsApp::AnnotationsApp(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AnnotationsApp)
{
    ui->setupUi(this);
    ui->gvImage->setScene(mainScene);


    QHeaderView *classHeader = qobject_cast<QTableView *>(ui->tblClasses)->horizontalHeader();
    connect(classHeader, &QHeaderView::sectionClicked, [this](int logicalIndex){

		std::vector<std::pair<QString, QString>> contents;  //vector of pairs to store contents
		
		//read the conetents of the current QTableView into a vector for sorting
		int rows = ui->tblClasses->rowCount();
		for (int row = 0; row < rows; ++row) {
			contents.push_back({ ui->tblClasses->item(row, 0)->text(),"" });
		}
			
		bubbleSort(contents, classSort, logicalIndex);
		populateTableView(ui->tblClasses, contents, false);
		classSort = !classSort;
    });

    QHeaderView *imageHeader = qobject_cast<QTableView *>(ui->tblImages)->horizontalHeader();
    connect(imageHeader, &QHeaderView::sectionClicked, [this](int logicalIndex){
		std::vector<std::pair<QString, QString>> contents;  //vector of pairs to store contents

		//read the conetents of the current QTableView into a vector for sorting
		int rows = ui->tblImages->rowCount();
		for (int row = 0; row < rows; ++row) {
			contents.push_back({ ui->tblImages->item(row, 0)->text(),ui->tblImages->item(row, 1)->text() });
		}
		
		if (logicalIndex == 0) {
			bubbleSort(contents, imageSortCol1, logicalIndex);
			imageSortCol1 = !imageSortCol1;
		} else {
			bubbleSort(contents, imageSortCol2, logicalIndex);
			imageSortCol2 = !imageSortCol2;
		}
		populateTableView(ui->tblImages, contents, true);
    });

   
}

AnnotationsApp::~AnnotationsApp()
{
    delete ui;
}

void AnnotationsApp::resizeEvent(QResizeEvent* event)
{
    QMainWindow::resizeEvent(event);
    if( mainScene->getImageLoaded() ){
        resizeImage();
    }
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
		std::vector<std::pair<QString, QString>> contents;

        for ( const auto& image : images  ){
			currentImageDir = QFileInfo(image).path();
            QString filename = QFileInfo(image).fileName();
            QDateTime filedate = QFileInfo(image).lastModified();

			contents.push_back({ filename,filedate.toString("dd/MM/yyyy hh:mm") });
		}

		//populate the table
		populateTableView(ui->tblImages, contents, true);

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
		std::vector<std::pair<QString, QString>> contents;

        while (!in.atEnd()) {
            QString line = in.readLine();

            //add the contents of the file to the vector
			contents.push_back({ line,"" });
        }
        classFile.close();

		//populate the table
		populateTableView(ui->tblClasses, contents, false);

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

void AnnotationsApp::on_actionExit_triggered()
{
    QMessageBox::information(this, tr("Information"), "Not Implemented");
}

void AnnotationsApp::on_tblImages_cellClicked(int row, int column)
{

    QString imageToLoad = currentImageDir + "/" + ui->tblImages->item(row, 0)->text();


    QPixmap pix (imageToLoad);
    currentImageSize = {0,0,pix.width(),pix.height()};
    ui->gvImage->scene()->clear();
    ui->gvImage->scene()->setSceneRect(0,0,pix.width(),pix.height());
    ui->gvImage->scene()->addPixmap(pix);
    mainScene->setImageLoaded(true);
    mainScene->setCurrentImage(pix);
    resizeImage();
}





void AnnotationsApp::on_cvShapes_currentIndexChanged(int index)
{
    mainScene->newShape();
    switch(index) {
        case 0:
            //polygon
            mainScene->setMaxPoints(8);
            break;
        case 1:
            //polygon
            mainScene->setMaxPoints(3);
            break;
        case 2:
        case 3:
        case 4:
            //polygon
            mainScene->setMaxPoints(4);
            break;

    }

}

void AnnotationsApp::on_tblClasses_cellClicked(int row, int column)
{
    mainScene->setCurrentClass(ui->tblClasses->item(row, 0)->text());
}
