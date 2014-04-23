/**
 * @file /include/segbot_logical_translator_gui/qnode.hpp
 *
 * @brief Communications central!
 *
 * @date February 2011
 **/
/*****************************************************************************
** Ifdefs
*****************************************************************************/

#ifndef segbot_logical_translator_gui_QNODE_HPP_
#define segbot_logical_translator_gui_QNODE_HPP_

/*****************************************************************************
** Includes
*****************************************************************************/

#include <ros/ros.h>
#include <actionlib/server/simple_action_server.h>
#include <actionlib/client/simple_action_client.h>
#include <actionlib/client/terminal_state.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <QThread>
#include <QStringListModel>

#include <bwi_mapper/map_loader.h>
#include <tf/transform_listener.h>
#include <segbot_logical_translator_gui/ClingoInterfaceAction.h>
#include <segbot_logical_translator/door_handler.h>
#include <segbot_logical_translator/gazebo_handler.h>
#include <segbot_logical_translator/cost_estimator.h>
#include <nav_msgs/Odometry.h>
#include <opencv/cv.h>

#include "tf/transform_listener.h"
#include "tf/message_filter.h"
#include "message_filters/subscriber.h"

/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace segbot_logical_translator_gui {

/*****************************************************************************
** Class
*****************************************************************************/

  class QNode : public QThread {
    Q_OBJECT
    public:
      QNode(int argc, char** argv );
      virtual ~QNode();
      bool init();
      void run();

      /* Service callback */
      void clingoInterfaceHandler(
          const segbot_logical_translator_gui::ClingoInterfaceGoalConstPtr &req);

      /* Get robot location */
      void odometryHandler(const nav_msgs::Odometry::ConstPtr &odom);

      bool newLocationReceived(const std::string& loc);

      /* Display stuff */
      std::string display_text_;
      bool button1_enabled_;
      std::string button1_text_;
      bool button2_enabled_;
      std::string button2_text_;
      cv::Mat generated_image_;
      bool location_box_enabled_;

    Q_SIGNALS:
      void rosShutdown();
      void updateFrameInfo();

    private:
      int init_argc;
      char** init_argv;

      void senseDoorProximity(std::vector<segbot_logical_translator_gui::ClingoFluent>& fluents, int door_idx = -1);
      bool executeRobotGoal(const geometry_msgs::PoseStamped& pose);

      /* Ros Stuff */
      boost::shared_ptr<ros::NodeHandle> nh_;
      boost::shared_ptr<actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> > robot_controller_;
      boost::shared_ptr<actionlib::SimpleActionServer<
          segbot_logical_translator_gui::ClingoInterfaceAction> > as_;

      /* Robot Location */
      std::string global_frame_;
      boost::shared_ptr<tf::TransformListener> tf_;
      boost::shared_ptr<tf::MessageFilter<nav_msgs::Odometry> > tf_filter_;
      boost::shared_ptr<message_filters::Subscriber<nav_msgs::Odometry> > 
        odom_subscriber_;
      float robot_x_;
      float robot_y_;
      float robot_yaw_;

      /* Feedback from gui */
      bool location_received_;
      std::string person_name_;
      std::string person_location_;

      /* DoorHandler */
      std::string map_file_;
      std::string door_file_;
      std::string location_file_;
      boost::shared_ptr<bwi_mapper::MapLoader> mapper_;
      boost::shared_ptr<segbot_logical_translator::DoorHandler> handler_;
      boost::shared_ptr<segbot_logical_translator::GazeboHandler> gh_;
      boost::shared_ptr<segbot_logical_translator::CostEstimator> ce_;

      bool sim_auto_door_;
      int close_door_idx_;
      int prev_door_idx_;
      
  };

}  // namespace segbot_logical_translator_gui

#endif /* segbot_logical_translator_gui_QNODE_HPP_ */
