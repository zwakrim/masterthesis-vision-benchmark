import cv2
import sys
import serial
import time
import multiprocessing
import threading
import psutil
import jsonlines
import datetime
import numpy as np

def pixeltransform(width , heigh, fpsArray):

    video_capture = cv2.VideoCapture(camera)
    video_capture.set(3,width)
    video_capture.set(4,heigh)


    font = cv2.FONT_HERSHEY_SIMPLEX
    color = (0, 255, 0) #color of the fps ?

    frames = 0
    tick = 0
    fps =0
    i=0

    #print("starting webcam")
    start = time.time()
    while (time.time() - start <= timeout):
        # Capture frame-by-frame
        ret, frame = video_capture.read()
        #hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
        rows =  frame.shape[0]
        cols = frame.shape[1]
        #print (frame.shape)
        #print (frame.size)

        b,g,r = cv2.split(frame)
        #print("b "+ str(b))
        #print("type " + str(type(b)))

        #frame [0:rows,0:cols] = [255,255,255]
        #print(b)

        """
        for x in np.nditer(b):
            b = x * 2
            if b > 255:
                b = 255
            #print(b)
        """
        #l=0
        for i in range(rows):
            for j in range(cols):
                k = frame[i,j]
                r = k[0] * 1.5 + 100
                g = k[1] * 1.5 + 100
                b = k[2] * 1.5 + 100
                frame[i,j] = [r,g,b]

        #print ("l " + str(l))
        #print ("size " + str(frame.size))



        frames = frames +1
        end = time.time()
        seconds = end- start

        if seconds-tick >= 1:
            tick = tick + 1
            fps = frames
            print str(fps)
            fpsArray.append(fps)
            #fpsArray[i]=fps
            i=i+1
            frames = 0


        cv2.putText(frame, "FPS: {}" .format(fps), (15,80) ,font,1,color)


        # Display the resulting frame
        cv2.imshow('Video', frame)
        #cv2.imshow('hsv', hsv)


        if cv2.waitKey(1) & 0xFF == ord('q'):
            break

    cv2.destroyAllWindows()
    video_capture.release()



cascPath = sys.argv[1]
faceCascade = cv2.CascadeClassifier(cascPath)
camera= int(sys.argv[2])
timeout = int(sys.argv[3])
width= int(sys.argv[4])
height = int(sys.argv[5])
fpsArrayshared2 = []

if __name__ == '__main__':

    #print("start")
    #facedetect(220,176,fpsArrayshared2)
    pixeltransform(width,height,fpsArrayshared2)
    timesnow = datetime.datetime.now().strftime('_%Y_%m_%d_%H_%M_%S')

    filename =  'result/'+ "Algopixeltransform_python"+str(width) + str(timesnow)+ '.json'
    with jsonlines.open(filename,mode='w') as outputfile:
        counter =1
        for item in fpsArrayshared2:
            result ={}
            result["algoritme"]= "pixeltransform"
            result["fps"] = item
            result["Type"] = "Python"
            result["Second"] = counter
            result["resolution"] = width
            counter = counter +1
            outputfile.write(result)