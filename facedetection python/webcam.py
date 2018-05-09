import cv2
import sys
import serial
import time

# Create an object Serial with ttymxc3 port
#ser = serial.Serial(
 #   port='/dev/ttymxc3',
#    baudrate=115200,
 #   parity=serial.PARITY_ODD, # Optional
 #   stopbits=serial.STOPBITS_ONE, # Optional
#    bytesize=serial.EIGHTBITS # Optional
#)
# Check if Serial is Open, close it then re-open (to avoid exception)
#if ser.isOpen():
#    ser.close()
#ser.open()

cascPath = sys.argv[1]
camera = int(sys.argv[2])
faceCascade = cv2.CascadeClassifier(cascPath)

print("hello arg camera is ",camera)
# Set video source (UDOO Camera) and resolution
video_capture = cv2.VideoCapture(camera)
video_capture.set(3,640)
video_capture.set(4,480)


font = cv2.FONT_HERSHEY_SIMPLEX
color = (0, 255, 0)

frames = 0
tick = 0
fps =0
start = time.time()
timeout = 60.0

while (time.time() - start <= 60):
    # Capture frame-by-frame
    ret, frame = video_capture.read()
    frames = frames +1
    end = time.time()
    seconds = end- start 	
   
    if seconds-tick >= 1:
      tick = tick + 1
      fps = frames
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
		#print ("x: ",x,", y: ",y)
		prov=str(x)
		prov = prov + 'x'
		#ser.write(prov)
		print(prov)
		prov=str(y)
		prov = prov + 'y'
		#ser.write(prov)
		print(prov)
		cv2.rectangle(frame, (x, y), (x+w, y+h), (0, 255, 0), 2)

    # Display the resulting frame
    cv2.imshow('Video', frame)
    
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break
 
# When everything is done, release the capture
video_capture.release()
cv2.destroyAllWindows()
