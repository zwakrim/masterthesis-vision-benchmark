import subprocess
import time
import platform
import psutil


def cpu_info_time(time_max):
    start = time.time()
    do_or_not = False
    if time_max == 0:
        do_or_not = True
    else:
        do_or_not = False

    while time.time() - start <= time_max + 5:
        print(psutil.cpu_percent(1, 1))  # get cpu usage in %
        print(psutil.cpu_freq(percpu=True))  # get cpu frequentie in Mhz
        print(psutil.virtual_memory())
        print(psutil.swap_memory())
        if platform.system() == "Linux":
            print(psutil.sensors_temperatures())
        if do_or_not:
            break


def cpuinfo():
    print(psutil.cpu_percent(1, 1))  # get cpu usage in %
    print(psutil.cpu_freq(percpu=True))  # get cpu frequentie in Mhz
    print(psutil.virtual_memory())
    print(psutil.swap_memory())
    if platform.system() == "Linux":
        print(psutil.sensors_temperatures())


if __name__ == '__main__':
    os = platform.system()
    machine = platform.machine()
    bits = platform.architecture()[0]
    print(os)
    print(machine)
    print(bits)
    python_algorithm = open("python_algorithm.txt", "r")
    algorithm_lines = python_algorithm.readlines()
    for line in algorithm_lines:
        if line[0][0] != "#":
            cpu_info_time(1)
            p = subprocess.Popen(line, stdout=subprocess.PIPE, shell=True)
            cpu_info_time(1)
            while p.poll() is None:
                cpu_info_time(0)
            cpu_info_time(1)
            out, err = p.communicate()
            p.wait()
            print(out)
            print("end")
            time.sleep(3)
