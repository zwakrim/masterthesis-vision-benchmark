import cv2
import numpy as np
testarr=[]
def pixelcalc():
    video_capture = cv2.VideoCapture(0)
    video_capture.set(3,640)
    video_capture.set(4,480)
    while(1):
        ret, frame = video_capture.read()
        #gray= cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

        #histo =cv2.equalizeHist(gray)

        testarr=cv2.split(frame)
        #print(testarr)
        #cv2.calcHist(testarr[0],0,cv2.mat)
        #cv2.imshow('Videot', frame)
        #cv2.imshow('histo',histo)

        if cv2.waitKey(1) & 0xFF == ord('q'):
            break

    # When everything is done, release the capture
    video_capture.release()
    cv2.destroyAllWindows()
if __name__ == '__main__':

        pixelcalc()