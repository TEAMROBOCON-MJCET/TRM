#!/usr/bin/env python2.7

"""
Code was used to detect the color of the Ball when the autonomous Robot recieved it from the 
Manual Robot. Successful color recognition initiated the recieve command on the Autonomous
Robot
"""

# Intial Library Imports
import cv2
import numpy as np
import RPi.GPIO as GPIO

# Setting up the Raspberry-Pi-3 Pins
OUTPUT_PINS = [23,24,25]
GPIO.setmode(GPIO.BCM)
#GPIO.setwarnings(False)
GPIO.setup(OUTPUT_PINS,GPIO.OUT)
GPIO.setup([12,16,18],GPIO.IN)



def find_area_of_largest_contour(binary_image):
    """
    Takes an input binarized Image to and finds the area of the largest contour

    Input:  [Binary Image]  Resolution of Image or other characteristics are not important
                            but the image must be single channel (or converted to a single
                            channel image). Can be reconstructed later

    Output: [Float]         Returns the area of the largest contour found in the Image
    """

    # Extraction of all the contours within the Image
    contours_set, heirarchy = cv2.findContours(binary_image,1,2)
    # We Store the number of Contours found in a varible
    number_of_contours_in_set = len(contours_set)
    # If any countours exist
    if (number_of_contours_in_set >= 1):
        # Then we set the first contour as the largest contour
        largest_contour = contours_set[0]
        # We then cycle through the list of contours to find the greatest contour
        # This is done as in several instances, the largest contour is not the first one 
        if(number_of_contours_in_set != 1):
            for i in range(1, number_of_contours_in_set - 1):
                contour = contours_set[i]
                area1 = cv2.contourArea(contour)
                area2 = cv2.contourArea(largest_contour)
                if area1>area1 :
                    largest_contour = contour
        # We return the Area of the Largest Contour
        return cv2.contourArea(largest_contour)
    else:
        # If no contour was found
        return 0


# Initializing relevant variables
count_area1,count_area2,count_area3 = 0,0,0

# Initializing Video Capture
global cap
cap = cv2.VideoCapture(0)

while(True):

    # The recognition process starts when a command is received from the Central Arduino
    if (GPIO.input(12) == GPIO.HIGH):
        # print ('In Tha Loop')

        # As long as the camera is getting an input
        while(cap.isOpened()):

            # Reading the input frames and selecting an ROI
            ret,frame = cap.read()
            frame = frame[148:345,188:580]

            # Converting to HSV Format
            hsv_image = cv2.cvtColor(frame,cv2.COLOR_BGR2HSV)

            # Hardcoded Colour Ranges, each consists of a lower & upper pair
            lower1 = np.array([16,54,10])     #yellow ball 23
            upper1 = np.array([89,122,250])

            lower2 = np.array([84,208,10])      #blue ball 24
            upper2 = np.array([121,255,250])

            lower3 = np.array([117,70,114])      #blue frisbee 25
            upper3 = np.array([175,145,250])
            
            # We then search for these colour ranges in the Image
            binary_image1 = cv2.inRange(hsv_image,lower1,upper1)
            binary_image2 = cv2.inRange(hsv_image,lower2,upper2)
            binary_image3 = cv2.inRange(hsv_image,lower3,upper3)

            # For Future use, blurring and eroding the image will be helpful as it reduces the number
            # of contours thereby increasing the speed of execution

            # We find and draw the contours for each of the colour ranges in the Image

            area1 = find_area_of_largest_contour(binary_image1)
            area2 = find_area_of_largest_contour(binary_image2)
            area3 = find_area_of_largest_contour(binary_image3)
            
            # We then select the largest colour found in the Image if it lies above a certain threshold
            # But the process may be susceptible to errors, so we setup a counter for the times it was 
            # detected and then we select a colour if it was detected at least 5 times 
            if area1>area2 and area1>area3 and area1>5000:
                count_area1 += 1
            elif area2>area1 and area2>area3 and area2>5000:
                count_area2 += 1
            elif area3>area1 and area3>area2 and area3>5000:
                count_area3 += 1
            else:
                pass
                # print('No color large enough detected')

            if count_area1 == 5:
                # We reset the counter
                count_area1,count_area2,count_area3 = 0,0,0
                # We actuate the corresponding output PIN
                GPIO.output(OUTPUT_PINS,(1,0,0))
                print('Green detected')
            elif count_area2 == 5:
                # We reset the counter
                count_area1,count_area2,count_area3 = 0,0,0
                # We actuate the corresponding output PIN
                GPIO.output(OUTPUT_PINS,(0,1,0))
                print('Yellow detected')
            elif count_area3 == 5:                
                # We reset the counter
                count_area1,count_area2,count_area3 = 0,0,0                
                # We actuate the corresponding output PIN
                GPIO.output(OUTPUT_PINS,(0,0,1))
                print('Blue detected')
            else:
                GPIO.output(OUTPUT_PINS,(0,0,0))
                print('Waiting for ze color...')
            
            # We quit the loop if the command from the Central Microcontroller is no longer active
            if cv2.waitKey(1) & GPIO.input(12) == (GPIO.LOW):
                break
        # This is to switch the camera, can be initiated from the Central Microcontroller
        if (GPIO.input(18) == GPIO.HIGH):
            cap = cv2.VideoCapture(1)
    # Exit command
    elif (GPIO.input(16) == GPIO.HIGH):
        print ('Pin 16 set HIGH, programs quits here')
        break
    else:
        print ('Waiting for pin BCM 12 to be HIGH.....')
        GPIO.output(OUTPUT_PINS,(0,0,0))
        #set all the GPIO pins to zero (i.e. 23,24 & 25) is it holds the output as true even after quitting the loop

# Terminating Windows                
cv2.destroyAllWindows()
cap.release()
GPIO.cleanup()