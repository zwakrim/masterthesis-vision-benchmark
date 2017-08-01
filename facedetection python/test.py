import subprocess
import time
import platform
import psutil


def cpuinfo(timeMax):
    start = time.time()
    while (time.time() - start <= timeMax + 5):
        print(psutil.cpu_percent(1, 1))


if __name__ == '__main__':
    os = platform.system()
    print(os)
    algoritmes = open("algo.txt", "r")
    algolines = algoritmes.readlines()
    for line in algolines:
        if line[0][0] != "#":
            cpuinfo(0)
            p = subprocess.Popen(line, stdout=subprocess.PIPE)
            cpuinfo(0)
            while (p.poll() == None):
                print(psutil.cpu_percent(1, 1))
            cpuinfo(0)
            out, err = p.communicate()
            p.wait()
            print(out)
            print("end")
            time.sleep(3)
