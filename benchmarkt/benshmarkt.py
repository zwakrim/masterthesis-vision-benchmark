import json
import platform
import subprocess
import time
import jsonlines
import psutil
import sys
import datetime
import serial
from zipfile import *
import os as OS


def readCurrent(): #read value from multimeter

    try:
        if platform.system () == "Windows":
            ser = serial.Serial(sys.argv[1], 2400, timeout=1)
        else:
            ser = serial.Serial("/dev/"+sys.argv[1], 2400, timeout=1)
        data = ser.read(14)
        val = float(data[1:5]) #we dont care first byte cause +-
        point = data[6].encode('hex') #point byte for decimal location
        #check where is the point and adapt
        if point == "31":
            val = val / 1000
        elif point =="32":
            val = val / 100
        elif point =="34":
            val= val /10
        ser.close()
    except:
        #print "no serial connection with multimeter"
        val = 99999

    return val


def cpu_info_time(time_max=1, array_cpu_perc=[], array_temperature=[], algorithme="before", counter=0, resolution=0):
    """
    if time_max == 1:
        do_or_not = True
    else:
        do_or_not = False
    """

    ##start timer
    start = time.time ()
    while time.time () - start <= time_max:

        perc = psutil.cpu_percent (1, 1)  # get cpu usage in %
        perf = {}
        perf["counter"] = counter
        counter += 1
        perf["percent_cpu"] = perc
        perf["node"] = node
        perf["algoritme"] = algorithme
        perf["resulotion"] = resolution
        if algorithme is not "before" and algorithme is not "after":
            perf["algoritme"] = algorithme
        #print(perf)


        array_cpu_perc.append (perc)

        perf["Current"] = readCurrent()


        if platform.system () == "Linux":
            perf["Temp"] = psutil.sensors_temperatures ()
            array_temperature.append (psutil.sensors_temperatures ())
        perf["time"] = datetime.datetime.now().strftime('%Y-%m-%d %H:%M:%S')
        outputfile.write(perf)
        #if do_or_not:
         #   break




info = {}
counter = 0

if __name__ == '__main__':
    #check if there is a multimeter

###########################################################################################################


    os = platform.system ()
    machine = platform.machine ()
    bits = platform.architecture ()[0]
    cores = psutil.cpu_count ()
    node = platform.node ()

    info["os"] = os
    info["machine"] = machine
    info["bits"] = bits
    info["cores"] = cores
    info["node"] = node

    # time = dt.now() #to get time info
    timesnow = datetime.datetime.now ().strftime ('%Y_%m_%d_%H_%M_%S')
    filename = 'result/benchmarkt_' + node + '_' + os + '_' + str (timesnow) + '.json'


    # print info
    with jsonlines.open (filename, mode='w') as outputfile:
        outputfile.write (info)  # save at the first line the jsonformat
        # those part are used to create the json file
        algo = " "
        algo_name = ""
        res = ""

        ##first do the python algorimtes
        print("starting python algorithms")
        python_algorithm = open ("python_algorithm.txt", "r")  # open file of python algoritmes
        algorithm_lines = python_algorithm.readlines ()  # read each line
        d_algo_type = {}
        for line in algorithm_lines:
            d_data_python = {}  ##used to save correctly the data
            d_res_python = {}  ##same as above
            if line[0][0] == "#":
                algo = line.split ('#')[1]
                algo = algo.split (' ')
                algo_name = algo[1]  # get the name of the algoritme

            elif line[0][0] != "#":
                spl = line.split (' ')
                if algo[0] == "camera":
                    res = spl[5] + "," + spl[6].split ("\n")[
                        0]  # get the resolution of the facedection the last split is to remove \n
                elif algo_name == "Matrixmul":
                    res = spl[2]

                cpu_temp = []
                cpu_perc = []

                cpu_info_time (5, array_cpu_perc=cpu_perc,
                               array_temperature=cpu_temp)  # begin to see what cpu does before openening process
                # starting process
                p = subprocess.Popen (line, stdout=subprocess.PIPE, shell=True,
                                      stderr=subprocess.PIPE)  # opensubprocess

                print("starting python " + algo_name + " " + res)
                counter = 0
                while p.poll () is None:
                    if algo[0] == "camera":
                        cpu_info_time (array_cpu_perc=cpu_perc, array_temperature=cpu_temp,
                                       algorithme=algo_name + "_python", counter=counter,
                                       resolution=int (res.split (",")[0]))  # whats cpu does during subprocess
                    else:
                        cpu_info_time (array_cpu_perc=cpu_perc, array_temperature=cpu_temp,
                                       algorithme=algo_name, counter=counter)
                    counter = counter + 1
                # end of process saving whats append after

                cpu_info_time (5, array_cpu_perc=cpu_perc, array_temperature=cpu_temp,
                               algorithme="after")  # whats cpu does after subprocess



    
#########################################################################################################################################

        if os == "Windows":
            print("starting windows c++ algoritmes")
            windows_algorithm = open("windows_algorithm.txt", "r")
            algorithm_lines = windows_algorithm.readlines ()
            for line in algorithm_lines:
                d_data_windows={}
                d_res_windows={}
                if line[0][0] == "#":
                    algo=line.split('#')[1]
                    algo= algo.split(' ')
                    algo_name=algo[1]#get the name of the algoritme
                elif line[0][0] != "#":
                    spl=line.split(' ')
                    if algo[0] == "camera":
                        res = spl[3] +","+ spl[4].split("\n")[0] #get the resolution of the facedection the last split is to remove \n
                    elif algo_name =="Matrixmul":
                        print(spl[1])
                        res= spl[1]

                    cpu_perc = []
                    cpu_info_time (5, array_cpu_perc=cpu_perc,
                                   )
                    p = subprocess.Popen (line, stdout=subprocess.PIPE, shell=False,
                                          stderr=subprocess.PIPE)
                    print("starting Windows " + algo_name + " " + res)
                    counter = 0
                    while p.poll () is None:
                        if algo[0] == "camera":
                            cpu_info_time (array_cpu_perc=cpu_perc,
                                           algorithme=algo_name + "_windows", counter=counter,
                                           resolution=int(res.split (",")[0]))  # whats cpu does during subprocess
                        else:
                            cpu_info_time (array_cpu_perc=cpu_perc, array_temperature=cpu_temp,
                                           algorithme=algo_name, counter=counter)
                    counter = counter + 1

                    cpu_info_time (5, array_cpu_perc=cpu_perc,
                                   algorithme="after")
                    filenameOutput =  'result/'+ algo_name + "_Windows_" +str(spl[3])+"_" + str(timesnow)+ '.json'

                    with jsonlines.open(filenameOutput,mode='w') as outputfileRes:
                        for line in iter(p.stdout.readline,''):
                            out=line.strip()
                            out=out.split(",")
                            counter = 1
                            for data in out[2:len(out)-1]:
                                if out[0] == "fps":
                                    result ={}
                                    result["algoritme"]= algo_name + "_Windows"
                                    result["fps"] = data
                                    result["Type"] = "windows"
                                    result["Second"] = counter
                                    result["resolution"] = spl[3]
                                    counter = counter +1
                                    outputfileRes.write(result)

            #########################################################################################################################################

        elif os == "Linux":
            print("starting Linux c++ algoritmes")
            d_algo_type={}
            linux_algorithm = open ("linux_algorithm.txt", "r")
            algorithm_lines = linux_algorithm.readlines ()
            for line in algorithm_lines:
                d_data_linux={}
                d_res_linux={}


                if line[0][0] == "#":
                    algo=line.split('#')[1]
                    algo= algo.split(' ')
                    algo_name=algo[0]#get the name of the algoritme

                elif line[0][0] != "#":
                    spl=line.split(' ')
                    if algo_name == "camera":
                        res = spl[3] +","+ spl[4].split("\n")[0] #get the resolution of the facedection the last split is to remove \n

                    cpu_temp = []
                    cpu_perc = []
                    cpu_info_time (5,array_cpu_perc=cpu_perc,array_temperature=cpu_temp) #begin to see what cpu does before openening process
                    p = subprocess.Popen (line, stdout=subprocess.PIPE, shell=True) #opensubprocess

                    counter = 0
                    print("starting c++ " + algo_name + " " + res)

                    while p.poll () is None:
                        if algo[0] == "camera":
                            cpu_info_time (array_cpu_perc=cpu_perc,
                                           algorithme=algo_name + "_Linux", counter=counter,
                                           resolution=int(res.split (",")[0]))  # whats cpu does during subprocess
                        else:
                            cpu_info_time (array_cpu_perc=cpu_perc, array_temperature=cpu_temp,
                                           algorithme=algo_name, counter=counter)
                    counter = counter + 1

                    #cpu_info_time (5,array_cpu_perc=cpu_perc,array_temperature=cpu_temp) #whats cpu does after subprocess
                    #out = p.stdout.readline() #print the communicaiton of the subprocess
                    cpu_info_time (5, array_cpu_perc=cpu_perc,
                                   algorithme="after")
                    filenameOutput =  'result/'+ algo_name + "_Linux_" +str(spl[3])+"_" + str(timesnow)+ '.json'

                    with jsonlines.open(filenameOutput,mode='w') as outputfileRes:
                        for line in iter(p.stdout.readline,''):
                            out=line.strip()
                            out=out.split(",")
                            counter = 1
                            for data in out[2:len(out)-1]:
                                if out[0] == "fps":
                                    result ={}
                                    result["algoritme"]= algo_name + "_Linux"
                                    result["fps"] = data
                                    result["Type"] = "linux"
                                    result["Second"] = counter
                                    result["resolution"] = spl[3]
                                    counter = counter +1
                                    outputfileRes.write(result)


lsfile = OS.listdir("./result")
zip_archive = ZipFile("./result/benchmarket_" +str(machine)+"_" + str(node)+ "_"+ str (timesnow) + ".zip","w")
print("zipping files")
for f in lsfile:
    file = './result/' + f
    ext = OS.path.splitext(file)[-1].lower()
    if ext == ".json":
        zip_archive.write(file)
        OS.remove(file)

zip_archive.close()
print("benchmarkt done")


    # calling function to get all file paths in the directory






