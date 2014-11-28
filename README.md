KalmanFilterFollower
====================

Ece4330 Final Project

Note: This project requires the MobileSim and gnuplot programs to be available.

Kalman/, Object/, Reactive/, & Wander/ folders are build configurations for the
separate programs in this project.

	Object configuration   - Path recording program, allows user to drive the 
	                         robot, recording path for a repeatable path for
	                         the Wander configuration in Data/object.dat.
	                       
   	Wander configuration   - Simulated object to track.  Follows the path stored
   	                         in Data/object.dat, and provides a repeatable path
   	                         to compare multiple tracking programs. Also records
   	                         the path for comparison in Data/comparison.dat.
   	                       
	Reactive configuration - Tracking program based on reaction to current 
							 tracking object reading from laser sensor.
	
	Kalman configuration   - Tracking program that utilizes a Kalman Filter to
	 						 predict the upcoming position of the tracked 
	 						 object.

Misc/ contains all project files not needed for build. Gnuplot format files, 
*.gpt, for all grapsh generated for presentation. The project proposal is 
included in this folder.

Scripts/ contains bash scripts that will allow running the presentation on the 
MobileSim program.  Note: ctrl-p resets the position of the robots in the 
simulator. 

Headers/ are included *.hpp files that are required for at least one build 
configuration.

Source/ contains all *.cpp files required for at least one build configuration.

Data/ contains all stored *.dat files needed for tracking and plotting.
