import serial
from time import sleep
import sys




def readCurrent(serial):
    data = serial.read(14)
    val = float(data[1:5]) #we dont care first byte cause +-
    point = data[6].encode('hex') #point byte for decimal location
    #check where is the point and adapt
    if point == "31":
        val = val / 1000
    elif point =="32":
        val = val / 100
    elif point =="34":
        val= val /10
    return val

ser = serial.Serial()
try:
    ser = serial.Serial(sys.argv[2], 2400, timeout=1)
    open = True
except:
    open = False

#http://shaddack.brutowave.com/projects/reveng_multimeters/chips/FS9922-DMM4-DS-11_EN.pdf
while True:

    if open:
        print readCurrent(ser)
    else:
        print "no port"
    sleep(1)

