# Simple Tower Defense
The project can be compiled in at least Linux and Windows (with MinGW). 
If SFML 2.5.1 isn’t installed by default it must be installed. 
All of the commands must be done from the src-folder. 
Building and compiling the project can be done with the command “make build”. 
If “clean” is not working it must be done manually; 
first, run the command “make noclean” and after that run the command “rm *.o”. 
This seemed to be an issue to some of us in Windows but has not happened in Linux. 
To run the project one should use different commands in Linux and Windows. 
In Linux the command is “make lrun” and on Windows “make wrun”. 
The linux version does compile but it is a bit laggy. We think this is beacuse of the SFML library but we are not sure.
