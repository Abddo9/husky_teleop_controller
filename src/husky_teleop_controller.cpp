#include <ros/ros.h>
#include <std_msgs/String.h>
#include <geometry_msgs/Twist.h>

ros::Publisher publisher;

void call_back_function( const std_msgs::String & msg) {

        geometry_msgs::Twist message = geometry_msgs::Twist();
        if (msg.data == "I" || msg.data == "i")
	{
		message.linear.x = 1.0;
	}
	else if (msg.data == "U" || msg.data == "u")
	{
		message.linear.x = 1.0;
		message.angular.z = 1.0;
	}
	else if (msg.data == "O" || msg.data == "o")
        {
                message.linear.x = 1.0;
                message.angular.z = -1.0;
        }
	else
        {
                message.linear.x = 0;
                message.angular.z = 0;
        }

        publisher.publish(message);

}



int main(int argc, char** argv) {

	// Initialize ROS
	ros::init(argc, argv, "husky_teleop_controller");

	// Add a node handle
	ros::NodeHandle nodeHandle("~");

	// specify the frequency to 10HZ
	ros::Rate loopRate(1000) ;

	// Make an instance of your ROS package
	//ros_package_template::RosPackageTemplate rosPackageTemplate(nodeHandle);

	ros::Subscriber subscriber = nodeHandle.subscribe("/teleop/cmd", 1, call_back_function);
        publisher = nodeHandle.advertise<geometry_msgs::Twist>("/husky_velocity_controller/cmd_vel", 5);


	while ( ros::ok() ) {

		// the callbacks function will automatically be called.
		ros::spinOnce() ;

		// call the update function

		// sleep for any time remaining to the publish rate
		loopRate.sleep() ;

	}

	return 0;
}
