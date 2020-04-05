/********************************************************************************
** Form generated from reading UI file 'AnnotationsApp.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ANNOTATIONSAPP_H
#define UI_ANNOTATIONSAPP_H
#include "GraphicsScene.h"
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AnnotationsApp
{
public:
    QAction *actionExit;
    QWidget *centralWidget;
    QFormLayout *formLayout;
    QGridLayout *sideLayout;
    QHBoxLayout *buttonLayout;
    QPushButton *btnAddClass;
    QPushButton *btnDeleteClass;
    QPushButton *btnLoadClasses;
    QPushButton *btnLoadAnnotations;
    QPushButton *btnSaveAnnotations;
    QTableWidget *tblImages;
    QPushButton *btnLoadImages;
    QTableWidget *tblClasses;
    QGridLayout *mainLayout;
    QComboBox *cboColor;
    QLabel *lblColor;
    QGraphicsView *gvImage;
    QHBoxLayout *shapesLayout;
    QPushButton *btnTriangle;
    QPushButton *btnRectangle;
    QPushButton *btnTrapezium;
    QPushButton *btnPolygon;
    QMenuBar *menuBar;
    QMenu *menuFile;
    GraphicsScene *mainScene;

    void setupUi(QMainWindow *AnnotationsApp)
    {
        if (AnnotationsApp->objectName().isEmpty())
            AnnotationsApp->setObjectName(QString::fromUtf8("AnnotationsApp"));
        AnnotationsApp->resize(800, 600);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(AnnotationsApp->sizePolicy().hasHeightForWidth());
        AnnotationsApp->setSizePolicy(sizePolicy);
        AnnotationsApp->setMinimumSize(QSize(800, 600));
        actionExit = new QAction(AnnotationsApp);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        centralWidget = new QWidget(AnnotationsApp);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        formLayout = new QFormLayout(centralWidget);
        formLayout->setSpacing(6);
        formLayout->setContentsMargins(11, 11, 11, 11);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        sideLayout = new QGridLayout();
        sideLayout->setSpacing(6);
        sideLayout->setObjectName(QString::fromUtf8("sideLayout"));
        sideLayout->setContentsMargins(0, 0, 0, 0);
        buttonLayout = new QHBoxLayout();
        buttonLayout->setSpacing(6);
        buttonLayout->setObjectName(QString::fromUtf8("buttonLayout"));
        btnAddClass = new QPushButton(centralWidget);
        btnAddClass->setObjectName(QString::fromUtf8("btnAddClass"));
        btnAddClass->setEnabled(false);

        buttonLayout->addWidget(btnAddClass);

        btnDeleteClass = new QPushButton(centralWidget);
        btnDeleteClass->setObjectName(QString::fromUtf8("btnDeleteClass"));
        btnDeleteClass->setEnabled(false);

        buttonLayout->addWidget(btnDeleteClass);

        btnLoadClasses = new QPushButton(centralWidget);
        btnLoadClasses->setObjectName(QString::fromUtf8("btnLoadClasses"));

        buttonLayout->addWidget(btnLoadClasses);


        sideLayout->addLayout(buttonLayout, 3, 0, 1, 1);

        btnLoadAnnotations = new QPushButton(centralWidget);
        btnLoadAnnotations->setObjectName(QString::fromUtf8("btnLoadAnnotations"));

        sideLayout->addWidget(btnLoadAnnotations, 5, 0, 1, 1);

        btnSaveAnnotations = new QPushButton(centralWidget);
        btnSaveAnnotations->setObjectName(QString::fromUtf8("btnSaveAnnotations"));

        sideLayout->addWidget(btnSaveAnnotations, 4, 0, 1, 1);

        tblImages = new QTableWidget(centralWidget);
        if (tblImages->columnCount() < 2)
            tblImages->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tblImages->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tblImages->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tblImages->setObjectName(QString::fromUtf8("tblImages"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(tblImages->sizePolicy().hasHeightForWidth());
        tblImages->setSizePolicy(sizePolicy1);
        tblImages->setMinimumSize(QSize(320, 0));
        QFont font;
        font.setPointSize(10);
        tblImages->setFont(font);
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

        sideLayout->addWidget(tblImages, 0, 0, 1, 1);

        btnLoadImages = new QPushButton(centralWidget);
        btnLoadImages->setObjectName(QString::fromUtf8("btnLoadImages"));
        sizePolicy.setHeightForWidth(btnLoadImages->sizePolicy().hasHeightForWidth());
        btnLoadImages->setSizePolicy(sizePolicy);
        btnLoadImages->setMinimumSize(QSize(320, 0));

        sideLayout->addWidget(btnLoadImages, 1, 0, 1, 1);

        tblClasses = new QTableWidget(centralWidget);
        if (tblClasses->columnCount() < 1)
            tblClasses->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tblClasses->setHorizontalHeaderItem(0, __qtablewidgetitem2);
        tblClasses->setObjectName(QString::fromUtf8("tblClasses"));
        sizePolicy1.setHeightForWidth(tblClasses->sizePolicy().hasHeightForWidth());
        tblClasses->setSizePolicy(sizePolicy1);
        tblClasses->setMinimumSize(QSize(320, 0));
        tblClasses->setFont(font);
        tblClasses->setAutoFillBackground(true);
        tblClasses->setProperty("showDropIndicator", QVariant(false));
        tblClasses->setSelectionMode(QAbstractItemView::SingleSelection);
        tblClasses->setSelectionBehavior(QAbstractItemView::SelectRows);
        tblClasses->setShowGrid(false);
        tblClasses->setGridStyle(Qt::NoPen);
        tblClasses->setCornerButtonEnabled(false);
        tblClasses->horizontalHeader()->setCascadingSectionResizes(true);
        tblClasses->horizontalHeader()->setProperty("showSortIndicator", QVariant(true));
        tblClasses->horizontalHeader()->setStretchLastSection(true);
        tblClasses->verticalHeader()->setVisible(false);
        tblClasses->verticalHeader()->setHighlightSections(false);

        sideLayout->addWidget(tblClasses, 2, 0, 1, 1);


        formLayout->setLayout(0, QFormLayout::LabelRole, sideLayout);

        mainLayout = new QGridLayout();
        mainLayout->setSpacing(6);
        mainLayout->setObjectName(QString::fromUtf8("mainLayout"));
        mainLayout->setContentsMargins(0, 0, 0, 0);
        cboColor = new QComboBox(centralWidget);
        cboColor->addItem(QString());
        cboColor->addItem(QString());
        cboColor->addItem(QString());
        cboColor->addItem(QString());
        cboColor->setObjectName(QString::fromUtf8("cboColor"));

        mainLayout->addWidget(cboColor, 8, 1, 1, 3);

        lblColor = new QLabel(centralWidget);
        lblColor->setObjectName(QString::fromUtf8("lblColor"));

        mainLayout->addWidget(lblColor, 8, 0, 1, 1);

        mainScene = new GraphicsScene();
        mainScene->setObjectName(QString::fromUtf8("gvImage"));

        gvImage = new QGraphicsView(centralWidget);
        gvImage->setObjectName(QString::fromUtf8("gvImage"));
        gvImage->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        gvImage->setScene(mainScene);

        mainLayout->addWidget(gvImage, 10, 0, 1, 4);

        shapesLayout = new QHBoxLayout();
        shapesLayout->setSpacing(6);
        shapesLayout->setObjectName(QString::fromUtf8("shapesLayout"));
        btnTriangle = new QPushButton(centralWidget);
        btnTriangle->setObjectName(QString::fromUtf8("btnTriangle"));
        btnTriangle->setCheckable(true);

        shapesLayout->addWidget(btnTriangle);

        btnRectangle = new QPushButton(centralWidget);
        btnRectangle->setObjectName(QString::fromUtf8("btnRectangle"));
        btnRectangle->setCheckable(true);

        shapesLayout->addWidget(btnRectangle);

        btnTrapezium = new QPushButton(centralWidget);
        btnTrapezium->setObjectName(QString::fromUtf8("btnTrapezium"));
        btnTrapezium->setCheckable(true);

        shapesLayout->addWidget(btnTrapezium);

        btnPolygon = new QPushButton(centralWidget);
        btnPolygon->setObjectName(QString::fromUtf8("btnPolygon"));
        btnPolygon->setCheckable(true);

        shapesLayout->addWidget(btnPolygon);


        mainLayout->addLayout(shapesLayout, 7, 0, 1, 4);


        formLayout->setLayout(0, QFormLayout::FieldRole, mainLayout);

        AnnotationsApp->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(AnnotationsApp);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 800, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        AnnotationsApp->setMenuBar(menuBar);
        QWidget::setTabOrder(tblImages, btnLoadImages);
        QWidget::setTabOrder(btnLoadImages, tblClasses);
        QWidget::setTabOrder(tblClasses, btnAddClass);
        QWidget::setTabOrder(btnAddClass, btnDeleteClass);
        QWidget::setTabOrder(btnDeleteClass, btnLoadClasses);
        QWidget::setTabOrder(btnLoadClasses, btnSaveAnnotations);
        QWidget::setTabOrder(btnSaveAnnotations, btnLoadAnnotations);

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
        btnAddClass->setText(QCoreApplication::translate("AnnotationsApp", "Add a Class", nullptr));
        btnDeleteClass->setText(QCoreApplication::translate("AnnotationsApp", "Delete a Class", nullptr));
        btnLoadClasses->setText(QCoreApplication::translate("AnnotationsApp", "Load Classes", nullptr));
        btnLoadAnnotations->setText(QCoreApplication::translate("AnnotationsApp", "Load Annotations", nullptr));
        btnSaveAnnotations->setText(QCoreApplication::translate("AnnotationsApp", "Save Annotations", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tblImages->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("AnnotationsApp", "Image Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tblImages->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("AnnotationsApp", "Image Date", nullptr));
        btnLoadImages->setText(QCoreApplication::translate("AnnotationsApp", "Load Images", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tblClasses->horizontalHeaderItem(0);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("AnnotationsApp", "Class Names", nullptr));
        cboColor->setItemText(0, QCoreApplication::translate("AnnotationsApp", "Red", nullptr));
        cboColor->setItemText(1, QCoreApplication::translate("AnnotationsApp", "Green", nullptr));
        cboColor->setItemText(2, QCoreApplication::translate("AnnotationsApp", "Blue", nullptr));
        cboColor->setItemText(3, QCoreApplication::translate("AnnotationsApp", "Black", nullptr));

        lblColor->setText(QCoreApplication::translate("AnnotationsApp", "Colour:", nullptr));
        btnTriangle->setText(QCoreApplication::translate("AnnotationsApp", "Triangle", nullptr));
        btnRectangle->setText(QCoreApplication::translate("AnnotationsApp", "Rectangle", nullptr));
        btnTrapezium->setText(QCoreApplication::translate("AnnotationsApp", "Trapezium", nullptr));
        btnPolygon->setText(QCoreApplication::translate("AnnotationsApp", "Polygon", nullptr));
        menuFile->setTitle(QCoreApplication::translate("AnnotationsApp", "File", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AnnotationsApp: public Ui_AnnotationsApp {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ANNOTATIONSAPP_H
