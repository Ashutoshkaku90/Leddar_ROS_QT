/**
 * @file /src/main.cpp
 *
 * @brief Qt based gui.
 *
 * @date November 2010
 **/
/*****************************************************************************
** Includes
*****************************************************************************/

#include <QtGui>
#include <QApplication>
#include "../include/leddar_qt/main_window.hpp"

//#include "leddar_ros/leddar_data.h"

/*****************************************************************************
** Main
*****************************************************************************/

int main(int argc, char **argv) {

    /*********************
    ** Qt
    **********************/
    QApplication app(argc, argv);
    leddar_qt::MainWindow w(argc,argv);
    
     
     // QPushButton button ("Hello world !");
    //button.show();  
        w.show();
     
     app.connect(&app, SIGNAL(lastWindowClosed()), &app, SLOT(quit()));
        
       
   // int result = app.exec();
return app.exec();
	//return result;
}
