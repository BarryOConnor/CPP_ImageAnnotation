#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QFileDialog>
#include <QInputDialog>

QString classFileName = "";


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnLoadImages_clicked()
{
    QMessageBox::information(this, "information","Loading Images.");
}

void MainWindow::on_btnAddClass_clicked()
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

void MainWindow::on_btnDeleteClass_clicked()
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

void MainWindow::on_btnLoadClasses_clicked()
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

void MainWindow::on_btnLoadAnnotations_clicked()
{
    QMessageBox msgBox;
    msgBox.setText("Loading Annotations.");
    msgBox.exec();
}

void MainWindow::on_btnSaveAnnotations_clicked()
{
    QMessageBox msgBox;
    msgBox.setText("Saving Annotations.");
    msgBox.exec();
}

void MainWindow::on_btnRectangle_clicked()
{
    QMessageBox msgBox;
    msgBox.setText("Rectangle.");
    msgBox.exec();
}

void MainWindow::on_btnTriangle_clicked()
{
    QMessageBox msgBox;
    msgBox.setText("Triangle.");
    msgBox.exec();
}

void MainWindow::on_btnTrapezium_clicked()
{
    QMessageBox msgBox;
    msgBox.setText("Trapezium.");
    msgBox.exec();
}

void MainWindow::on_btnPolygon_clicked()
{
    QMessageBox msgBox;
    msgBox.setText("Polygon.");
    msgBox.exec();
}

void MainWindow::on_actionExit_triggered()
{
    QMessageBox msgBox;
    msgBox.setText("Exit clicked.");
    msgBox.exec();
}
