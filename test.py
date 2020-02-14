#!/usr/bin/env python3
import subprocess
import sys
import time

for arg in sys.argv:
	if arg != sys.argv[0]:
		print(arg + '\n')

arg = sys.argv[1]

subprocess.Popen('lxterminal --command="print "' + arg, shell=True)
