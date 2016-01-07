/**
 * @file /include/leddar_qt/qnode.hpp
 *
 * @brief Communications central!
 *
 * @date February 2011
 **/
/*****************************************************************************
** Ifdefs
*****************************************************************************/

#ifndef leddar_qt_QNODE_HPP_
#define leddar_qt_QNODE_HPP_

/*****************************************************************************
** Includes
*****************************************************************************/

#include <ros/ros.h>
#include <string>
#include <QThread>
#include <QStringListModel>
#include "LeddarC.h"
#include "LeddarProperties.h"
#include "leddar_qt/leddar_data.h"
#include <iostream>
#include "std_msgs/Float32.h"
#include "std_msgs/Int32.h"
#include <QtGui>
#include <QMessageBox>
/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace leddar_qt {

/*****************************************************************************
** Class
*****************************************************************************/

class QNode : public QThread {
    Q_OBJECT
public:
	QNode(int argc, char** argv );
	virtual ~QNode();
	bool init();
	bool init(const std::string &master_url, const std::string &host_url);
       
        void leddar_recieve_data(const leddar_qt::leddar_data msg);
	
	/*********************
	** Logging
	**********************/
                /////////////////////////////////////////////////////
            int ray_segment;
            float obj_distance;
            QStandardItemModel *model;
             
           //////////////////////////////////////////////////////////
            
	enum LogLevel {
	         Debug,
	         Info,
	         Warn,
	         Error,
	         Fatal
	 };

	QStringListModel* loggingModel() { return &logging_model; }
	void log( const LogLevel &level, const std::string &msg);

Q_SIGNALS:
	void loggingUpdated();
        void rosShutdown();
        

private:
          void run();
	int init_argc;
	char** init_argv;
	ros::Publisher chatter_publisher;
    QStringListModel logging_model;
};

}  // namespace leddar_qt

#endif /* leddar_qt_QNODE_HPP_ */
