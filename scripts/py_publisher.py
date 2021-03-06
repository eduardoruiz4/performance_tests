#!/usr/bin/env python

# This node Publishes a custom string message, the loop_rate for the communication can be modified using dynamic parameter reconfiguration. Furthermore, in order to
# visualize how the loop_rate changes, a message is published with this desired rate information. Note: this node is based on the one showed on the ROS Wiki Tutorials


import rospy
from performance_tests.msg import SuperAwesome #Custom created string message
from std_msgs.msg import Int32 #Integer message for desired rate publication
from dynamic_reconfigure.server import Server as DynamicReconfigureServer #dynamic reconfiguration server
from performance_tests.cfg import dynparamConfig 


#Publisher Class
class Publisher():

	#Dynamic reconfiguration callback
	def callback(self, config, level):
		self.loop_rate=config["loop_rate"]
		return config
	
	def __init__(self):
	    pub = rospy.Publisher('/SuperAwesomeTopic', SuperAwesome, queue_size=1000) #Custom message publisher definition
	    pub_ = rospy.Publisher('/DesiredRate', Int32, queue_size=1000)#Real rate message publisher definition
	    rospy.init_node('py_publisher', anonymous=True) 
	    
	    
	    self.server = DynamicReconfigureServer(dynparamConfig, self.callback) #Dynamic reconfiguration definition

	    while not rospy.is_shutdown():
	
	   	rate = rospy.Rate(self.loop_rate) #Modifiable loop rate

		hello_str = "hello world" 
		rospy.loginfo('DESIRED RATE %d' % (self.loop_rate))
		pub.publish(hello_str) #Custom message publication
		pub_.publish(self.loop_rate) #Real Rate message publication
	
		rate.sleep()

#Main
if __name__ == '__main__':
    try:
	
        pu=Publisher() #Publisher object
    except rospy.ROSInterruptException:
        pass
