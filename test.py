#!/usr/bin/env python3
import subprocess
import sys

for arg in sys.argv:
	if arg != sys.argv[0]:
		print(arg + '\n')

arg = 'hello'

subprocess.Popen('lxterminal --command="yes "' + arg, shell=True)


