#!/usr/bin/env python2.7

"""
Code was used to detect the position of the Ball being passed by the Manual Robot. Successful position detection could lead to the Autonomous Robot initiating the recieve command
"""

# Intial Library Imports
import cv2
import numpy as np
import RPi.GPIO as GPIO

#Setting the output and input pins of the raspberry pi
OUTPUT_PINS = [23,24,25]
GPIO.setmode(GPIO.BCM)
GPIO.setup(OUTPUT_PINS,GPIO.OUT)
GPIO.setup(16,GPIO.IN)

# Initializing Video Capture
cap = cv2.VideoCapture(0)

# Main execution loop
while(cap.isOpened()):

    # Reading the input frames
    ret,frame = cap.read()

    # Converting to HSV Format
    hsv_image = cv2.cvtColor(frame,cv2.COLOR_BGR2HSV)

    # Hardcoded colour Ranges (HSV)
    lower = np.array([102,58,123])
    upper = np.array([117,197,240])

    # Binarized Image based on Colour Ranges
    binary_image = cv2.inRange(hsv_image,lower,upper)

    # Generating Contours
    contours,heirarchy = cv2.findContours(binary_image,1,2)

    number_of_contours = len(contours)
    if number_of_contours>=1:
        # Then we set the first contour as the largest contour
        largest_contour = contours[0]
        if(number_of_contours!=1):
            for i in range(1, number_of_contours-1):
                contour = contours[i]
                A = cv2.contourArea(contour)
                B = cv2.contourArea(largest_contour)
                if (A > B):
                    largest_contour = contour

        # Assuming that the center of the Bounding Rectangle is roughly the actual center of the object
        x,y,w,h = cv2.boundingRect(largest_contour)
        # Drawing a Bounding Rectangle
        cv2.rectangle(frame,(x,y),(x+w,y+h),(0,255,0),3)
        # Extracting the centers
        cx, cy = (x+w)/2, (y+h)/2


        if (cv2.contourArea(largest_contour)>7000):
            print(cv2.contourArea(largest_contour))
            if cx<160:
                print('left')
                GPIO.output(OUTPUT_PINS,(1,0,0))
            elif cx>250:
                print('right')
                GPIO.output(OUTPUT_PINS,(0,1,0))
            elif 160<cx and cx<250:
                print('middle')
                GPIO.output(OUTPUT_PINS,(0,0,1))
            else:
                print('This message shouldn\'t exist, check code')
                GPIO.output(OUTPUT_PINS,(0,0,0))
        else:
            print('Object Not Found - TYPE 1')
            GPIO.output(OUTPUT_PINS,(0,0,0))
    else:
        print('Object Not Found - TYPE 1')
        GPIO.output(OUTPUT_PINS,(0,0,0))

    #cv2.imshow('binary',binary_image)
    #cv2.imshow('frame',frame)
    if GPIO.input(16) == GPIO.HIGH :
       break

cv2.destroyAllWindows()
cap.release()
GPIO.cleanup()
