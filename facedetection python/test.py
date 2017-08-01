import cv2
import sys
import serial
import time
import multiprocessing
import threading
import psutil
import subprocess 

if __name__ == '__main__':
    
   
    subprocess.Popen("python facedectMultiProcessing.py haarcascade_frontalface_default.xml 0 10")
