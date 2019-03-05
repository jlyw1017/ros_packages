#!/usr/bin/env python
# license removed for brevity
import rospy
from std_msgs.msg import String
import sys,select,termios,tty
import os
import subprocess
import cv2

def getKey():
    settings = termios.tcgetattr(sys.stdin)
    tty.setraw(sys.stdin.fileno())
    rlist, _, _ = select.select([sys.stdin], [], [], 0.1)
    if rlist:
        key = sys.stdin.read(1)
    else:
        key = ''

    termios.tcsetattr(sys.stdin, termios.TCSADRAIN, settings)
    return key

def talker():

    pub = rospy.Publisher('chatter', String, queue_size=10)
    rospy.init_node('talker', anonymous=True)
    rate = rospy.Rate(10) # 10hz
    n=100
    control = 0
    while not rospy.is_shutdown():
        key = getKey()
        if key == 'o':
            pub.publish("pubinfo")
        if key == 'w':
            control = 1
        if key == 's':
            control = 0

  
def imagetovedio():	
    print('run')


