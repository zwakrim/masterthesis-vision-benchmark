import cv2
import sys
import serial
import time
import multiprocessing
import threading
import psutil
import subprocess


def reset_to_0(the_array):
    for i, e in enumerate(the_array):
        if isinstance(e, list):
            reset_to_0(e)
        else:
            the_array[i] = 0


def cpuinfo(timeMax):
    start = time.time()
    while (time.time() - start <= timeMax + 3):
        print(psutil.cpu_percent(1, 1))


def facedetect(width, heigh, fpsArrayshared):
    video_capture = cv2.VideoCapture(camera)
    video_capture.set(3, width)
    video_capture.set(4, heigh)

    font = cv2.FONT_HERSHEY_SIMPLEX
    color = (0, 255, 0)

    frames = 0
    tick = 0
    fps = 0
    i = 0

    fpsArray = []

    print("starting webcam")
    start = time.time()

    while (time.time() - start <= timeout):
        # Capture frame-by-frame
        ret, frame = video_capture.read()
        frames = frames + 1
        end = time.time()
        seconds = end - start

        if seconds - tick >= 1:
            tick = tick + 1
            fps = frames
            fpsArrayshared[i] = fps
            i = i + 1
            frames = 0

        gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
        cv2.putText(frame, "FPS: {}".format(fps), (15, 80), font, 1, color)

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
            prov = str(x)
            prov = prov + 'x'
            # ser.write(prov)
            prov = str(y)
            prov = prov + 'x'
            # ser.write(prov)
            cv2.rectangle(frame, (x, y), (x + w, y + h), (0, 255, 0), 2)

        # Display the resulting frame
        cv2.imshow('Video', frame)

        if cv2.waitKey(1) & 0xFF == ord('q'):
            break

    # When everything is done, release the capture
    video_capture.release()
    cv2.destroyAllWindows()


cascPath = sys.argv[1]
faceCascade = cv2.CascadeClassifier(cascPath)
camera = int(sys.argv[2])
timeout = int(sys.argv[3])

if __name__ == '__main__':
    print("starting the test with camera ", camera, ", the time of each test is ", timeout)

    """
    p0=  multiprocessing.Process(target=cpuinfo)
    p00= multiprocessing.Process(target=cpuinfo)
    p000= multiprocessing.Process(target=cpuinfo)
    p0000= multiprocessing.Process(target=cpuinfo)
    """
    # global variable

    fpsArrayshared = multiprocessing.Array('i', 100)

    p1 = multiprocessing.Process(target=facedetect, args=(220, 176, fpsArrayshared))  # Hqvga half qvga
    p2 = multiprocessing.Process(target=facedetect, args=(320, 240, fpsArrayshared))  # QVGA
    p3 = multiprocessing.Process(target=facedetect, args=(640, 480, fpsArrayshared))  # VGA
    p4 = multiprocessing.Process(target=facedetect, args=(1024, 768, fpsArrayshared))  # XGA

    # first resolution
    # p0.start()
    # time.sleep(5)

    cpuinfo(0)
    p1.start()
    while (p1.is_alive()):
        cpuinfo(timeout)
    p1.join()
    print(fpsArrayshared[:])
    reset_to_0(fpsArrayshared)

    cpuinfo(0)
    p2.start()
    while (p2.is_alive()):
        cpuinfo(timeout)
    p2.join()
    print(fpsArrayshared[:])
    reset_to_0(fpsArrayshared)

    cpuinfo(0)
    p3.start()
    while (p3.is_alive()):
        cpuinfo(timeout)
    p3.join()
    print(fpsArrayshared[:])
    reset_to_0(fpsArrayshared)

    cpuinfo(0)
    p4.start()
    while (p4.is_alive()):
        cpuinfo(timeout)
    p4.join()
    print(fpsArrayshared[:])
    print("done")

    """
    p1.join()
    print("webcam finish")
    p0.join()
    print("done")
   
    #second resolution
    p00.start()
    time.sleep(5)
    print("starting webcam")
    p2.start()

   
    p2.join()
    print("webcam finish")
    p00.join()
    print("done")

    #3 resolution
    p000.start()
    time.sleep(5)
    print("starting webcam")
    p3.start()
  
   
    p3.join()
    print("webcam finish")
    p000.join()
    print("done")

    #3 resolution
    p0000.start()
    time.sleep(5)
    print("starting webcam")
    p4.start()

   
    p4.join()
    print("webcam finish")
    p0000.join()
    print("done")
   """
