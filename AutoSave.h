#ifndef AUTOSAVE_H
#define AUTOSAVE_H
#include "Annotation.h"
#include <QThread>
#include <QTimer>


//!  Autosave class operates in a seperate thread and autosaves every minute.
/*!
  Inbuilt QT class which runs the application
*/
class AutoSave : public QObject
{
    Q_OBJECT

public:
    //!  default constructor.
    AutoSave();

public slots:
    //! recieves data from the application and processes this
    /*!
      The autosave signals the main thread that it's ready for data and this slot handles the reply
      The data is processed by the autosave thread and uses it to generate an autosave file

      \param *uniqueImages QVector containing a list of all unique images in the linked list
      \param *jsonData A vector of pairs containing the name of the image and all corresponding annotations
    */
    void saveDataReady(QVector<QString> * uniqueImages, QVector<QPair<QString, QVector<Annotation *>>> *jsonData);

signals:
    //! signals to the model in the main thread that the autosave function is ready to recieve data
    void getSaveData();

private:
    QTimer *timer; //!< timer object to handle the 1 minute timer
    QString filename; //!< name of the autosave file to write to
};
#endif // AUTOSAVE_H
