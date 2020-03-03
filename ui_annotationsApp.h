/********************************************************************************
** Form generated from reading UI file 'annotationsApp.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ANNOTATIONSAPP_H
#define UI_ANNOTATIONSAPP_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AnnotationsApp
{
public:
    QAction *actionExit;
    QWidget *centralWidget;
    QFormLayout *formLayout;
    QGridLayout *gridLayout_3;
    QTableWidget *tblClasses;
    QPushButton *btnLoadAnnotations;
    QPushButton *btnSaveAnnotations;
    QTableWidget *tblImages;
    QHBoxLayout *horizontalLayout;
    QPushButton *btnAddClass;
    QPushButton *btnDeleteClass;
    QPushButton *btnLoadClasses;
    QPushButton *btnLoadImages;
    QGridLayout *gridLayout;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QGraphicsView *gvImage;
    QPushButton *btnTrapezium;
    QPushButton *btnTriangle;
    QPushButton *btnRectangle;
    QPushButton *btnPolygon;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QToolBar *mainToolBar;

    void setupUi(QMainWindow *AnnotationsApp)
    {
        if (AnnotationsApp->objectName().isEmpty())
            AnnotationsApp->setObjectName(QString::fromUtf8("AnnotationsApp"));
        AnnotationsApp->resize(800, 600);
        AnnotationsApp->setMinimumSize(QSize(800, 600));
        actionExit = new QAction(AnnotationsApp);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        centralWidget = new QWidget(AnnotationsApp);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        formLayout = new QFormLayout(centralWidget);
        formLayout->setSpacing(6);
        formLayout->setContentsMargins(11, 11, 11, 11);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        gridLayout_3 = new QGridLayout();
        gridLayout_3->setSpacing(6);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        tblClasses = new QTableWidget(centralWidget);
        if (tblClasses->columnCount() < 1)
            tblClasses->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tblClasses->setHorizontalHeaderItem(0, __qtablewidgetitem);
        tblClasses->setObjectName(QString::fromUtf8("tblClasses"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tblClasses->sizePolicy().hasHeightForWidth());
        tblClasses->setSizePolicy(sizePolicy);
        tblClasses->setMinimumSize(QSize(320, 0));
        tblClasses->setSelectionMode(QAbstractItemView::SingleSelection);
        tblClasses->setSelectionBehavior(QAbstractItemView::SelectRows);
        tblClasses->setShowGrid(false);
        tblClasses->setGridStyle(Qt::NoPen);
        tblClasses->setCornerButtonEnabled(false);
        tblClasses->horizontalHeader()->setCascadingSectionResizes(true);
        tblClasses->horizontalHeader()->setProperty("showSortIndicator", QVariant(true));
        tblClasses->horizontalHeader()->setStretchLastSection(true);
        tblClasses->verticalHeader()->setVisible(false);

        gridLayout_3->addWidget(tblClasses, 2, 0, 1, 1);

        btnLoadAnnotations = new QPushButton(centralWidget);
        btnLoadAnnotations->setObjectName(QString::fromUtf8("btnLoadAnnotations"));

        gridLayout_3->addWidget(btnLoadAnnotations, 5, 0, 1, 1);

        btnSaveAnnotations = new QPushButton(centralWidget);
        btnSaveAnnotations->setObjectName(QString::fromUtf8("btnSaveAnnotations"));

        gridLayout_3->addWidget(btnSaveAnnotations, 4, 0, 1, 1);

        tblImages = new QTableWidget(centralWidget);
        if (tblImages->columnCount() < 2)
            tblImages->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tblImages->setHorizontalHeaderItem(0, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tblImages->setHorizontalHeaderItem(1, __qtablewidgetitem2);
        tblImages->setObjectName(QString::fromUtf8("tblImages"));
        sizePolicy.setHeightForWidth(tblImages->sizePolicy().hasHeightForWidth());
        tblImages->setSizePolicy(sizePolicy);
        tblImages->setMinimumSize(QSize(320, 0));
        tblImages->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        tblImages->setSelectionMode(QAbstractItemView::SingleSelection);
        tblImages->setSelectionBehavior(QAbstractItemView::SelectRows);
        tblImages->setShowGrid(false);
        tblImages->setGridStyle(Qt::NoPen);
        tblImages->setSortingEnabled(false);
        tblImages->setRowCount(0);
        tblImages->setColumnCount(2);
        tblImages->horizontalHeader()->setDefaultSectionSize(160);
        tblImages->horizontalHeader()->setHighlightSections(false);
        tblImages->horizontalHeader()->setProperty("showSortIndicator", QVariant(true));
        tblImages->horizontalHeader()->setStretchLastSection(true);
        tblImages->verticalHeader()->setVisible(false);
        tblImages->verticalHeader()->setMinimumSectionSize(18);
        tblImages->verticalHeader()->setProperty("showSortIndicator", QVariant(false));
        tblImages->verticalHeader()->setStretchLastSection(false);

        gridLayout_3->addWidget(tblImages, 0, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        btnAddClass = new QPushButton(centralWidget);
        btnAddClass->setObjectName(QString::fromUtf8("btnAddClass"));
        btnAddClass->setEnabled(false);

        horizontalLayout->addWidget(btnAddClass);

        btnDeleteClass = new QPushButton(centralWidget);
        btnDeleteClass->setObjectName(QString::fromUtf8("btnDeleteClass"));
        btnDeleteClass->setEnabled(false);

        horizontalLayout->addWidget(btnDeleteClass);

        btnLoadClasses = new QPushButton(centralWidget);
        btnLoadClasses->setObjectName(QString::fromUtf8("btnLoadClasses"));

        horizontalLayout->addWidget(btnLoadClasses);


        gridLayout_3->addLayout(horizontalLayout, 3, 0, 1, 1);

        btnLoadImages = new QPushButton(centralWidget);
        btnLoadImages->setObjectName(QString::fromUtf8("btnLoadImages"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(btnLoadImages->sizePolicy().hasHeightForWidth());
        btnLoadImages->setSizePolicy(sizePolicy1);
        btnLoadImages->setMinimumSize(QSize(320, 0));

        gridLayout_3->addWidget(btnLoadImages, 1, 0, 1, 1);


        formLayout->setLayout(0, QFormLayout::LabelRole, gridLayout_3);

        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        scrollArea = new QScrollArea(centralWidget);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 450, 516));
        gvImage = new QGraphicsView(scrollAreaWidgetContents);
        gvImage->setObjectName(QString::fromUtf8("gvImage"));
        gvImage->setGeometry(QRect(0, 0, 451, 481));
        scrollArea->setWidget(scrollAreaWidgetContents);

        gridLayout->addWidget(scrollArea, 1, 0, 1, 7);

        btnTrapezium = new QPushButton(centralWidget);
        btnTrapezium->setObjectName(QString::fromUtf8("btnTrapezium"));
        sizePolicy1.setHeightForWidth(btnTrapezium->sizePolicy().hasHeightForWidth());
        btnTrapezium->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(btnTrapezium, 0, 1, 1, 1);

        btnTriangle = new QPushButton(centralWidget);
        btnTriangle->setObjectName(QString::fromUtf8("btnTriangle"));
        sizePolicy1.setHeightForWidth(btnTriangle->sizePolicy().hasHeightForWidth());
        btnTriangle->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(btnTriangle, 0, 2, 1, 1);

        btnRectangle = new QPushButton(centralWidget);
        btnRectangle->setObjectName(QString::fromUtf8("btnRectangle"));
        sizePolicy1.setHeightForWidth(btnRectangle->sizePolicy().hasHeightForWidth());
        btnRectangle->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(btnRectangle, 0, 0, 1, 1);

        btnPolygon = new QPushButton(centralWidget);
        btnPolygon->setObjectName(QString::fromUtf8("btnPolygon"));
        sizePolicy1.setHeightForWidth(btnPolygon->sizePolicy().hasHeightForWidth());
        btnPolygon->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(btnPolygon, 0, 3, 1, 1);


        formLayout->setLayout(0, QFormLayout::FieldRole, gridLayout);

        AnnotationsApp->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(AnnotationsApp);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 800, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        AnnotationsApp->setMenuBar(menuBar);
        mainToolBar = new QToolBar(AnnotationsApp);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        AnnotationsApp->addToolBar(Qt::TopToolBarArea, mainToolBar);

        menuBar->addAction(menuFile->menuAction());
        menuFile->addAction(actionExit);

        retranslateUi(AnnotationsApp);
        QObject::connect(actionExit, SIGNAL(triggered()), AnnotationsApp, SLOT(close()));

        QMetaObject::connectSlotsByName(AnnotationsApp);
    } // setupUi

    void retranslateUi(QMainWindow *AnnotationsApp)
    {
        AnnotationsApp->setWindowTitle(QCoreApplication::translate("AnnotationsApp", "SDI Annotations", nullptr));
        actionExit->setText(QCoreApplication::translate("AnnotationsApp", "Exit", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tblClasses->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("AnnotationsApp", "Class Names", nullptr));
        btnLoadAnnotations->setText(QCoreApplication::translate("AnnotationsApp", "Load Annotations", nullptr));
        btnSaveAnnotations->setText(QCoreApplication::translate("AnnotationsApp", "Save Annotations", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tblImages->horizontalHeaderItem(0);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("AnnotationsApp", "Image Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tblImages->horizontalHeaderItem(1);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("AnnotationsApp", "Image Date", nullptr));
        btnAddClass->setText(QCoreApplication::translate("AnnotationsApp", "Add a Class", nullptr));
        btnDeleteClass->setText(QCoreApplication::translate("AnnotationsApp", "Delete a Class", nullptr));
        btnLoadClasses->setText(QCoreApplication::translate("AnnotationsApp", "Load Classes", nullptr));
        btnLoadImages->setText(QCoreApplication::translate("AnnotationsApp", "Load Images", nullptr));
        btnTrapezium->setText(QCoreApplication::translate("AnnotationsApp", "Trapezium", nullptr));
        btnTriangle->setText(QCoreApplication::translate("AnnotationsApp", "Triangle", nullptr));
        btnRectangle->setText(QCoreApplication::translate("AnnotationsApp", "Rectangle", nullptr));
        btnPolygon->setText(QCoreApplication::translate("AnnotationsApp", "Polygon", nullptr));
        menuFile->setTitle(QCoreApplication::translate("AnnotationsApp", "File", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AnnotationsApp: public Ui_AnnotationsApp {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ANNOTATIONSAPP_H
