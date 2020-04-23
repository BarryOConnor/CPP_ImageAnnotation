#ifndef ANNOTATIONSAPP_H
#define ANNOTATIONSAPP_H
#include "controller.h"
#include "view.h"
#include <QMainWindow>


//!  Application level class.
/*!
  Inbuilt QT class which runs the application
*/
class AnnotationsApp : public QMainWindow
{
    Q_OBJECT

public:
    //!  default constructor.
    /*!
      \param *parent pointer to the parent widget
    */
    explicit AnnotationsApp(QWidget *parent = 0);

    //! default destructor
    ~AnnotationsApp();


private slots:

    //! resize event for when the application is rezised
    /*!
      \param *pointer to a QResizeEvent
    */
    void resizeEvent(QResizeEvent*);

    //! click event handler for the Load Images button
    void on_btnLoadImages_clicked();

    //! click event handler for the Add Class button
    void on_btnAddClass_clicked();

    //! click event handler for the Delete Class button
    void on_btnDeleteClass_clicked();

    //! click event handler for the Load CLasses button
    void on_btnLoadClasses_clicked();

    //! click event handler for the Load Annotations button
    void on_btnLoadAnnotations_clicked();

    //! click event handler for the Save Annotations button
    void on_btnSaveAnnotations_clicked();

    //! click event for the Images listbox
    /*!
      \param row int representing the row that was clicked
      \param column int representing the column that was clicked
    */
    void on_tblImages_cellClicked(int row, int column);

    //! click event for the Classes listbox
    /*!
      \param row int representing the row that was clicked
      \param column int representing the column that was clicked
    */
    void on_tblClasses_cellClicked(int row, int column);

    //! click event handler for the Triangle button
    void on_btnTriangle_clicked();

    //! click event handler for the Rectangle button
    void on_btnRectangle_clicked();

    //! click event handler for the Trapezium button
    void on_btnTrapezium_clicked();

    //! click event handler for the Polygon button
    void on_btnPolygon_clicked();

    //! click event for the Color combobox
    /*!
      \param index the selected index of the selected item
    */
    void on_cboColor_currentIndexChanged(int index);

    //! click event handler for the Search button
    void on_btnSearch_clicked();

signals:
    void tableHeading_clicked(QTableWidget* varTable, bool varDirection, int carColumn);

    //! emits a signal to the controller when Load Images button is clicked
    void btnLoadImages_clicked();

    //! emits a signal to the controller when Add Class button is clicked
    void btnAddClass_clicked();

    //! emits a signal to the controller when Delete Class button is clicked
    void btnDeleteClass_clicked();

    //! emits a signal to the controller when Load Class button is clicked
    void btnLoadClasses_clicked();

    //! emits a signal to the controller when Load Annotations button is clicked
    void btnLoadAnnotations_clicked();

    //! emits a signal to the controller when Save Annotations button is clicked
    void btnSaveAnnotations_clicked();

    //! emits a signal to the controller when Images listbox is clicked
    /*!
      \param row int representing the row that was clicked
    */
    void tblImages_cellClicked(int varRow);

    //! emits a signal to the controller when Classes listbox is clicked
    /*!
      \param row int representing the row that was clicked
    */
    void tblClasses_cellClicked(int varRow);

    //! emits a signal to the controller when Triangle button is clicked
    void btnTriangle_clicked();

    //! emits a signal to the controller when Rectangle button is clicked
    void btnRectangle_clicked();

    //! emits a signal to the controller when Trapezium button is clicked
    void btnTrapezium_clicked();

    //! emits a signal to the controller when Polygon button is clicked
    void btnPolygon_clicked();

    //! emits a signal when the color combobox changes
    /*!
      \param index the selected index of the selected item
    */
    void cboColor_currentIndexChanged(int varIndex);

    //! emits a signal to the controller when Search button is clicked
    void btnSearch_clicked();

private:
    QString classFileName = ""; //!< name of the Classes file
    QString currentImageDir = ""; //!< name if the image directory

    bool imageLoaded = false; //!< has an image been loaded?
    bool classSort = false; //!< direction of sort for class table
    bool imageSortCol1 = false; //!< direction of sort for column 0 of image table
    bool imageSortCol2 = false; //!< direction of sort for column 1 of image table
};

#endif // ANNOTATIONSAPP_H
