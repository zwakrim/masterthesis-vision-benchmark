import subprocess
import time
import platform
import psutil
import json


def cpu_info_time(time_max, array_cpu_perc):
    start = time.time ()
    do_or_not = False
    if time_max == 0:
        do_or_not = True
    else:
        do_or_not = False

    while time.time () - start <= time_max + 5:
        perc=psutil.cpu_percent (1, 1) # get cpu usage in %
        print(perc)
        array_cpu_perc.append(perc)
        """ 
        print(psutil.cpu_freq (percpu=True))  # get cpu frequentie in Mhz
        print(psutil.virtual_memory ())
        print(psutil.swap_memory ())"""

        if platform.system () == "Linux":
            print(psutil.sensors_temperatures ())
        if do_or_not:
            break


def cpuinfo():
    print(psutil.cpu_percent (1, 1))  # get cpu usage in %
    """ print(psutil.cpu_freq (percpu=True))  # get cpu frequentie in Mhz
    print(psutil.virtual_memory ())
    print(psutil.swap_memory ())"""
    if platform.system () == "Linux":
        print(psutil.sensors_temperatures ())

performance ={}

if __name__ == '__main__':
    os = platform.system ()
    machine = platform.machine ()
    bits = platform.architecture ()[0]
    cores = psutil.cpu_count()

    performance["os"]= os
    performance["machine"]=machine
    performance["bits"]=bits
    performance["cores"]= cores

    python_algorithm = open ("python_algorithm.txt", "r")
    algorithm_lines = python_algorithm.readlines ()
    algo =" "

    algo_spec={}
    d_data={}
    d_res={}
    d_algo_type={}
    algo_name=""
    res=""

    for line in algorithm_lines:
        if line[0][0]=="#":
            algo=line.split('#')[1]
            algo= algo.split(' ')
            algo_name=algo[0]#get the name of the algoritme

        elif line[0][0] != "#":
            spl=line.split(' ')
            if algo_name == "facedetection":
                res = spl[5] +","+ spl[6].split("\n")[0] #get the resolution of the facedection the last split is to remove \n

            cpu_perc = []
            cpu_info_time (1,cpu_perc) #begin to see what cpu does before openening process
            p = subprocess.Popen (line, stdout=subprocess.PIPE, shell=True) #opensubprocess
            while p.poll () is None:
                cpu_info_time (0,cpu_perc) #whats cpu does during subprocess
            cpu_info_time (1,cpu_perc) #whats cpu does after subprocess
            out, err = p.communicate () #print the communicaiton of the subprocess
            p.wait () #wait untill subprosess stops
            out = out.split(",")

            for data in out[1:len(out)-1]:
                if not out[0] in d_data:
                    d_data[out[0]] = []
                d_data[out[0]].append(int(data))


            d_data["cpu %"]= cpu_perc

            d_res[res]= d_data
            d_algo_type["python"]=d_res


            performance[algo_name]=d_algo_type

            print json.dumps(performance,indent=4)
            print(out)
            time.sleep (3)
    """
    if os == "Windows":
        windows_algorithm = open ("windows_algorithm.txt", "r")
        algorithm_lines = windows_algorithm.readlines ()
        for line in algorithm_lines:
            if line[0][0] != "#":
                cpu_info_time (1)
                p = subprocess.Popen (line, stdout=subprocess.PIPE, shell=True)
                cpu_info_time (1)
                while p.poll () is None:
                    cpu_info_time (0)
                cpu_info_time (1)
                out, err = p.communicate ()
                p.wait ()
                print(out)
                print("end")
                time.sleep (3)

    elif os == "Linux":
        linux_algorithm = open ("linux_algorithm.txt", "r")
        algorithm_lines = linux_algorithm.readlines ()
        for line in algorithm_lines:
            if line[0][0] != "#":
                cpu_info_time (1)
                p = subprocess.Popen (line, stdout=subprocess.PIPE, shell=True)
                cpu_info_time (1)
                while p.poll () is None:
                    cpu_info_time (0)
                cpu_info_time (1)
                out, err = p.communicate ()
                p.wait ()
                print(out)
                print("end")
                time.sleep (3)
"""
