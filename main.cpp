#include "AnnotationsApp.h"

#include <QApplication>
#include <QGridLayout>


int main(int argc, char *argv[])
{

    QApplication annotationApp(argc, argv);
    AnnotationsApp window;
    window.show();


    return annotationApp.exec();
}
