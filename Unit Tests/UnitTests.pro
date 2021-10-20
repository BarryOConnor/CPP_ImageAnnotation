TEMPLATE = app
CONFIG -= app_bundle
CONFIG += console



greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
isEmpty(BOOST_INCLUDE_DIR): BOOST_INCLUDE_DIR=$$(BOOST_INCLUDE_DIR)
# set by Qt Creator wizard
isEmpty(BOOST_INCLUDE_DIR): BOOST_INCLUDE_DIR="C:/boost_1_66_0"
!isEmpty(BOOST_INCLUDE_DIR): INCLUDEPATH *= $${BOOST_INCLUDE_DIR}

isEmpty(BOOST_INCLUDE_DIR): {
    message("BOOST_INCLUDE_DIR is not set, assuming Boost can be found automatically in your system")
}

SOURCES += \
    annotation.cpp \
    annotations.cpp \
    binarysearch.cpp \
    bubblesort.cpp \
    main.cpp

HEADERS += \
    annotation.h \
    annotations.h \
    binarysearch.h \
    bubblesort.h
