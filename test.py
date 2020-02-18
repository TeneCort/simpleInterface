#!/usr/bin/env python3
import subprocess
import sys
import datetime
import time
import smbus

args = ''
duration = 0
bus = smbus.SMBus(1)
address = 0x12
arguments = []

# Iterates through the GET variables, fills an array with modules to activate (+100 to differenciate from the duration value)
# stocks the duration value inside another variable
for arg in sys.argv:
	if arg != sys.argv[0]:
		if arg[0] == 'm':
			if arg[-2] == '1' or arg[-2] == '2':
				arguments.append(100 + int(arg[-2] + arg[-1]));  
			else:
				arguments.append(100 + int(arg[-1]))
		else:
			arguments.append(int(arg))
 
# Opening the log file
f = open("log.txt", "w")
# Outputing initial values to send
f.write(str(arguments) + '\n')

# I2C process
for argument in arguments:
	bus.write_byte(address, argument)

	time.sleep(1)

	reponse = bus.read_byte(address)
	
	f.write("Envoi de la valeur " + str(argument) + '\n')
	f.write("la reponse de l'arduino: " + str(reponse) + '\n')

# Time calculation process
currentTime = datetime.datetime.now()

endTime = currentTime + datetime.timedelta(minutes = duration)

# Write to log. Make a function out of it? 
f.write("Started at: " + currentTime.strftime("%H:%M:%S") + '\n')
f.write("Ending at: " + endTime.strftime("%H:%M:%S") + '\n')

# Closing the log file
f.close()
