import serial
import re
import getopt
import sys

SERIAL_TIMEOUT=5
POWER=0xc
REPEAT_COUNT=0x10

def issueCmd(s, cmd, expected):
	s.write(cmd + '\r')
	response = s.readline().strip()
	print response
	if len(response) == 0:
		raise Exception('Device not respond to command')
	if not re.match(expected, response):
		raise Exception('Unexpected device response')

def startTx(s, power, repeats):
	repS = ('%02x' % repeats).replace('0x','')
	powS = ('%02x' % power).replace('0x','')
	cmd = 'Tx'+powS+repS
	issueCmd(s, cmd, cmd+' started')

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

#open ports
sender = serial.Serial(senderCOM, 38400, timeout=SERIAL_TIMEOUT)

#issue stream of 5 packets with 3.0 dbm power
startTx(sender, POWER, REPEAT_COUNT)

#read measures
results = []
for i in xrange(REPEAT_COUNT):
	s = sender.readline().strip()
	print s
	m = re.match(r'^Tx:([-]?[\d\.]+), Rx:([-]?[\d]+)$', s)
	if m == None:
		raise Exception('Unrecognized output for measure')
	results.append((float(m.group(1)), float(m.group(2))))

#wait for 'Tx end' command
eoc = sender.readline().strip()
if eoc == None or 'Tx end' != eoc:
	raise Exception('Lack of Tx end')
print 'Measure successfully finished'

#print results
print 'Results:'
for i in results:
	print 'tx:%0.1f rx:%0.1f diff:%0.1f' % (i[0], i[1], i[0] - i[1])
diffs = map(lambda x: x[0]-x[1], results)
mean_diff = reduce(lambda x, y: x+y, diffs)/len(diffs)
print 'mean diff: %0.3f' % mean_diff
