"""
@testcase
@description Certification test implementation (ESP part) 
  
@tags
  
@configuration

@connection port2 = coordinator, COM:COM69
"""
import time


tasks=[]
port2.setTimeout(1000)
while 1:
  res=port2.receive()
  if res != None:
    #print res
    pass
print("SUCCESS")
