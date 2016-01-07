/**
 * @file /src/qnode.cpp
 *
 * @brief Ros communication central!
 *
 * @date February 2011
 **/

/*****************************************************************************
** Includes
*****************************************************************************/

#include <ros/ros.h>
#include <ros/network.h>
#include <string>
#include <std_msgs/String.h>
#include <sstream>
#include "../include/leddar_qt/qnode.hpp"

/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace leddar_qt {

/*****************************************************************************
** Implementation
*****************************************************************************/

QNode::QNode(int argc, char** argv ) :
	init_argc(argc),
	init_argv(argv)
	{}

QNode::~QNode() 
{
if(ros::isStarted()) 
    {
      ros::shutdown(); // explicitly needed since we use ros::start();
      ros::waitForShutdown();
    }
	wait();
   
}

bool QNode::init() {

        std::cout << "-------------------------------------------------"  << std::endl;
  std::cout << "               leddar ros initialized            "  << std::endl;
  std::cout << "-------------------------------------------------"  << std::endl;
	 model = new QStandardItemModel(0,0,this);
         model->setHorizontalHeaderItem(0, new QStandardItem(QString("Segment")));
         model->setHorizontalHeaderItem(1, new QStandardItem(QString("Distance")));
         model->setHorizontalHeaderItem(2, new QStandardItem(QString("Amplitude")));
	 start();
         
	return true;
}

bool QNode::init(const std::string &master_url, const std::string &host_url) {
	std::map<std::string,std::string> remappings;
	remappings["__master"] = master_url;
	remappings["__hostname"] = host_url;
	ros::init(remappings,"leddar_qt");
	if ( ! ros::master::check() ) {
		return false;
	}
	ros::start(); // explicitly needed since our nodehandle is going out of scope.
	ros::NodeHandle n;
	// Add your ros communications here.
	chatter_publisher = n.advertise<std_msgs::String>("chatter", 1000);
	start();
	return true;
}
void QNode::leddar_recieve_data(const leddar_qt::leddar_data msg)
{
  printf("\n%d------>%f",msg.ray_segment,msg.distance);
  ray_segment=msg.ray_segment;
  obj_distance=msg.distance;
  //model->insertRow();
  //model->setData(model->index(0,ray_segment),"1");
}
void QNode::run() 
{
  ros::init(init_argc,init_argv,"leddar_qt");
	ros::NodeHandle n;
        ros::Subscriber leddar_data;
       
        
  
       
  leddar_data=n.subscribe<leddar_qt::leddar_data>("leddar_data",1,&QNode::leddar_recieve_data,this);
  ros::spin();	
  std::cout << "Ros shutdown, proceeding to close the gui." << std::endl;
}



void QNode::log( const LogLevel &level, const std::string &msg)
 {
	logging_model.insertRows(logging_model.rowCount(),1);
	std::stringstream logging_model_msg;
	switch ( level ) {
		case(Debug) : {
				ROS_DEBUG_STREAM(msg);
				logging_model_msg << "[DEBUG] [" << ros::Time::now() << "]: " << msg;
				break;
		}
		case(Info) : {
				ROS_INFO_STREAM(msg);
				logging_model_msg << "[INFO] [" << ros::Time::now() << "]: " << msg;
				break;
		}
		case(Warn) : {
				ROS_WARN_STREAM(msg);
				logging_model_msg << "[INFO] [" << ros::Time::now() << "]: " << msg;
				break;
		}
		case(Error) : {
				ROS_ERROR_STREAM(msg);
				logging_model_msg << "[ERROR] [" << ros::Time::now() << "]: " << msg;
				break;
		}
		case(Fatal) : {
				ROS_FATAL_STREAM(msg);
				logging_model_msg << "[FATAL] [" << ros::Time::now() << "]: " << msg;
				break;
		}
	}
	QVariant new_row(QString(logging_model_msg.str().c_str()));
	logging_model.setData(logging_model.index(logging_model.rowCount()-1),new_row);
	Q_EMIT loggingUpdated(); // used to readjust the scrollbar
}

}  // namespace leddar_qt
