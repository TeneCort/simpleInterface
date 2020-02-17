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
# Arguments provided, needs rework
for arg in sys.argv:
	if arg != sys.argv[0]:
		if arg[0] == 'm':
			args += arg + ' '
		else:
			duration = int(arg)
 
#subprocess.Popen('lxterminal --command="yes "' + arg, shell=True)

#output = subprocess.check_output(['ls', '-1'])

# I2C process
bus.write_byte(address, duration)

time.sleep(1)

reponse = bus.read_byte(address)

# Time process
currentTime = datetime.datetime.now()

endTime = currentTime + datetime.timedelta(minutes = duration)

# Write to log
f = open("log.txt", "w")
f.write(str(args) + '\n')
f.write(str(duration) + '\n')
f.write("Started at: " + currentTime.strftime("%H:%M:%S") + '\n')
f.write("Ending at: " + endTime.strftime("%H:%M:%S") + '\n')
f.write("Envoi de la valeur " + str(duration) + '\n')
f.write("la reponse de l'arduino: " + str(reponse))
f.close()

