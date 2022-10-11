import serial
import re
import getopt
import sys
import time

SERIAL_TIMEOUT=5

def usage():
	print """python test.py -s <transmitter comport> -p <power> -c <repeat count>
Example: transmitter connected to COM4.
	python test.py -s 4
"""

senderCOM = -1

#process arguments
try:
	opts, args = getopt.getopt(sys.argv[1:], "hr:s:p:c:", ["help"])
except getopt.GetoptError, err:
	# print help information and exit:
	print str(err) 
	usage()
	sys.exit(2)
for o, a in opts:
	if o in ("-h", "--help"):
		usage()
		sys.exit()
	elif o == "-s":
		output = senderCOM = int(a)-1
	elif o == "-p":
		POWER = int(a,0)
	elif o == "-c":
		REPEAT_COUNT = int(a,0)
	else:
		assert False, "unhandled option"

if senderCOM < 0:
	print '-s option is mandatory'
	usage()
	sys.exit(1)

def sendbuf(sender,buf):
  print 'Sent ',buf
  a=''.join(map(lambda d: chr(d),buf))
  sender.write(chr(len(a))+a)

def getbuf(sender):
  time.sleep(4)
  res=sender.inWaiting()
  print 'inwaitng=',res
  #r=sender.read(1)
  #print 'len -',ord(r)
  rr=sender.read(res)
  return [ord(i) for i in rr]
     
  

#open ports
sender = serial.Serial(senderCOM, 38400, timeout=SERIAL_TIMEOUT)
sendbuf(sender,[1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16])
sendbuf(sender,[11,12,13,14,15,16,17,18,19,20])
print 'Received-',getbuf(sender)
