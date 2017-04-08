
// This node Publishes a custom string message, the loop_rate for the communication can be modified using dynamic parameter reconfiguration. Furthermore, in order to
// visualize how the loop_rate changes, a message is published with this desired rate information. Note: this node is based on the one showed on the ROS Wiki Tutorials


#include "ros/ros.h"
#include "performance_tests/SuperAwesome.h" //Custom created string message
#include "std_msgs/Int32.h" //Ineteger message for desired rate publication
#include <sstream>
#include <dynamic_reconfigure/server.h>
#include <performance_tests/dynparamConfig.h>

int loopRate=10; //Default rate

//Dynamic reconfiguration callback
void callback(performance_tests::dynparamConfig &config, uint32_t level)
{
	
	loopRate=config.loop_rate;

}

//Main Function

int main(int argc, char **argv)
{


	ros::init(argc, argv, "cpp_publisher");

	ros::NodeHandle n;


	ros::Publisher chatter_pub = n.advertise<performance_tests::SuperAwesome>("/SuperAwesomeTopic", 1000);//Custom message publisher definition
	ros::Publisher chatter_pub_ = n.advertise<std_msgs::Int32>("/DesiredRate", 1000);//Rate message publisher definition
	
	//Dynamic Reconfiguration	
	dynamic_reconfigure::Server<performance_tests::dynparamConfig> server;
	dynamic_reconfigure::Server<performance_tests::dynparamConfig>::CallbackType f;
	f = boost::bind(&callback, _1, _2);
	server.setCallback(f);


	while (ros::ok())
	{
		ros::Rate loop_rate(loopRate); //The frequency is assigned by the value obtained from the dynamic reconfiguration
		performance_tests::SuperAwesome msg; //Custom message definition
		std_msgs::Int32 msg_;//Integer message for rate publication for visualization
		std::stringstream ss;
		ss << "HELLO";// String assingment
		msg.SuperAwesome = ss.str();//Custom message assignment
		msg_.data=loopRate;//Rate message assignment

		ROS_INFO("DESIRED RATE %d", loopRate);

		chatter_pub.publish(msg);//Custom message publication
		chatter_pub_.publish(msg_);//Rate message publication

		ros::spinOnce();
		loop_rate.sleep();    
	}


	return 0;
}

