#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "View.h"
#include "Annotation.h"
#include "Model.h"
#include "GraphicsScene.h"

#include <QTableWidget>
#include <QMainWindow>

//!  Controller class for the application.
/*!
  Acts as a go between for the view and model classes
*/
class Controller : public QObject
{
    Q_OBJECT

public:
    //!  handles the sorting of table views
    /*!
      \param *thisTable pointer to the tableview object to be sorted
      \param varDirection boolean value representing sort direction true=Ascending, false = descending
      \param varColumn integer representing the column to be sorted
    */
    void sortTableView(QTableWidget* thisTable, bool varDirection, int varColumn);

    //!  default constructor
    /*!
      \param *newView pointer to the view object which controls the UI
      \param *varParent to the application for use in messageBoxes
    */
    Controller(View *varView, QWidget *varParent);

    //!  default destructor
    ~Controller();

public slots:

    void tableHeading_clicked(QTableWidget* varTable, bool varDirection, int varColumn);

    //!  recieves the matching Load Images button click signal from the application
    void btnLoadImages_clicked();

    //!  recieves the matching Add Class button click signal from the application
    void btnAddClass_clicked();

    //!  recieves the matching Delete Class button click signal from the application
    void btnDeleteClass_clicked();

    //!  recieves the matching Load Classes button click signal from the application
    void btnLoadClasses_clicked();

    //!  recieves the matching Load Annotations button click signal from the application
    void btnLoadAnnotations_clicked();

    //!  recieves the matching Save Annotations button click signal from the application
    void btnSaveAnnotations_clicked();

    //!  recieves the matching signal from the image table being clicked from the application
    /*!
      \param row integer value for the row number of the clicked item
    */
    void tblImages_cellClicked(int row);

    //!  recieves the matching signal from the class table being clicked from the application
    /*!
      \param row integer value for the row number of the clicked item
    */
    void tblClasses_cellClicked(int row);

    //!  recieves the matching Triangle button click signal from the application
    void btnTriangle_clicked();

    //!  recieves the matching Rectangle button click signal from the application
    void btnRectangle_clicked();

    //!  recieves the matching Trapezium button click signal from the application
    void btnTrapezium_clicked();

    //!  recieves the matching Polygon button click signal from the application
    void btnPolygon_clicked();

    //!  recieves the matching Search button click signal from the application
    void btnSearch_clicked();

    //!  recieves the matching signal from the application when the color combobox is changed
    /*!
      \param varIndex integer value for the index number of the clicked item
    */
    void cboColor_currentIndexChanged(int varIndex);

    //!  recieves the matching signal from the GraphicsScene when the user has finished drawing a shape
    /*!
      \param *varAnnotation pointer to the completed annotation object
    */
    void annotationReady(Annotation *varAnnotation);

    //!  recieves the matching signal from the GraphicsScene when the user has deleted a shape
    /*!
      \param varId integer representing the ID of the annotation that was deleted
    */
    void annotationDeleted(int varId);

    //!  recieves the matching signal from the GraphicsScene when the user has finished updating (moving) a shape
    /*!
      \param varId integer representing the ID of the annotation that was moved
      \param varPosition new coordinates of the shape after the move was completed
    */
    void updateItem(int varId, QPolygonF varPosition);


private:
    //! binary search function for use on the images list
    /*!
      \param *varContents vector of pairs (since the table has 2 columns) containing the table data
      \param searchTerm the text to be searched for
    */
    void binarySearch(QVector<QPair<QString, QString>> *varContents, const QString &searchTerm);

    //! bubblesort function to sort the contents of the images or classes lists
    /*!
      \param *varContents vector of pairs (since the table has 2 columns) containing the table data
      \param varDirection boolean value representing sort direction true=Ascending, false = descending
      \param varColumn integer representing the column to be sorted
    */
    void bubbleSort(QVector<QPair<QString, QString>>& varContents, bool varDirection, int varColumn);

    //! function to populate a TableView (list) with data (generally after a sort)
    /*!
      \param *varTable pointer to the TableView control that needs to be updated
      \param *varContents vector of pairs (since the table has 2 columns) containing the table data
    */
    void populateTableView(QTableWidget* varTable, const QVector<QPair<QString, QString>> &varContents);

    QString classFileName; //!< stores the name of the class file
    QString annotationFileName; //!< stores the name of the annotations file
    QString currentImageDir; //!< stores the name of the directory the images were chosen from
    QWidget *parent; //!< pointer to the parent application (needed to associate messageboxes witht he application)

    View *view; //!< pointer to the application UI object
    Model *model; //!< pointer to the Model class

    friend class AnnotationsApp;
};

#endif // CONTROLLER_H
