#define BOOST_TEST_MODULE SDIAnnotations_UnitTests
#include <boost/test/included/unit_test.hpp>
#include <QVector>
#include <QPolygonF>
#include <QDebug>

#include "annotation.h"
#include "annotations.h"
#include "bubblesort.h"
#include "binarysearch.h"





/////////////////////////////////////////////////////////////////////////////////////////

BOOST_AUTO_TEST_SUITE( SortTestSuite )

//set up the initial vector with data
QVector<QPair<QString, QString>> initialContents = {
    {"beautifulImage1.jpg","21/01/1985 10:54"},
    {"stunningView.jpg","03/11/2006 18:35"},
    {"marvellousCactus.png","23/08/2009 12:05"},
    {"lakesideView.jpg","28/06/2016 00:10"},
    {"beachHut.jpg","09/10/2019 13:15"}
};

//set up some boolean values for search direction
const bool sortAscending = true;
const bool sortDescending = false;

//set up some integers for the column numbers
const int columnOne = 0;
const int columnTwo = 1;


void checkSortValid(const QVector<QPair<QString, QString>> & actual, const QVector<QPair<QString, QString>> & expected)
{
    /* Boost has issues with outputting custom types during the comparison so rqather than completely rewriting the
     * << operator, it's easier to just apply the values to strings and compare strings */

    std::string actualStr, expectedStr;
    for(int loopcount = 0; loopcount < actual.length(); loopcount++){
        //check first column
        actualStr = actual[loopcount].first.toStdString();
        expectedStr = expected[loopcount].first.toStdString();
        BOOST_CHECK_EQUAL( actualStr , expectedStr );

        //check second column
        actualStr = actual[loopcount].second.toStdString();
        expectedStr = expected[loopcount].second.toStdString();
        BOOST_CHECK_EQUAL( actualStr , expectedStr );
    }

}

BOOST_AUTO_TEST_CASE( bubblesort_test_no_contents )
{
    QVector<QPair<QString, QString>> emptyVector = {};


    BOOST_CHECK_THROW( bubbleSort(emptyVector, sortAscending, columnOne) , std::invalid_argument );


}

BOOST_AUTO_TEST_CASE( bubblesort_test_single_pair )
{

    QVector<QPair<QString, QString>> singlePair = {{"lakesideView.jpg","28/06/2016 00:10"}};



    const QVector<QPair<QString, QString>> expectedResults = {
        {"lakesideView.jpg","28/06/2016 00:10"}
    };

    //acts upon the referemce to the string so need to run before the checks
    bubbleSort(singlePair, sortAscending, columnOne);

    //perform the comparison
    checkSortValid(singlePair, expectedResults);

}


BOOST_AUTO_TEST_CASE( bubblesort_test_ascending_column1 )
{

    /*The test uses a vector of pairs because the table in the final application
     * has two columns so we need to check that both columns sort correctly*/

    const QVector<QPair<QString, QString>> expectedResults = {
        {"beachHut.jpg","09/10/2019 13:15"},
        {"beautifulImage1.jpg","21/01/1985 10:54"},
        {"lakesideView.jpg","28/06/2016 00:10"},
        {"marvellousCactus.png","23/08/2009 12:05"},
        {"stunningView.jpg","03/11/2006 18:35"}
    };

    //acts upon the referemce to the string so need to run before the checks
    bubbleSort(initialContents, sortAscending, columnOne);

    //perform the comparison
    checkSortValid(initialContents, expectedResults);

}

BOOST_AUTO_TEST_CASE( bubblesort_test_descending_column1 )
{

    /*The test uses a vector of pairs because the table in the final application
     * has two columns so we need to check that both columns sort correctly*/

    QVector<QPair<QString, QString>> expectedResults = {
        {"stunningView.jpg","03/11/2006 18:35"},
        {"marvellousCactus.png","23/08/2009 12:05"},
        {"lakesideView.jpg","28/06/2016 00:10"},
        {"beautifulImage1.jpg","21/01/1985 10:54"},
        {"beachHut.jpg","09/10/2019 13:15"}
    };

    //acts upon the referemce to the string so need to run before the checks
    bubbleSort(initialContents, sortDescending, columnOne);

    //perform the comparison
    checkSortValid(initialContents, expectedResults);

}


BOOST_AUTO_TEST_CASE( bubblesort_test_ascending_column2 )
{

    /*The test uses a vector of pairs because the table in the final application
     * has two columns so we need to check that both columns sort correctly*/

    const QVector<QPair<QString, QString>> expectedResults = {
        {"beautifulImage1.jpg","21/01/1985 10:54"},
        {"stunningView.jpg","03/11/2006 18:35"},
        {"marvellousCactus.png","23/08/2009 12:05"},
        {"lakesideView.jpg","28/06/2016 00:10"},
        {"beachHut.jpg","09/10/2019 13:15"}
    };

    //acts upon the referemce to the string so need to run before the checks
    bubbleSort(initialContents, sortAscending, columnTwo);

    //perform the comparison
    checkSortValid(initialContents, expectedResults);

}



BOOST_AUTO_TEST_CASE( bubblesort_test_descending_column2 )
{

    /*The test uses a vector of pairs because the table in the final application
     * has two columns so we need to check that both columns sort correctly*/

    const QVector<QPair<QString, QString>> expectedResults = {
        {"beachHut.jpg","09/10/2019 13:15"},
        {"lakesideView.jpg","28/06/2016 00:10"},
        {"marvellousCactus.png","23/08/2009 12:05"},
        {"stunningView.jpg","03/11/2006 18:35"},
        {"beautifulImage1.jpg","21/01/1985 10:54"}
    };

    //acts upon the referemce to the string so need to run before the checks
    bubbleSort(initialContents, sortDescending, columnTwo);

    //perform the comparison
    checkSortValid(initialContents, expectedResults);


}

BOOST_AUTO_TEST_SUITE_END()

/////////////////////////////////////////////////////////////////////////////////////////


BOOST_AUTO_TEST_SUITE( SearchTestSuite )




BOOST_AUTO_TEST_CASE( binarysearch_test_no_match )
{
    QVector<QPair<QString, QString>> *initialContents = new QVector<QPair<QString, QString>>;
    initialContents->push_back({"beautifulImage1.jpg","21/01/1985 10:54"});
    initialContents->push_back({"stunningView.jpg","03/11/2006 18:35"});
    initialContents->push_back({"marvellousCactus.png","23/08/2009 12:05"});
    initialContents->push_back({"lakesideView.jpg","28/06/2016 00:10"});
    initialContents->push_back({"beachHut.jpg","09/10/2019 13:15"});

    std::string result = binarySearch(initialContents, "xyz").toStdString();
    //perform the comparison
   BOOST_CHECK_EQUAL(result, "no match");

   initialContents->clear();
}

BOOST_AUTO_TEST_CASE( binarysearch_test_one_match )
{

    QVector<QPair<QString, QString>> *initialContents = new QVector<QPair<QString, QString>>;
    initialContents->push_back({"beautifulImage1.jpg","21/01/1985 10:54"});
    initialContents->push_back({"stunningView.jpg","03/11/2006 18:35"});
    initialContents->push_back({"marvellousCactus.png","23/08/2009 12:05"});
    initialContents->push_back({"lakesideView.jpg","28/06/2016 00:10"});
    initialContents->push_back({"beachHut.jpg","09/10/2019 13:15"});

    std::string result = binarySearch(initialContents, "stunn").toStdString();
    //perform the comparison
   BOOST_CHECK_EQUAL(result, "stunningView.jpg");

   initialContents->clear();

}

BOOST_AUTO_TEST_CASE( binarysearch_test_multiple_match_first )
{

    QVector<QPair<QString, QString>> *initialContents = new QVector<QPair<QString, QString>>;
    initialContents->push_back({"beautifulImage1.jpg","21/01/1985 10:54"});
    initialContents->push_back({"stunningView.jpg","03/11/2006 18:35"});
    initialContents->push_back({"marvellousCactus.png","23/08/2009 12:05"});
    initialContents->push_back({"lakesideView.jpg","28/06/2016 00:10"});
    initialContents->push_back({"beachHut.jpg","09/10/2019 13:15"});

    std::string result = binarySearch(initialContents, "bea").toStdString();
    //perform the comparison
   BOOST_CHECK_EQUAL(result, "beachHut.jpg");

    initialContents->clear();

}

BOOST_AUTO_TEST_CASE( binarysearch_test_whole_string )
{

    QVector<QPair<QString, QString>> *initialContents = new QVector<QPair<QString, QString>>;
    initialContents->push_back({"beautifulImage1.jpg","21/01/1985 10:54"});
    initialContents->push_back({"stunningView.jpg","03/11/2006 18:35"});
    initialContents->push_back({"marvellousCactus.png","23/08/2009 12:05"});
    initialContents->push_back({"lakesideView.jpg","28/06/2016 00:10"});
    initialContents->push_back({"beachHut.jpg","09/10/2019 13:15"});

    std::string result = binarySearch(initialContents, "lakesideView.jpg").toStdString();
    //perform the comparison
   BOOST_CHECK_EQUAL(result, "lakesideView.jpg");

   initialContents->clear();

}

BOOST_AUTO_TEST_CASE( binarysearch_test_too_many_letters )
{

    QVector<QPair<QString, QString>> *initialContents = new QVector<QPair<QString, QString>>;
    initialContents->push_back({"beautifulImage1.jpg","21/01/1985 10:54"});
    initialContents->push_back({"stunningView.jpg","03/11/2006 18:35"});
    initialContents->push_back({"marvellousCactus.png","23/08/2009 12:05"});
    initialContents->push_back({"lakesideView.jpg","28/06/2016 00:10"});
    initialContents->push_back({"beachHut.jpg","09/10/2019 13:15"});

    std::string result = binarySearch(initialContents, "marvellousCactus123").toStdString();
    //perform the comparison
   BOOST_CHECK_EQUAL(result, "no match");

   initialContents->clear();

}


BOOST_AUTO_TEST_SUITE_END()


/////////////////////////////////////////////////////////////////////////////////////////


BOOST_AUTO_TEST_SUITE( LinkedListTestSuite )




BOOST_AUTO_TEST_CASE( LinkedList_test_append )
{
    qDebug() << "\n-----  LinkedList_test_append -----";
    Annotations *linkedlist = new Annotations();
    Annotation *node = new Annotation(1,"Dog","beautifulImage.jpg",1,1,{{50,50},{50,50},{50,50}});

    linkedlist->appendAnnotation(node);
    BOOST_CHECK_EQUAL(linkedlist->length, 1);
    linkedlist->display();
}


BOOST_AUTO_TEST_CASE( LinkedList_test_append_three )
{
    qDebug() << "\n\n----- LinkedList_test_append_three -----";
    Annotations *linkedlist = new Annotations();
    Annotation *node = new Annotation(1,"Dog","beautifulImage.jpg",1,1,{{50,50},{50,50},{50,50}});
    linkedlist->appendAnnotation(node);
    node = new Annotation(2,"Cat","beautifulImage.jpg",1,1,{{10,10},{10,10},{10,10}});
    linkedlist->appendAnnotation(node);
    node = new Annotation(3,"Person","beautifulImage.jpg",1,1,{{30,30},{30,30},{30,30}});
    linkedlist->appendAnnotation(node);

    BOOST_CHECK_EQUAL(linkedlist->length, 3);
    linkedlist->display();
}

BOOST_AUTO_TEST_CASE( LinkedList_test_append_three_delete_all )
{
    qDebug() << "\n\n----- LinkedList_test_append_three_delete_all -----";
    Annotations *linkedlist = new Annotations();
    Annotation *node = new Annotation(1,"Dog","beautifulImage.jpg",1,1,{{50,50},{50,50},{50,50}});
    linkedlist->appendAnnotation(node);
    node = new Annotation(2,"Cat","beautifulImage.jpg",1,1,{{10,10},{10,10},{10,10}});
    linkedlist->appendAnnotation(node);
    node = new Annotation(3,"Person","beautifulImage.jpg",1,1,{{30,30},{30,30},{30,30}});
    linkedlist->appendAnnotation(node);

    BOOST_CHECK_EQUAL(linkedlist->length, 3);

    linkedlist->deleteAllAnnotations();
    BOOST_CHECK_EQUAL(linkedlist->length, 0);
    linkedlist->display();
}

BOOST_AUTO_TEST_CASE( LinkedList_test_append_three_delete_head )
{
    qDebug() << "\n\n----- LinkedList_test_append_three_delete_head -----";
    Annotations *linkedlist = new Annotations();
    Annotation *node = new Annotation(1,"Dog","beautifulImage.jpg",1,1,{{50,50},{50,50},{50,50}});
    linkedlist->appendAnnotation(node);
    node = new Annotation(2,"Cat","beautifulImage.jpg",1,1,{{10,10},{10,10},{10,10}});
    linkedlist->appendAnnotation(node);
    node = new Annotation(3,"Person","beautifulImage.jpg",1,1,{{30,30},{30,30},{30,30}});
    linkedlist->appendAnnotation(node);

    BOOST_CHECK_EQUAL(linkedlist->length, 3);

    linkedlist->deleteWithId(1);
    BOOST_CHECK_EQUAL(linkedlist->length, 2);
    linkedlist->display();
}


BOOST_AUTO_TEST_CASE( LinkedList_test_append_three_delete_middle )
{
    qDebug() << "\n\n----- LinkedList_test_append_three_delete_middle -----";
    Annotations *linkedlist = new Annotations();
    Annotation *node = new Annotation(1,"Dog","beautifulImage.jpg",1,1,{{50,50},{50,50},{50,50}});
    linkedlist->appendAnnotation(node);
    node = new Annotation(2,"Cat","beautifulImage.jpg",1,1,{{10,10},{10,10},{10,10}});
    linkedlist->appendAnnotation(node);
    node = new Annotation(3,"Person","beautifulImage.jpg",1,1,{{30,30},{30,30},{30,30}});
    linkedlist->appendAnnotation(node);

    BOOST_CHECK_EQUAL(linkedlist->length, 3);

    linkedlist->deleteWithId(2);
    BOOST_CHECK_EQUAL(linkedlist->length, 2);
    linkedlist->display();
}

BOOST_AUTO_TEST_CASE( LinkedList_test_append_three_delete_tail )
{
    qDebug() << "\n\n----- LinkedList_test_append_three_delete_tail -----";
    Annotations *linkedlist = new Annotations();
    Annotation *node = new Annotation(1,"Dog","beautifulImage.jpg",1,1,{{50,50},{50,50},{50,50}});
    linkedlist->appendAnnotation(node);
    node = new Annotation(2,"Cat","beautifulImage.jpg",1,1,{{10,10},{10,10},{10,10}});
    linkedlist->appendAnnotation(node);
    node = new Annotation(3,"Person","beautifulImage.jpg",1,1,{{30,30},{30,30},{30,30}});
    linkedlist->appendAnnotation(node);

    BOOST_CHECK_EQUAL(linkedlist->length, 3);

    linkedlist->deleteWithId(3);
    BOOST_CHECK_EQUAL(linkedlist->length, 2);
    linkedlist->display();
}


BOOST_AUTO_TEST_CASE( LinkedList_test_append_one_then_update )
{
    qDebug() << "\n\n----- LinkedList_test_append_one_then_update -----";
    Annotations *linkedlist = new Annotations();
    Annotation *node = new Annotation(1,"Dog","beautifulImage.jpg",1,1,{{50,50},{50,50},{50,50}});

    linkedlist->appendAnnotation(node);

    BOOST_CHECK_EQUAL(linkedlist->length, 1);

    QPolygonF newCoords;
    newCoords << QPointF(10.4, 20.5) << QPointF(20.2, 30.2) << QPointF(15.2, 25.2);
    linkedlist->updateAnnotation(1,newCoords);
    linkedlist->display();
}


BOOST_AUTO_TEST_CASE( LinkedList_test_append_three_search_image )
{
    qDebug() << "\n\n----- LinkedList_test_append_three_search_image -----";
    QVector<Annotation*> returnedNodes;
    Annotations *linkedlist = new Annotations();
    Annotation *node = new Annotation(1,"Dog","beautifulImage.jpg",1,1,{{50,50},{50,50},{50,50}});
    linkedlist->appendAnnotation(node);
    node = new Annotation(2,"Cat","lakesideView.jpg",1,1,{{10,10},{10,10},{10,10}});
    linkedlist->appendAnnotation(node);
    node = new Annotation(3,"Person","beautifulImage.jpg",1,1,{{30,30},{30,30},{30,30}});
    linkedlist->appendAnnotation(node);

    BOOST_CHECK_EQUAL(linkedlist->length, 3);

    returnedNodes = linkedlist->searchByImage("beautifulImage.jpg");
    BOOST_CHECK_EQUAL(returnedNodes.length(), 2);
}


BOOST_AUTO_TEST_SUITE_END()

