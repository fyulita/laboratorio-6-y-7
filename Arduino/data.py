#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import serial

arduino_port = "/dev/ttyUSB0" #serial port of Arduino
baud = 9600 #arduino uno runs at 9600 baud
fileName="data.txt" #name of the CSV file generated

ser = serial.Serial(arduino_port, baud)
print("Connected to Arduino port:" + arduino_port)
file = open(fileName, "a")
print("Created file")



samples = 10 #how many samples to collect
print_labels = False
line = 0 #start at 0 because our header is 0 (not real data)
while line <= samples:
    # incoming = ser.read(9999)
    # if len(incoming) > 0:
    if print_labels:
        if line==0:
            print("Printing Column Headers")
        else:
            print("Line " + str(line) + ": writing...")
    getData=str(ser.readline())
    data=getData[0:][:-2]
    print(data)

    file = open(fileName, "a")
    file.write(data) #write data with a newline
    line = line+1

print("Data collection complete!")
file.close()