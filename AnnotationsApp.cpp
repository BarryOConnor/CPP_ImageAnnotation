#include "AnnotationsApp.h"
#include "Controller.h"
#include "AutoSave.h"
#include <QThread>
#include <QTimer>

Controller *controller;
AutoSave * autosave;
View *view;

QString classFileName = "";
QString currentImageDir = "";

bool imageLoaded = false;
bool classSort = false;
bool imageSortCol1 = false;
bool imageSortCol2 = false;

QString toQssFormat(const QColor &color)
{
    return QString("rgba(%1, %2, %3, %4)")
            .arg(color.red())
            .arg(color.green())
            .arg(color.blue())
            .arg(color.alpha());
}



AnnotationsApp::AnnotationsApp(QWidget *parent) : QMainWindow(parent)
{
    view = new View();
    //setup the application UI
    view->setupUi(this);

    //pass some handles to the controller so it will work correctly
    controller = new Controller(view, this);

    autosave = new AutoSave();
    QThread *autosaveThread = new QThread();
    autosave->moveToThread(autosaveThread);
    autosaveThread->start();

    //set up some basic color styles to keep the highlighted items blue
    QStringList styles;

    // Force views to highlight the selected rows even when the view does not have focus.
    QString fg = toQssFormat( palette().color( QPalette::Active, QPalette::HighlightedText ) );
    QString bg = toQssFormat( palette().color( QPalette::Active, QPalette::Highlight ) );

    styles << QString( "QTableView:!active { selection-color: %1; selection-background-color: %2; }" )
    .arg( fg )
    .arg( bg );

    setStyleSheet( styles.join( " " ) );

    //set up some signals between components to allow them to communicate
    //AnnotationsApp -> Controller signals
    QObject::connect(this, &AnnotationsApp::btnLoadImages_clicked, controller, &Controller::btnLoadImages_clicked);
    QObject::connect(this, &AnnotationsApp::btnAddClass_clicked, controller, &Controller::btnAddClass_clicked);
    QObject::connect(this, &AnnotationsApp::btnDeleteClass_clicked, controller, &Controller::btnDeleteClass_clicked);
    QObject::connect(this, &AnnotationsApp::btnLoadClasses_clicked, controller, &Controller::btnLoadClasses_clicked);
    QObject::connect(this, &AnnotationsApp::btnLoadAnnotations_clicked, controller, &Controller::btnLoadAnnotations_clicked);
    QObject::connect(this, &AnnotationsApp::btnSaveAnnotations_clicked, controller, &Controller::btnSaveAnnotations_clicked);
    QObject::connect(this, &AnnotationsApp::tblImages_cellClicked, controller, &Controller::tblImages_cellClicked);
    QObject::connect(this, &AnnotationsApp::cboColor_currentIndexChanged, controller, &Controller::cboColor_currentIndexChanged);
    QObject::connect(this, &AnnotationsApp::tblClasses_cellClicked, controller, &Controller::tblClasses_cellClicked);
    QObject::connect(this, &AnnotationsApp::tableHeading_clicked, controller, &Controller::tableHeading_clicked);
    QObject::connect(this, &AnnotationsApp::btnTriangle_clicked, controller, &Controller::btnTriangle_clicked);
    QObject::connect(this, &AnnotationsApp::btnRectangle_clicked, controller, &Controller::btnRectangle_clicked);
    QObject::connect(this, &AnnotationsApp::btnTrapezium_clicked, controller, &Controller::btnTrapezium_clicked);
    QObject::connect(this, &AnnotationsApp::btnPolygon_clicked, controller, &Controller::btnPolygon_clicked);
    QObject::connect(this, &AnnotationsApp::btnSearch_clicked, controller, &Controller::btnSearch_clicked);

    //GraphicsScene -> Controller signals
    QObject::connect(view->mainScene, &GraphicsScene::annotationReady, controller, &Controller::annotationReady);
    QObject::connect(view->mainScene, &GraphicsScene::annotationDeleted, controller, &Controller::annotationDeleted);
    QObject::connect(view->mainScene, &GraphicsScene::updateItem, controller, &Controller::updateItem);

    //AutoSave-> Model and reply
    QObject::connect(autosave, &AutoSave::getSaveData, controller->model, &Model::prepareAutosaveData);
    QObject::connect(controller->model, &Model::saveDataReady, autosave, &AutoSave::saveDataReady);

    //setup the header buttons to connect to a sort algorithm for the tblClasses TblView
    QHeaderView *classHeader = qobject_cast<QTableView *>(view->tblClasses)->horizontalHeader();
    connect(classHeader, &QHeaderView::sectionClicked, [this](int logicalIndex){

        emit tableHeading_clicked(view->tblClasses, classSort, logicalIndex);
        classSort = !classSort;

    });

    //setup the header buttons to connect to a sort algorithm for the tblImages TblView
    QHeaderView *imageHeader = qobject_cast<QTableView *>(view->tblImages)->horizontalHeader();
    connect(imageHeader, &QHeaderView::sectionClicked, [this](int logicalIndex){


        if (logicalIndex == 0) {
            emit tableHeading_clicked(view->tblImages, imageSortCol1, logicalIndex);
            imageSortCol1 = !imageSortCol1;
        } else {
            emit tableHeading_clicked(view->tblImages, imageSortCol2, logicalIndex);
            imageSortCol2 = !imageSortCol2;
        }

    });


}

AnnotationsApp::~AnnotationsApp()
{
    delete view;
}

void AnnotationsApp::resizeEvent(QResizeEvent* varEvent)
{
    QMainWindow::resizeEvent(varEvent);
}

void AnnotationsApp::on_btnLoadImages_clicked()
{
    emit btnLoadImages_clicked();
}

void AnnotationsApp::on_btnAddClass_clicked()
{
    emit btnAddClass_clicked();
}

void AnnotationsApp::on_btnDeleteClass_clicked()
{
    emit btnDeleteClass_clicked();
}

void AnnotationsApp::on_btnLoadClasses_clicked()
{
    emit btnLoadClasses_clicked();
}

void AnnotationsApp::on_btnLoadAnnotations_clicked()
{
    emit btnLoadAnnotations_clicked();
}

void AnnotationsApp::on_btnSaveAnnotations_clicked()
{
    emit btnSaveAnnotations_clicked();
}

void AnnotationsApp::on_tblImages_cellClicked(int varRow, int varColumn)
{
    emit tblImages_cellClicked(varRow);
}




void AnnotationsApp::on_tblClasses_cellClicked(int varRow, int varColumn)
{
    emit tblClasses_cellClicked(varRow);
}



void AnnotationsApp::on_btnTriangle_clicked()
{
    emit btnTriangle_clicked();
}

void AnnotationsApp::on_btnRectangle_clicked()
{
    emit btnRectangle_clicked();
}

void AnnotationsApp::on_btnTrapezium_clicked()
{
    emit btnTrapezium_clicked();
}

void AnnotationsApp::on_btnPolygon_clicked()
{
    emit btnPolygon_clicked();
}

void AnnotationsApp::on_cboColor_currentIndexChanged(int varIndex)
{
    emit cboColor_currentIndexChanged(varIndex);
}

void AnnotationsApp::on_btnSearch_clicked()
{
    emit btnSearch_clicked();
}
