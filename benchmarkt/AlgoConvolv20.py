import cv2
import sys
import time
import numpy as np
import jsonlines
import datetime
import platform

def convolvimg(width , heigh, fpsArray):
    video_capture = cv2.VideoCapture(camera)
    video_capture.set(3,width)
    video_capture.set(4,heigh)

    font = cv2.FONT_HERSHEY_SIMPLEX
    color = (0, 255, 0)

    frames = 0
    tick = 0
    fps =0
    i=0

    global totalCalcTime
    totalCalcTime=0
    start = time.time()
    while (time.time() - start <= timeout):
        ret, frame = video_capture.read()
        frames = frames +1
        end = time.time()
        seconds = end- start
	#print(frame.shape)
        if seconds-tick >= 1:
            tick = tick + 1
            fps = frames
            fpsArray.append(fps)
            #fpsArray[i]=fps
            i=i+1
            frames = 0

        #hsv hue sat value
        #hsv = cv2.cvtColor(frame,cv2.COLOR_BGR2HSV) #convert to hsv color

        #lower_color= np.array([150,150,50])
        #upper_color= np.array([180,255,255])

        #mask = cv2.inRange(hsv,lower_color,upper_color)
        #result = cv2.bitwise_and(frame,frame,mask=mask)

        #blur= cv2.medianBlur(frame,5,0)
        #median = cv2.medianBlur(result,15)
        beginCalcTime = time.time()

        kernel = np.ones((20,20),np.float32)/400
        filter = cv2.filter2D(frame,-1,kernel)

        endCalcTime = time.time() - beginCalcTime
        totalCalcTime = totalCalcTime + endCalcTime

        cv2.putText(frame, "FPS: {}" .format(fps), (15,80) ,font,1,color)
        cv2.putText(filter, "FPS: {}" .format(fps), (15,80) ,font,1,color)

        cv2.imshow('original',frame)

        cv2.imshow('filtered',filter)

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
    beginTime = time.time()
    convolvimg(width,height,fpsArrayshared2)
    endTime = time.time() - beginTime
    #print("fps,"+",".join(str(x) for x in fpsArrayshared2)+ ",")
    timesnow = datetime.datetime.now().strftime('_%Y_%m_%d_%H_%M_%S')

    filename =  'result/'+ "AlgoConvolution20_python_"+str(width) + str(timesnow)+ '.json'
    with jsonlines.open(filename,mode='w') as outputfile:
        counter =1
        for item in fpsArrayshared2:
            result ={}
            result["algoritme"]= "Convolution20_python"
            result["fps"] = item
            result["Type"] = "Python"
            result["Second"] = counter
            result["resolution"] = width
            result["ratioCalTime"] = totalCalcTime/endTime * 100
            counter = counter +1
            outputfile.write(result)

