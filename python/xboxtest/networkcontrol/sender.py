from socket import *
""" Xbox 360 controller support for Python
11/9/13 - Steven Jacobs

This class module supports reading a connected xbox controller.
It requires that xboxdrv be installed first:

    sudo apt-get install xboxdrv

See http://pingus.seul.org/~grumbel/xboxdrv/ for details on xboxdrv

Example usage:

    import xbox
    joy = xbox.Joystick()         #Initialize joystick
    
    if joy.A():                   #Test state of the A button (1=pressed, 0=not pressed)
        print 'A button pressed'
    x_axis   = joy.leftX()        #X-axis of the left stick (values -1.0 to 1.0)
    (x,y)    = joy.leftStick()    #Returns tuple containing left X and Y axes (values -1.0 to 1.0)
    trigger  = joy.rightTrigger() #Right trigger position (values 0 to 1.0)
    
    joy.close()                   #Cleanup before exit
"""

import subprocess
import os
import select
import time

class Sender:
    HOST='127.0.0.1'
    PORT=123
    BUFSIZ=1024
    ADDR=(HOST, PORT)

    """Initializes the joystick/wireless receiver, launching 'xboxdrv' as a subprocess
    and checking that the wired joystick or wireless receiver is attached.
    The refreshRate determines the maximnum rate at which events are polled from xboxdrv.
    Calling any of the Joystick methods will cause a refresh to occur, if refreshTime has elapsed.
    Routinely call a Joystick method, at least once per second, to avoid overfilling the event buffer.
 
    Usage:
        joy = xbox.Joystick()
    """
    def __init__(self,refreshRate = 30):
        
        self.client=socket(AF_INET, SOCK_STREAM)
        self.client.connect(self.ADDR)
        self.proc = subprocess.Popen(['xboxdrv','--no-uinput','--detach-kernel-driver'], stdout=subprocess.PIPE)
        self.pipe = self.proc.stdout
        #
        self.connectStatus = False  #will be set to True once controller is detected and stays on
        self.reading = '0' * 140    #initialize stick readings to all zeros
        #
        self.refreshTime = 0    #absolute time when next refresh (read results from xboxdrv stdout pipe) is to occur
        self.refreshDelay = 1.0 / refreshRate   #joystick refresh is to be performed 30 times per sec by default
        #
        # Read responses from 'xboxdrv' for upto 2 seconds, looking for controller/receiver to respond
        found = False
        while True:
            readable, writeable, exception = select.select([self.pipe],[],[],0)
            if readable:
                response = self.pipe.readline()
                self.client.send(response)
            
if __name__ == '__main__':
    client=Sender()
