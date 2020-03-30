#include "annotationsApp.h"

#include <QApplication>
#include <QGridLayout>


int main(int argc, char *argv[])
{
    QApplication annotations(argc, argv);
    AnnotationsApp window;
	
    window.show();

    return annotations.exec();
}
