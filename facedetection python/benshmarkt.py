import json
import platform
import subprocess
import time

import psutil


def cpu_info_time(time_max= 1, array_cpu_perc=[], array_temperature= []):
    ##check if time is given
    do_or_not = False
    if time_max == 1:
        do_or_not = True
    else:
        do_or_not = False

    ##start timer
    start = time.time ()
    while time.time () - start <= time_max:
        perc=psutil.cpu_percent (1, 1) # get cpu usage in %
        print(perc)
        array_cpu_perc.append(perc)
        """ 
        print(psutil.cpu_freq (percpu=True))  # get cpu frequentie in Mhz
        print(psutil.virtual_memory ())
        print(psutil.swap_memory ())"""

        if platform.system () == "Linux":
            array_temperature.append(psutil.sensors_temperatures ())
        if do_or_not:
            break




performance ={}

if __name__ == '__main__':
    os = platform.system ()
    machine = platform.machine ()
    bits = platform.architecture ()[0]
    cores = psutil.cpu_count()
    node = platform.node()

    performance["os"]= os
    performance["machine"]=machine
    performance["bits"]=bits
    performance["cores"]= cores
    performance["node"] = node




    #those part are used to create the json file
    algo =" "
    algo_spec={}
    d_data_python={}
    d_data_windows={}
    d_data_linux={}
    d_res_python={}
    d_res_windows={}
    d_res_linux={}
    d_algo_type={}
    algo_name=""
    res = ""

    ##first do the python algorimtes

    python_algorithm = open ("python_algorithm.txt", "r")  #open file of python algoritmes
    algorithm_lines = python_algorithm.readlines () #read each line

    for line in algorithm_lines:
        if line[0][0]=="#":
            algo=line.split('#')[1]
            algo= algo.split(' ')
            algo_name=algo[0]#get the name of the algoritme

        elif line[0][0] != "#":
            spl=line.split(' ')
            if algo_name == "facedetection":
                res = spl[5] +","+ spl[6].split("\n")[0] #get the resolution of the facedection the last split is to remove \n

            cpu_temp = []
            cpu_perc = []
            cpu_info_time (5,array_cpu_perc=cpu_perc,array_temperature=cpu_temp) #begin to see what cpu does before openening process
            p = subprocess.Popen (line, stdout=subprocess.PIPE, shell=True) #opensubprocess
            while p.poll () is None:
                cpu_info_time (array_cpu_perc=cpu_perc,array_temperature=cpu_temp) #whats cpu does during subprocess
            cpu_info_time (5,array_cpu_perc=cpu_perc,array_temperature=cpu_temp) #whats cpu does after subprocess
            #out = p.stdout.readline() #print the communicaiton of the subprocess


            for line in iter(p.stdout.readline,''):
                out=line.rstrip()
                out=out.split(",")

                for data in out[1:len(out)-1]:
                    if not out[0] in d_data_python:
                        d_data_python[out[0]] = []
                    d_data_python[out[0]].append(int(data))


            p.wait () #wait untill subprosess stops


            d_data_python["cpu %"]= cpu_perc
            d_data_python["cpu temp"]=cpu_temp
            d_res_python[res]= d_data_python
            d_algo_type["python"]=d_res_python


            performance[algo_name]=d_algo_type
            jsonperf= json.dumps(performance,indent=4)
            #print(jsonperf)
            time.sleep (3)
    """
    filename = 'result/'+node+'_python_perf.json'
    saveFile= open(filename,'w')
    saveFile.write(jsonperf)
    saveFile.close()
    """
#########################################################################################################################################



    if os == "Windows":
        print("starting windows c++ algoritmes")
        windows_algorithm = open ("windows_algorithm.txt", "r")
        algorithm_lines = windows_algorithm.readlines ()
        for line in algorithm_lines:
            if line[0][0] == "#":
                algo=line.split('#')[1]
                algo= algo.split(' ')
                algo_name=algo[0]#get the name of the algoritme
            elif line[0][0] != "#":
                spl=line.split(' ')
                if algo_name == "facedetection":
                    res = spl[3] +","+ spl[4].split("\n")[0] #get the resolution of the facedection the last split is to remove \n

                cpu_perc = []
                cpu_info_time (5,array_cpu_perc=cpu_perc)
                p = subprocess.Popen (line, stdout=subprocess.PIPE, shell=True)
                cpu_info_time (1)
                while p.poll () is None:
                    cpu_info_time (array_cpu_perc=cpu_perc)
                cpu_info_time (5,array_cpu_perc=cpu_perc)

                for line in iter(p.stdout.readline,''):
                    print(line.rstrip())
                    out=line.rstrip()
                    out=out.split(",")

                    for data in out[1:len(out)-1]:
                        if not out[0] in d_data_windows:
                            d_data_windows[out[0]] = []
                        d_data_windows[out[0]].append(int(data))
            #print(d_data)
            p.wait () #wait untill subprosess stops


            d_data_windows["cpu %"]= cpu_perc
            #d_data["cpu temp"]=cpu_temp
            d_res_windows[res]= d_data_windows
            d_algo_type["Windows"]=d_res_windows


            performance[algo_name]=d_algo_type
            jsonperf= json.dumps(performance,indent=4)
            #print(jsonperf)
            time.sleep (3)

        """
        filename = 'result/'+node+'_windows_perf.json'
        saveFile= open(filename,'w')
        saveFile.write(jsonperf)
        saveFile.close()
        """


#########################################################################################################################################


    elif os == "Linux":
        print("starting Linux c++ algoritmes")
        linux_algorithm = open ("linux_algorithm.txt", "r")
        algorithm_lines = linux_algorithm.readlines ()
        for line in algorithm_lines:
            if line[0][0] == "#":
                algo=line.split('#')[1]
                algo= algo.split(' ')
                algo_name=algo[0]#get the name of the algoritme
            elif line[0][0] != "#":
                spl=line.split(' ')
                if algo_name == "facedetection":
                    res = spl[3] +","+ spl[4].split("\n")[0] #get the resolution of the facedection the last split is to remove \n

                cpu_temp = []
                cpu_perc = []
                cpu_info_time (5,array_cpu_perc=cpu_perc,array_temperature=cpu_temp) #begin to see what cpu does before openening process
                p = subprocess.Popen (line, stdout=subprocess.PIPE, shell=True) #opensubprocess
                while p.poll () is None:
                    cpu_info_time (array_cpu_perc=cpu_perc,array_temperature=cpu_temp) #whats cpu does during subprocess
                cpu_info_time (5,array_cpu_perc=cpu_perc,array_temperature=cpu_temp) #whats cpu does after subprocess
                #out = p.stdout.readline() #print the communicaiton of the subprocess


                for line in iter(p.stdout.readline,''):
                    print(line.rstrip())
                    out=line.rstrip()
                    out=out.split(",")


                    for data in out[1:len(out)-1]:
                        if not out[0] in d_data_linux:
                            d_data_linux[out[0]] = []
                        d_data_linux[out[0]].append(int(data))
                #print(d_data)
                p.wait () #wait untill subprosess stops


                d_data_linux["cpu %"]= cpu_perc
                d_data_linux["cpu temp"]=cpu_temp
                d_res_linux[res]= d_data_linux
                d_algo_type["linux"]=d_res_linux


                performance[algo_name]=d_algo_type
                jsonperf= json.dumps(performance,indent=4)
                #print(jsonperf)
                time.sleep (3)

    filename = 'result/'+node+'_'+ os+ '.json'
    saveFile= open(filename,'w')
    saveFile.write(jsonperf)
    saveFile.close()
