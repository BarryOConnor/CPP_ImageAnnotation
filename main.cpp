#include "AnnotationsApp.h"

#include <QApplication>
#include <QGridLayout>


int main(int argc, char *argv[])
{

    // start the application
    QApplication annotationApp(argc, argv);
    //define the application window
    AnnotationsApp window;
    //display the GUI
    window.show();

    //handle the message loop for the application
    return annotationApp.exec();
}
