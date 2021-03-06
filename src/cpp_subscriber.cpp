// This node subscribes the message published by the x_publisher node, additionally it calculates the time elapsed between incoming messages, converts it to frequency,
// and Finally publishes the real rate frequency on a topic in order to be used by other nodes (specially for visualization)

#include "ros/ros.h"
#include "performance_tests/SuperAwesome.h" //Custom created string message
#include "std_msgs/Float64.h" //Double message used for real rate publication for plot usage

//GLOBAL VARIABLES

double previous_time = 0; //Initialize previous time for the first incoming message
double time_now, elapsed_time, rate_freq;
ros::Publisher chatter_pub; //The publisher variable should be declared global, as the message will be sent inside the Subscriber callback


//SUBSCRIBER CALLBACK
void chatterCallback(const performance_tests::SuperAwesome::ConstPtr& msg)
{
	time_now = ros::Time::now().toSec(); //Get actual time
	elapsed_time = time_now - previous_time; //Obtain elapsed time from the difference between actual and previous time
	previous_time=time_now;// Assign the actual time to the previous one in order to use it on the next incoming message
	rate_freq=1/elapsed_time;// Obtain frequency rate from elapsed time
	ROS_INFO("REAL RATE %f",rate_freq); 

	std_msgs::Float64 msg_;// A double message is declared
	msg_.data=rate_freq;// Assign the frequency rate to the message
	chatter_pub.publish(msg_);//Publish the frequency rate to be read by the rqt_plot
}

//MAIN FUNCTION
int main(int argc, char **argv)
{

	ros::init(argc, argv, "cpp_subscriber");

	ros::NodeHandle n;

	chatter_pub = n.advertise<std_msgs::Float64>("/RealRate", 1000); //Real Frequency Rate Publisher
	ros::Subscriber sub = n.subscribe("/SuperAwesomeTopic", 1000, chatterCallback);//Custom string message subscriber

	ros::spin();

	return 0;
}

