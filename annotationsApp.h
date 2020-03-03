#ifndef ANNOTATIONSAPP_H
#define ANNOTATIONSAPP_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class AnnotationsApp; }
QT_END_NAMESPACE

class AnnotationsApp : public QMainWindow
{
    Q_OBJECT

public:
    explicit AnnotationsApp(QWidget *parent = 0);
    ~AnnotationsApp();

private slots:
    void resizeImage();

    void resizeEvent(QResizeEvent*);

    void on_btnLoadImages_clicked();

    void on_btnAddClass_clicked();

    void on_btnDeleteClass_clicked();

    void on_btnLoadClasses_clicked();

    void on_btnLoadAnnotations_clicked();

    void on_btnSaveAnnotations_clicked();

    void on_btnRectangle_clicked();

    void on_btnTriangle_clicked();

    void on_btnTrapezium_clicked();

    void on_btnPolygon_clicked();

    void on_actionExit_triggered();

    void on_tblImages_cellClicked(int row, int column);

private:
    Ui::AnnotationsApp *ui;
};

#endif // ANNOTATIONSAPP_H
