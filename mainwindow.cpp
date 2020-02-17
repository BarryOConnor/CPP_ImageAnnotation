#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

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
    QMessageBox msgBox;
    msgBox.setText("Loading Images.");
    msgBox.exec();
}

void MainWindow::on_btnAddClass_clicked()
{
    QMessageBox msgBox;
    msgBox.setText("Adding a Class.");
    msgBox.exec();
}

void MainWindow::on_btnDeleteClass_clicked()
{
    QMessageBox msgBox;
    msgBox.setText("Deleting a Class.");
    msgBox.exec();
}

void MainWindow::on_btnLoadClasses_clicked()
{
    QMessageBox msgBox;
    msgBox.setText("Loading Classes.");
    msgBox.exec();
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
