#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
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

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
