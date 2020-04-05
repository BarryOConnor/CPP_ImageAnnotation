#ifndef ANNOTATIONSAPP_H
#define ANNOTATIONSAPP_H
#include "Controller.h"
#include "ui_AnnotationsApp.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Ui_AnnotationsApp; }
QT_END_NAMESPACE

class AnnotationsApp : public QMainWindow
{
    Q_OBJECT

public:
    explicit AnnotationsApp(QWidget *parent = 0);
    ~AnnotationsApp();


private slots:

    void resizeEvent(QResizeEvent*);

    void on_btnLoadImages_clicked();

    void on_btnAddClass_clicked();

    void on_btnDeleteClass_clicked();

    void on_btnLoadClasses_clicked();

    void on_btnLoadAnnotations_clicked();

    void on_btnSaveAnnotations_clicked();

    void on_tblImages_cellClicked(int row, int column);

    void on_tblClasses_cellClicked(int row, int column);

    void on_btnTriangle_clicked();

    void on_btnRectangle_clicked();

    void on_btnTrapezium_clicked();

    void on_btnPolygon_clicked();

    void on_cboColor_currentIndexChanged(int index);

signals:
    void tableHeading_clicked(QTableWidget* varTable, bool varDirection, int carColumn);

    void btnLoadImages_clicked();

    void btnAddClass_clicked();

    void btnDeleteClass_clicked();

    void btnLoadClasses_clicked();

    void btnLoadAnnotations_clicked();

    void btnSaveAnnotations_clicked();

    void tblImages_cellClicked(int varRow);

    void tblClasses_cellClicked(int varRow);

    void btnTriangle_clicked();

    void btnRectangle_clicked();

    void btnTrapezium_clicked();

    void btnPolygon_clicked();

    void cboColor_currentIndexChanged(int varIndex);

private:
    Ui::AnnotationsApp *view;

};

#endif // ANNOTATIONSAPP_H
