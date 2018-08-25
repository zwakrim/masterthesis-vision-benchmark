import cv2
import sys
import serial
import time
import multiprocessing
import threading
import psutil
import jsonlines
import datetime
import platform
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


    global totalCalcTime
    totalCalcTime=0
    start = time.time()
    while (time.time() - start <= timeout):
        # Capture frame-by-frame
        ret, frame = video_capture.read()


        rows =  frame.shape[0]
        cols = frame.shape[1]
        result = np.zeros((rows,cols,3), np.uint8)

    #print (frame.shape)
        #print (frame.size)

        #b,g,r = cv2.split(frame)
        #print("b "+ str(b))
        #print("type " + str(type(b)))

        #frame [0:rows,0:cols] = [255,255,255]
        #print(b)
        beginCalcTime = time.time()
        for i in range(0,rows):
            for j in range(0,cols):
                #b,g,r = cv2.split(frame)
                #k = frame[i,j]
                #print frame[i,j,0]
                b= frame[i,j,0] * 1.5 + 100
                g = frame[i,j,1] * 1.5 + 100
                r = frame[i,j,2] * 1.5 + 100
                result[i,j] = [b,g,r]
        endCalcTime = time.time() - beginCalcTime
        totalCalcTime = totalCalcTime + endCalcTime


        #print ("l " + str(l))
        #print ("size " + str(frame.size))

        frames = frames +1
        end = time.time()
        seconds = end- start

        if seconds-tick >= 1:
            tick = tick + 1
            fps = frames
            #print str(fps)
            fpsArray.append(fps)
            #fpsArray[i]=fps
            i=i+1
            frames = 0


        cv2.putText(frame, "FPS: {}" .format(fps), (15,80) ,font,1,color)


        # Display the resulting frame
        cv2.imshow('Video', frame)
        cv2.imshow('lol',lol)
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

lol=0

if __name__ == '__main__':

    #print("start")
    #facedetect(220,176,fpsArrayshared2)
    beginTime = time.time()
    pixeltransform(width,height,fpsArrayshared2)
    endTime = time.time() - beginTime
    #print "total "+str(endTime)
    #print "calc  "+str(totalCalcTime)
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
            result["ratioCalTime"] = totalCalcTime/endTime * 100
            result["node"] = platform.node ()
            counter = counter +1
            outputfile.write(result)