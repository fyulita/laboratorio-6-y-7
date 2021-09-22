import serial
import os
from datetime import datetime


arduino_port = "COM3" #serial port of Arduino
baud = 9600 #arduino uno runs at 9600 baud

ser = serial.Serial(arduino_port, baud)
print(f"Connected to Arduino port {arduino_port}")

now = datetime.now()
folder_name = now.strftime('%d-%m-%Y_%H-%M-%S')

os.makedirs(f"./measurements/temp/{folder_name}")
print(f"Created folder {folder_name}")

measurement = 0 #start at 0 because our header is 0 (not real data)
while True:
    if measurement % 100 == 0:
        fileName = f"./measurements/temp/{folder_name}/data_{int(measurement / 100)}.csv"
        print(f"{fileName} created")
        file = open(fileName, "w")
        file.write("Date_Time,Temp_Compost,Temp_Suncho,Estado\n")

    data = str(ser.readline())
    now = datetime.now()
    data = now.strftime("%d/%m/%Y_%H:%M:%S") + "," + data[2:-5] + "\n"
    print(data)

    file.write(data) #write data with a newline
    measurement += 1

    if measurement % 100 == 0 and measurement != 0:
        file.close()
        print(f"{fileName} completed")
