/**
 * @file /src/main_window.cpp
 *
 * @brief Implementation for the qt gui.
 *
 * @date February 2011
 **/
/*****************************************************************************
** Includes
*****************************************************************************/

#include <QtGui>
#include <QMessageBox>
#include <iostream>
#include "../include/leddar_qt/main_window.hpp"
#include <stdlib.h>
#include<stdio.h>
#include <string.h>
//#include<conio.h>
#include <sstream>
#include <qwt_plot_magnifier.h>
/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace leddar_qt 
{

using namespace Qt;

/*****************************************************************************
** Implementation [MainWindow]
*****************************************************************************/

MainWindow::MainWindow(int argc, char** argv, QWidget *parent): QMainWindow(parent),qnode(argc,argv)
{
	ui.setupUi(this); // Calling this incidentally connects all ui's triggers to on_...() callbacks in this class.
        
      setWindowState(Qt::WindowMaximized);
         qnode.init();
   // scene = new QGraphicsScene(this);
       QRect rec = QApplication::desktop()->screenGeometry();
       int height = rec.height();
        int width = rec.width();
      //  this->setFixedSize(width/2,height/2);
   // ui.graphicsView->setScene(scene);
     ui.qwtPlot->setAxisScale(2,-15,15,5);
      ui.qwtPlot->setAxisScale(0,0,40,2);
    QwtPlotMagnifier* magnifier = new QwtPlotMagnifier(ui.qwtPlot->canvas());
   magnifier->setMouseButton(Qt::LeftButton);
    double x[3] ={0};
    double y[3] ={0};
    // QwtPlotCurve *curve1 = new QwtPlotCurve();
    // curve1->setData(new QwtCPointerData(&x[0],&y[0],(size_t)3));    

    QBrush greenBrush(Qt::green);
    QBrush blackBrush(Qt::black);
    QPen outlinePen(Qt::black);
    outlinePen.setWidth(2);
   
   // rectangle = scene->addRect(ui.graphicsView->geometry().x(), ui.graphicsView->geometry().y(),
     //            ui.graphicsView->geometry().width(),ui.graphicsView->geometry().height(), outlinePen, blackBrush);

    // addEllipse(x,y,w,h,pen,brush)
    //ellipse = scene->addEllipse(0, -100, 300, 60, outlinePen, greenBrush);
     // char buffer [33];
          /// itoa(scene->width,buffer,10);
    //sprintf(buffer,"%d",ui.graphicsView->normalGeometry().width());
     //std::string s=std::to_string(scene->width);
   // ui.graphicsView->scene()->addText(buffer, QFont("Arial", 20) );
 
  
    ui.tableView->setModel(qnode.model);
   
  //QObject::connect(&qnode, SIGNAL(data_updated(const leddar_qt::leddar_data)), this, SLOT(displayresults(const leddar_qt::leddar_data)));
    // movable text
    //text->setFlag(QGraphicsItem::ItemIsMovable);
   
}

MainWindow::~MainWindow() {   }


void MainWindow::resizeEvent(QResizeEvent *event)
{
    
}
void MainWindow::displayresults(const leddar_qt::leddar_data msg)
{
printf("\n%d------>%f",msg.ray_segment,msg.distance);
}

/*****************************************************************************
** Implementation [Slots]
*****************************************************************************/



/*
 * These triggers whenever the button is clicked, regardless of whether it
 * is already checked or not.
 */



/*****************************************************************************
** Implemenation [Slots][manually connected]
*****************************************************************************/

/**
 * This function is signalled by the underlying model. When the model changes,
 * this will drop the cursor down to the last line in the QListview to ensure
 * the user can always see the latest log message.
 */


/*****************************************************************************
** Implementation [Menu]
*****************************************************************************/


/*****************************************************************************
** Implementation [Configuration]
*****************************************************************************/





}  // namespace leddar_qt

