import smbus
import time
import sys

arg = int(sys.argv[1])
bus = smbus.SMBus(1)
address = 0x12

print("Envoi de la valeur ", arg)
bus.write_byte(address, arg)

time.sleep(1)

reponse = bus.read_byte(address)
print("la reponse de l'arduino: ", reponse)
