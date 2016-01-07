/**
 * @file /include/leddar_qt/main_window.hpp
 *
 * @brief Qt based gui for leddar_qt.
 *
 * @date November 2010
 **/
#ifndef leddar_qt_MAIN_WINDOW_H
#define leddar_qt_MAIN_WINDOW_H

/*****************************************************************************
** Includes
*****************************************************************************/

#include <QtGui/QMainWindow>
#include "ui_main_window.h"
#include "qnode.hpp"

/*****************************************************************************
** Namespace
*****************************************************************************/

namespace leddar_qt {

/*****************************************************************************
** Interface [MainWindow]
*****************************************************************************/
/**
 * @brief Qt central, all operations relating to the view part here.
 */
class MainWindow : public QMainWindow 
{
Q_OBJECT

public:
	MainWindow(int argc, char** argv, QWidget *parent = 0);
	~MainWindow();

	

public Q_SLOTS:
	/******************************************
	** Auto-connections (connectSlotsByName())
	*******************************************/
	void resizeEvent(QResizeEvent *event);
        void displayresults(const leddar_qt::leddar_data msg);
    /******************************************
    ** Manual connections
    *******************************************/
   
private:
	Ui::MainWindowDesign ui;
	QNode qnode;
      
 
};

}  // namespace leddar_qt

#endif // leddar_qt_MAIN_WINDOW_H
