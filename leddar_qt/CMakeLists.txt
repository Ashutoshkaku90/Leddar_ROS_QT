##############################################################################
# CMake
##############################################################################

cmake_minimum_required(VERSION 2.8.0)
project(leddar_qt)

##############################################################################
# Catkin
##############################################################################

 find_path ( QWT_INCLUDE_DIR
     NAMES qwt_plot.h
     HINTS ${QT_INCLUDE_DIR}
     PATH_SUFFIXES qwt qwt-qt3 qwt-qt4 qwt-qt5
   )
set ( QWT_INCLUDE_DIRS ${QWT_INCLUDE_DIR} )

 find_library ( QWT_LIBRARY
     LIBRARY NAMES libqwt.so
     HINTS "/usr/lib" 
   )
 set ( QWT_LIBRARIES ${QWT_LIBRARY} )

include ( FindPackageHandleStandardArgs )
   find_package_handle_standard_args( Qwt DEFAULT_MSG QWT_LIBRARY QWT_INCLUDE_DIR)
# qt_build provides the qt cmake glue, roscpp the comms for a default talker


find_package(catkin REQUIRED COMPONENTS qt_build roscpp rospy message_generation)
include_directories(${catkin_INCLUDE_DIRS})
include_directories(${QWT_INCLUDE_DIRS})
# Use this to define what the package will export (e.g. libs, headers).
# Since the default here is to produce only a binary, we don't worry about
# exporting anything. 
 
add_message_files(
   FILES
   leddar_data.msg
#   Message2.msg
)

generate_messages(
   DEPENDENCIES
   std_msgs
 )
catkin_package(CATKIN_DEPENDS message_runtime)



##############################################################################
# Qt Environment
##############################################################################

# this comes from qt_build's qt-ros.cmake which is automatically 
# included via the dependency call in package.xml
rosbuild_prepare_qt4(QtCore QtGui) # Add the appropriate components to the component list here

##############################################################################
# Sections
##############################################################################

file(GLOB QT_FORMS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ui/*.ui)
file(GLOB QT_RESOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} resources/*.qrc)
file(GLOB_RECURSE QT_MOC RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} FOLLOW_SYMLINKS include/leddar_qt/*.hpp)

QT4_ADD_RESOURCES(QT_RESOURCES_CPP ${QT_RESOURCES})
QT4_WRAP_UI(QT_FORMS_HPP ${QT_FORMS})
QT4_WRAP_CPP(QT_MOC_HPP ${QT_MOC})

##############################################################################
# Sources
##############################################################################


file(GLOB_RECURSE QT_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} FOLLOW_SYMLINKS src/*.cpp)


##############################################################################
# Binaries
##############################################################################
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib)

add_executable(leddar_ros leddar_ros/leddar_ros.cpp)
add_executable(leddar_qt ${QT_SOURCES} ${QT_RESOURCES_CPP} ${QT_FORMS_HPP} ${QT_MOC_HPP} )


target_link_libraries(leddar_ros ${catkin_LIBRARIES} ${QT_LIBRARIES}  EvalKit LeddarC ModuleG Orange Platform sidetecM Tracker vtec dtec Leddar LeddarTech)
target_link_libraries(leddar_qt ${QT_LIBRARIES} ${catkin_LIBRARIES} -lqwt -lEvalKit LeddarC ModuleG Orange Platform sidetecM Tracker vtec dtec Leddar LeddarTech)


install(TARGETS leddar_qt RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})
install(TARGETS leddar_ros RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})

