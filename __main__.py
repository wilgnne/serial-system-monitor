import sys
import time

import psutil
import serial
import sensors

sensors.init()

def get_package_temp():
    try:
        chips = list(sensors.iter_detected_chips())
        chip = chips[0]

        features = list(chip)

        package = features[0]

        temp = package.get_value()
    except:
        temp = 0
    return temp

arduino = serial.Serial('/dev/ttyACM0', 9600, timeout=10)

buffer = ''
cont = 0

while True:
    try:
        cpu = int(psutil.cpu_percent())
        mem = int(psutil.virtual_memory().percent)

        temp = int(get_package_temp())

        buffer = f'CPU {cpu:03d}  MEM {mem:03d}TEMP {temp}'
        arduino.write(buffer.encode())
        print(buffer)
    except OSError:
        print("Write failed!")

    cont += 1
    time.sleep(1)

sensors.cleanup()
