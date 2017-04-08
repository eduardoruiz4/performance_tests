# performance_tests
Exercise 1- Performance Test - ROS Package

How does this package work?

As expected, the cpp nodes are on the src folder while the py nodes are on the scripts folder. The custom SuperAwesome message is 
on the msg folder. The dynamic reconfiguration cfg file is on the cfg folder and finally, obviously, the launch files are on the 
launch folder.

You can run the exercise by running the launch files. There are 4 different launch files, they launch the 4 different publisher/
subscriber combinations. These files launch the proper publish and subscriber nodes (indicated on the file name), the rqt_reconfigure in order to choose, by a GUI, the roop_late value; and a rqt_plot showing how the real value is changing through time against the desired value.

If the real rate value is changed from 1 on the rqt_reconfigure GUI, then the user can visualize in which desired rate the real 
rate becomes slower (lower frequency) and unstable (several peaks on the plot).

If you want to try this package, remember to make executable the python files, including the dynparam.cfg.

