#!/usr/bin/env python

import rospy
from std_msgs.msg import Int32
import numpy as np
from PIL import Image
import pytesseract
import cv2
import os
import smbus
from picamera import PiCamera
from time import sleep
#from rpi_cam.msg import Letter 

cam=PiCamera()

pub = rospy.Publisher('cam', Int32, queue_size=5)

def responseWall():
    
    print('prepare, taking the photo')
    sleep(4)
    image='0.jpg'
    cam.capture(image)
    cam.stop_preview()

    config = '--psm 10 --oem 3' 
    preprocess = "blur"

    image = cv2.imread(image)
    gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)



    if preprocess == "thresh":
        gray = cv2.threshold(gray, 0, 255,
        cv2.THRESH_BINARY | cv2.THRESH_OTSU)[1]


    elif preprocess == "blur":
        gray = cv2.medianBlur(gray, 3)




    filename = "{}.png".format(1)
    cv2.imwrite(filename, gray)
    i=1
    while i<3:
        img = cv2.imread(str(i)+'.png', cv2.IMREAD_UNCHANGED)
        width = int(img.shape[1] / 5)
        height = int(img.shape[0] / 5)
        dim = (width, height)
        resized = cv2.resize(img, dim, interpolation = cv2.INTER_AREA)
        filename = "{}.png".format(i+1)
        cv2.imwrite(filename, resized)

        text =pytesseract.image_to_string(resized,lang='eng',config=config)
        print('working')
        print(text)
        i+=1;
        if 'h' in text or 'H' in text:
            print "i respond H"
            return 1
            break
            
        elif 's' in text or 'S' in text:
            print "i respond S"
            return 2
            break
        elif 'u' in text or 'U' in text:
            print "i respond U"
            return 3
            break
        else:
			return 0

        if i>3:
            print "nothing interesting here"
            return 0
            break

            
                
   


def listener():

    rospy.init_node('rpi_cam')
    while (True):
        msg = Int32();
        msg.data=responseWall()
    	pub.publish(msg)


if __name__ == '__main__':
    print "Running"
    listener()
    	

