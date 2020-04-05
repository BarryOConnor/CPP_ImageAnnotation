#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "ui_AnnotationsApp.h"
#include "Annotation.h"
#include "Model.h"
#include "GraphicsScene.h"

#include <QTableWidget>
#include <QMainWindow>

class Controller : public QObject
{
    Q_OBJECT

public:
    void initialise(Ui::AnnotationsApp *newView);
    void sortTableView(QTableWidget* thisTable, bool varDirection, int varColumn);

    Controller();
    ~Controller();

public slots:

    void tableHeading_clicked(QTableWidget* varTable, bool varDirection, int varColumn);
    void btnLoadImages_clicked();
    void btnAddClass_clicked();
    void btnDeleteClass_clicked();
    void btnLoadClasses_clicked();
    void btnLoadAnnotations_clicked();
    void btnSaveAnnotations_clicked();
    void tblImages_cellClicked(int row);
    void tblClasses_cellClicked(int row);
    void btnTriangle_clicked();
    void btnRectangle_clicked();
    void btnTrapezium_clicked();
    void btnPolygon_clicked();

    void cboColor_currentIndexChanged(int varIndex);
    void annotationReady(Annotation *varAnnotation);
    void annotationDeleted(int varId);
    void updateItem(int varId, QPolygonF varPosition);

signals:
    //void valueChanged(int newValue);

private:
    void bubbleSort(QVector<QPair<QString, QString>>& varContents, bool varDirection, int varColumn);
    void populateTableView(QTableWidget* varTable, QVector<QPair<QString, QString>> varContents);
    QString classFileName;
    QString annotationFileName;
    QString currentImageDir;


    Ui::AnnotationsApp *view;
    Model *model;
};

#endif // CONTROLLER_H
