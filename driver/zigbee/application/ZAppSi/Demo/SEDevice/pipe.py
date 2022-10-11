import serial
import sys
import os
sender = serial.Serial(sys.argv[1], 38400, timeout=5)
stdin,stdout=os.popen2(sys.argv[2],'b')
while 1:
  buf=''
  k=stdout.read(1);
  size=ord(k)
  print 'size - ', size
  for i in range(size):
    k+=stdout.read(1)
  sender.write(k)
  print 'cmd -',[hex(ord(i)) for i in k]
exit(0)
#open ports
sendbuf(sender,[1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16])
sendbuf(sender,[11,12,13,14,15,16,17,18,19,20])
print 'Received-',getbuf(sender)

