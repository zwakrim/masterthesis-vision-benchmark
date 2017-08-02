import subprocess
import time
import platform
import psutil


def cpuInfoTime(timeMax):
    start = time.time()
    while (time.time() - start <= timeMax + 5):
        print(psutil.cpu_percent(1, 1)) #get cpu usage in %
        print(psutil.cpu_freq(percpu=True)) #get cpu frequentie in Mhz
        print(psutil.virtual_memory())
        print(psutil.swap_memory())
        if platform.system() == "Linux":
            print(psutil.sensors_temperatures())


def cpuInfo():
        print(psutil.cpu_percent(1, 1)) #get cpu usage in %
        print(psutil.cpu_freq(percpu=True)) #get cpu frequentie in Mhz
        print(psutil.virtual_memory())
        print(psutil.swap_memory())
        if platform.system() == "Linux":
            print(psutil.sensors_temperatures())

if __name__ == '__main__':
    os = platform.system()
    machine= platform.machine()
    bits = platform.architecture()[0]
    print(os)
    print(machine)
    print(bits)
    algoritmes = open("algo.txt", "r")
    algolines = algoritmes.readlines()
    for line in algolines:
        if line[0][0] != "#":
            cpuInfoTime(0)
            p = subprocess.Popen(line, stdout=subprocess.PIPE,shell=True)
            cpuInfoTime(0)
            while (p.poll() == None):
                cpuInfo()
            cpuInfoTime(0)
            out, err = p.communicate()
            p.wait()
            print(out)
            print("end")
            time.sleep(3)