import serial
ser = serial.Serial('/dev/<NAME_OF_TEENSY_PORT_HERE>', timeout=1)
print(ser.name)
line = ser.readline();
print(line)