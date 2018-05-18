import cv2
import sys
import serial
import time
import multiprocessing
import threading
import psutil
import jsonlines
import datetime


#def facedetect(width , heigh):#
def facedetect(width , heigh, fpsArray):

    video_capture = cv2.VideoCapture(camera)
    video_capture.set(3,width)

    video_capture.set(4,heigh)
     

    font = cv2.FONT_HERSHEY_SIMPLEX
    color = (0, 255, 0)

    frames = 0
    tick = 0
    fps =0
    i=0
    
    
    
    #print("starting webcam")
    start = time.time()
   
    
    while (time.time() - start <= timeout):
    # Capture frame-by-frame
        ret, frame = video_capture.read()
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
      
        gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
        cv2.putText(frame, "FPS: {}" .format(fps), (15,80) ,font,1,color)

        faces = faceCascade.detectMultiScale(
            gray,
            scaleFactor=1.2,
            minNeighbors=5,
            minSize=(30, 30),
            flags=cv2.CASCADE_SCALE_IMAGE
        )

        # Draw a rectangle around the faces
        for (x, y, w, h) in faces:
                   # print ("x: ",x,", y: ",y)
                    prov=str(x)
                    prov = prov + 'x'
                    #ser.write(prov)
                    prov=str(y)
                    prov = prov + 'x'
                    #ser.write(prov)
                    cv2.rectangle(frame, (x, y), (x+w, y+h), (0, 255, 0), 2)

        # Display the resulting frame
        cv2.imshow('Video', frame)
        
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
    facedetect(width,height,fpsArrayshared2)
    timesnow = datetime.datetime.now().strftime('_%Y_%m_%d_%H_%M_%S')

    filename =  'result/'+ "Algofacedetection_python_"+str(width) + str(timesnow)+ '.json'
    with jsonlines.open(filename,mode='w') as outputfile:
        counter =1
        for item in fpsArrayshared2:
            result ={}
            result["algoritme"]= "Facedetection_python"
            result["fps"] = item
            result["Type"] = "Python"
            result["Second"] = counter
            result["resolution"] = width
            counter = counter +1
            outputfile.write(result)



# print("fps,"+",".join(str(x) for x in fpsArrayshared2)+ ",")
    
        
