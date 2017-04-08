#!/usr/bin/env python

# This node subscribes the message published by the x_publisher node, additionally it calculates the time elapsed between incoming messages, converts it to frequency,
# and Finally publishes the real rate frequency on a topic in order to be used by other nodes (specially for visualization). Note: This code is based on the one showed
# on the ROS Wiki Tutorials

import rospy
from performance_tests.msg import SuperAwesome #Custom created message 
from std_msgs.msg import Float64 #Double message for real rate publication

#Global variables
previous_time=0 #Initialize previous time for the first incoming message
pub = rospy.Publisher('/RealRate', Float64, queue_size=1000) #The publisher variable should be declared global, as the message will be sent inside the Subscriber callback

#Subscriber callback
def callback(data):
    global previous_time

    now=rospy.get_time() #Get actual time
    elapsed_time=now-previous_time #Obtain elapsed time from the difference between actual and previous time
    previous_time=now #Assign the actual time to the previous one in order to use it on the next incoming message
    freq_rate=1/elapsed_time #Convert elapsed time to frequency
    rospy.loginfo("REAL RATE %f",freq_rate )
    pub.publish(freq_rate) #Publish real frequency rate

def listener():
    
    rospy.init_node('py_subscriber', anonymous=True)

    rospy.Subscriber("/SuperAwesomeTopic", SuperAwesome, callback) #Custom string message subscriber
    
    rospy.spin()

if __name__ == '__main__':
    listener()
