import sys
import os
import time
import Queue
import serial
import threading

#-----------------------------------------------------------------------------
GW_COM_PORT   = 'COM16'
BAUDRATE      = 115200
MAX_OTAU_CHILD_DEVICES = 1

deviceA_OTAU_File = 'OTAPackage.zigbee'
# deviceA_OTAU_File = 'TestFreeRtos_Enc_def_Key.zigbee'
# deviceB_OTAU_File = '1149-0001-000001F6-light_v2.zigbee'
# deviceC_OTAU_File = '1149-0001-000001F6-light_v2.zigbee'

#-----------------------------------------------------------------------------
SOF = 0x2A 

#ISD Command IDs
ISD_ZCL_COMMAND_INDICATION             = 0x0046
ISD_ZCL_COMMAND_REQUEST_MSB            = 0x44 
ISD_ZCL_COMMAND_REQUEST_LSB            = 0x00
ISD_DRIVER_INIT_REQUEST                = 0x0100
ISD_DRIVER_PRINT_REQUEST               = 0x0200
ISD_DRIVER_INIT_RESPONSE               = [01,01]
ISD_INIT_MARKER                        = [0x55]

#OTA Req/Cmds IDs
IMAGE_NOTIFY_CMD                       = 0x00
QUERY_NEXT_IMAGE_REQ_CMD               = 0x01
QUERY_NEXT_IMAGE_RESP_CMD              = [0x02]
IMAGE_BLOCK_REQ_CMD                    = 0x03
IMAGE_PAGE_REQ_CMD                     = 0x04
IMAGE_BLOCK_RESP_CMD                   = [0x05]
UPGRADE_END_REQ_CMD                    = 0x06
UPGRADE_END_RESP_CMD                   = [0x07]
DEFAULT_RESP_CMD                       = 0x0B

#Status values
ZCL_SUCCESS_STATUS                     = 0x00
MALFORMED_STATUS                       = 0x80

# Config params
MAX_OTAU_BLOCK_SIZE                    = 48

#-----------------------------------------------------------------------------
def uint8(num):
  return [num & 0xff]

#-----------------------------------------------------------------------------
def uint16(num):
  if isinstance(num, list):
    assert(len(num) == 2)
    return (num[1] << 8) | num[0]
  else:
    return [num & 0xff, (num >> 8) & 0xff]

#-----------------------------------------------------------------------------
def uint32(num):
  if isinstance(num, list):
    assert(len(num) == 4)
    return (num[3] << 24) | (num[2] << 16) | (num[1] << 8) | num[0]
  else:
    return [num & 0xff, (num >> 8) & 0xff, (num >> 16) & 0xff, (num >> 24) & 0xff]

#-----------------------------------------------------------------------------
def uint64(num):
  if isinstance(num,list):
    assert(len(num) == 8)
    return long((num[7] << 56) | (num[6] << 48) | (num[5] << 40) | (num[4] << 32)| 
    (num[3] << 24) | (num[2] << 16) | (num[1] << 8) | num[0])
  else:  
    return [num & 0xff, (num >> 8) & 0xff, (num >> 16) & 0xff, (num >> 24) & 0xff, 
      (num >> 32) & 0xff, (num >> 40) & 0xff, (num >> 48) & 0xff, (num >> 56) & 0xff]

#-----------------------------------------------------------------------------
def check_count(cmd, num):
  if len(cmd) != num + 1:
    print ("Command expects %d parameter(s)" % num)
    return True
  return False

#-----------------------------------------------------------------------------
class Struct:
  def __str__(self):
    excl = ['__doc__', '__module__', '__repr__', '__str__', '__getitem__']
    lst = [i for i in dir(self) if i not in excl]
    return ', '.join(['%s=0x%x' % (l, eval('self.%s' % l)) for l in lst])
  
  def __repr__(self):
    return self.___str___()

  def __getitem__(self, item):
    return item in dir(self)

#-----------------------------------------------------------------------------
class COMConnection:
  #------------------------------------
  def __init__(self, address, baud):
    self.address = address
    self.baud = baud
    self.port = serial.Serial(address, baud, timeout=0.5)

  #------------------------------------
  def close(self):
    self.port.close()

  #------------------------------------
  def write(self, data):
    #print 'WR %-2d: %s %s' % (len(data), to_hex(data[0:30]), '...' if len(data) > 30 else '')
    self.port.write(''.join(map(chr, data)))

  #------------------------------------
  def write_console(self, data):
    self.port.write(data)
  def read(self, size):
    return map(ord, self.port.read(size))

  #------------------------------------
  def flush(self):
    self.port.flushInput()

#-----------------------------------------------------------------------------
def to_hex(data):
  return ' '.join(['%02x' % d for d in data])
 
#-----------------------------------------------------------------------------
class Main:
  #------------------------------------
  def __init__(self, conn):
    self.conn = conn

    self.stop = threading.Event()

    self.wait = threading.Event()
    self.wait.clear()

    self.handle = 0
    self.start_time = time.time()
    self.ota_file = []

    self.ota_file.append(map(ord, open(deviceA_OTAU_File, 'rb').read()))
    # self.ota_file.append(map(ord, open(deviceB_OTAU_File, 'rb').read()))
    # self.ota_file.append(map(ord, open(deviceC_OTAU_File, 'rb').read()))
    self.ota_active = False
    self.delay_set = False
	
    self.console_command_process = 0
    self.cmd_resp = ""
    self.attrValue = 0xFF
    self.count = 0
    self.otaBaudRate = 10
    self.currOffset = 0
    
    self.deviceList = []
    for deviceIndex in range(MAX_OTAU_CHILD_DEVICES):
      self.deviceList.append(0)
    self.comm_thread = threading.Thread(target=self.receive_thread_handler)
    self.comm_thread.daemon = True
    self.comm_thread.start()

    self.ui_thread = threading.Thread(target=self.ui_thread_handler)
    self.ui_thread.daemon = True
    self.ui_thread.start()
    
    self.baudRate_thread = threading.Thread(target=self.baudRate_thread_handler)
    self.baudRate_thread.daemon = True
    self.baudRate_thread.start()

  #------------------------------------
  def run(self):
    self.comm_thread.join()
    self.ui_thread.join()
    self.baudRate_thread.join()

  #------------------------------------
  def time(self):
    return time.time() - self.start_time

  #------------------------------------
  def send_init_resp(self):
    payload = []
    payload = ISD_DRIVER_INIT_RESPONSE
    payload += ISD_INIT_MARKER 
    self.sendCommand(payload)
  #------------------------------------  
  def readAttribute(self,addrMode,addr,ep,clusterId,attrId):
    payload = "readAttribute"
    payload += " "
    payload += str(addrMode)
    payload += " "
    payload += str(addr)
    payload += " "
    payload += str(ep)
    payload += " "
    payload += str(clusterId)
    payload += " "
    payload += str(attrId)
    payload += "\r\n"
    #print payload
    self.conn.write_console(payload)
    self.console_command_process = 1
    return
  #------------------------------------
  def process_response(self,str):    
    self.attrResponse = 1
    print (str)
  
  #------------------------------------
  def parse_payload(self,data):
    payload = Struct()
    payload.srcAddrMode     = data[0]
    payload.srcShortAddress = uint16(data[1:3])
    payload.srcExtAddress   = uint64(data[3:11])
    payload.srcProfileId    = uint16(data[11:13])
    payload.srcEndpointId   = data[13]
    payload.srcClusterId    = uint16(data[14:16])
    payload.clusterId       = uint16(data[16:18])
    payload.direction       = data[18]
    payload.commandId       = data[19]
    payload.reqfields       = data[20:]
    return payload
  
  #------------------------------------
  def print_payload(self,payload):
    print ("Payload:"                                         )
    print ('srcAddrMode %02x' % payload.srcAddrMode           )
    print ('srcShortAddress %02x' % payload.srcShortAddress   )
    print ('srcExtAddress %02x' % payload.srcExtAddress       )
    print ('srcProfileId %02x' % payload.srcProfileId         )
    print ('srcEndpointId %02x' % payload.srcEndpointId       )
    print ('srcClusterId %02x' % payload.srcClusterId         )
    print ('clusterId %02x' % payload.clusterId               )
    print ('direction %02x' % payload.direction               )
    print ('commandId %02x' % payload.commandId               )
    print ('reqfields:'                                       )
    print (payload.reqfields                                  )
    return
    
    #------------------------------------
  def prepare_payload_header(self,payload_hdr,cmdid):
    hdr =  uint8(ISD_ZCL_COMMAND_REQUEST_MSB)
    hdr += uint8(ISD_ZCL_COMMAND_REQUEST_LSB)
    hdr += uint8(payload_hdr.srcAddrMode)     
    hdr += uint16(payload_hdr.srcShortAddress) 
    hdr += uint64(payload_hdr.srcExtAddress) 
    hdr += uint16(payload_hdr.srcProfileId) 
    hdr += uint8(payload_hdr.srcEndpointId) 
    hdr += uint8(payload_hdr.srcEndpointId) 
    hdr += uint16(payload_hdr.clusterId) 
    hdr += uint8(0) #defaultResp 
    hdr += uint8(0) #ISDControlFields
    hdr += cmdid
    return hdr  
    
  #------------------------------------
  def handle_query_next_image_req(self, data):
    deviceAvailable = False
    #check whether the address is already in list
    for deviceIndex in range(MAX_OTAU_CHILD_DEVICES):
      if self.deviceList[deviceIndex] == data.srcShortAddress:
        deviceAvailable = True
        break

    if deviceAvailable == False:
      for deviceIndex in range(MAX_OTAU_CHILD_DEVICES):
        if self.deviceList[deviceIndex] == 0:
          self.deviceList[deviceIndex] = data.srcShortAddress
          print ('Device Added: 0x%02x' % (data.srcShortAddress))
          break

    req = Struct()
    req.controlField = data.reqfields[0]
    req.manufacturerId = uint16(data.reqfields[1:3])
    req.imageType = uint16(data.reqfields[3:5])
    req.firmwareVersion = uint32(data.reqfields[5:9])
    self.send_query_next_image_resp(data, req)

  #------------------------------------
  def send_query_next_image_resp(self, payload_hdr, req):
    payload = self.prepare_payload_header(payload_hdr,QUERY_NEXT_IMAGE_RESP_CMD)
    if self.ota_active:
      payload += uint8(0) # status
      payload += uint16(req.manufacturerId) # manufacturerId
      payload += uint16(req.imageType) # imageType
      payload += uint32(req.firmwareVersion + 1) # firmwareVersion
      for deviceIndex in range(MAX_OTAU_CHILD_DEVICES):
        if payload_hdr.srcShortAddress == self.deviceList[deviceIndex]:
          payload += uint32(len(self.ota_file[deviceIndex])) # imageSize
          break
      self.delay_set = True #False
      self.startTime = time.time()
    else:
      payload += uint8(0x98) # status
    
    #print '[{}]'.format(', '.join(hex(x) for x in payload))
    self.sendCommand(payload)

  #------------------------------------
  def handle_image_block_req(self, data):
    req = Struct()
    req.controlField = data.reqfields[0]
    req.manufacturerId = uint16(data.reqfields[1:3])
    req.imageType = uint16(data.reqfields[3:5])
    req.firmwareVersion = uint32(data.reqfields[5:9])
    req.fileOffset = uint32(data.reqfields[9:13])
    req.maxDataSize = data.reqfields[13]
    
    #if req.controlField & 1: # reqNodeIeeeAddrPresent
    #  req.fileOffset = uint64(data.reqfields[14:22])
    self.currOffset = req.fileOffset
    if req.controlField & 2: # blockRequestDelayPresent
      req.blockRequestDelay = uint16(data.reqfields[14:16])

    self.send_image_block_resp(data, req)
  #------------------------------------
  def send_image_block_resp(self, payload_hdr, blReq):
    payload = self.prepare_payload_header(payload_hdr,IMAGE_BLOCK_RESP_CMD)
     
    size = blReq.maxDataSize

    if self.delay_set:
      payload += uint8(0) # status
      payload += uint16(blReq.manufacturerId) # manufacturerId
      payload += uint16(blReq.imageType) # imageType
      payload += uint32(blReq.firmwareVersion) # firmwareVersion
      payload += uint32(blReq.fileOffset) # fileOffset
      payload += uint8(size) # dataSize
      # payload += self.ota_file[blReq.fileOffset:blReq.fileOffset+size] # imageData
      for deviceIndex in range(MAX_OTAU_CHILD_DEVICES):
        if payload_hdr.srcShortAddress == self.deviceList[deviceIndex]:
          payload += self.ota_file[deviceIndex][blReq.fileOffset:blReq.fileOffset+size] # imageData
          filesize = (len(self.ota_file[deviceIndex]))
          break
      # print 'Block Resp Offset 0x%04x:%d Size %d' % (blReq.fileOffset,blReq.fileOffset,size)
      
      offset = (blReq.fileOffset)
      ota_progress = ((offset * 1.0)/filesize)
      self.update_ota_progress(ota_progress)
    else:
      self.delay_set = True
      payload += uint8(0x97) # ZCL_WAIT_FOR_DATA_STATUS
      payload += uint32(0) # currentTime
      payload += uint32(0) # requestTime
      payload += uint16(50) # blockRequestDelay

    self.sendCommand(payload)
      
  #------------------------------------
  def handle_upgrade_end_req(self, data):
    req = Struct()
    req.controlField = data.reqfields[0]
    req.manufacturerId = uint16(data.reqfields[1:3])
    req.imageType = uint16(data.reqfields[3:5])
    req.firmwareVersion = uint32(data.reqfields[5:9])
    self.endTime = time.time()
    if data.reqfields[0] == ZCL_SUCCESS_STATUS:
        self.update_ota_progress(1)
    print ('\r\nTotal Upgrade Time %d:%d' % (((self.endTime - self.startTime) / 60), ((self.endTime - self.startTime) % 60)))
    self.send_upgrade_end_resp(data, req)

  #------------------------------------
  def send_upgrade_end_resp(self, payload_hdr, req):
    payload = self.prepare_payload_header(payload_hdr,UPGRADE_END_RESP_CMD)

    payload += uint16(req.manufacturerId) # manufacturerId
    payload += uint16(req.imageType) # imageType
    payload += uint32(req.firmwareVersion) # firmwareVersion
    payload += uint32(1000) # currentTime
    payload += uint32(1005) # upgradeTime

    self.ota_active = False
    self.sendCommand(payload)

  #------------------------------------
 
  def sendCommand(self, data=[]):
    #print '%4.2f   TX %-2d: %s %s' % (self.time(), len(data), to_hex(data[0:30]), '...' if len(data) > 30 else '')
    payload = [SOF, len(data), 0] + data #adding extra 0 after length as the firmware expects length to be uint16
    self.conn.write(payload)
  
  #------------------------------------
  def process(self, data):
    # print '%4.2f   RX %-2d: %s %s' % (self.time(), len(data), to_hex(data[0:30]), '...' if len(data) > 30 else '')
    cmdid = (data[1] << 8) | data[0]
    if(cmdid == ISD_DRIVER_INIT_REQUEST):
      self.send_init_resp()
      print ('ISD Initialized')
      return

    if(cmdid == ISD_DRIVER_PRINT_REQUEST):
      self.send_init_resp()
      newData = []
      for eachData in data:
        newData.append(chr(eachData))
      printData = newData[2:]
      stringData = ""
      for eachData in printData:
        stringData = stringData + eachData
      # print 'ISD Print data : ', stringData
      print (stringData)
      return

    payload = self.parse_payload(data[2:])
    self.deviceAddress = payload.srcShortAddress
    #self.print_payload(payload)

    dispatch = {
      (ISD_ZCL_COMMAND_INDICATION, QUERY_NEXT_IMAGE_REQ_CMD): self.handle_query_next_image_req,
      (ISD_ZCL_COMMAND_INDICATION, IMAGE_BLOCK_REQ_CMD): self.handle_image_block_req,
      (ISD_ZCL_COMMAND_INDICATION, UPGRADE_END_REQ_CMD): self.handle_upgrade_end_req,
    }
     
    parse_fields = [cmdid,payload.commandId]
    if tuple(parse_fields) in dispatch:
      dispatch[tuple(parse_fields)](payload)

  #------------------------------------
  def print_menu(self):
    print ('-' * 30                                            )
    print ("Commands:"                                         )
    print ('1. ota <b>  ,where b is 1 for Start or 0 for Stop' )
    print ('2. q / quit'                                       )
    print ('-' * 30                                            )
    print ('> ',                                               )

  #------------------------------------
  def ui_thread_handler(self):
    self.print_menu()
    while True:
      cmd = raw_input().strip().split()

      if len(cmd) == 0:
        self.print_menu()
        continue

      if cmd[0] in ['q', 'quit']:
        print ('quitting')
        self.stop.set()
        os._exit(1)
        break

     
      elif cmd[0] == 'ota':
        if check_count(cmd, 1):
          continue

        if eval(cmd[1]) == 0:
          self.ota_active = False
          continue

        self.ota_active = True

      else:
        print ('Unknown Command: %s' % cmd)

  #------------------------------------
  def receive_thread_handler(self):
    STATE_IDLE      = 0
    STATE_SIZE_LSB  = 1
    STATE_SIZE_MSB  = 2
    STATE_DATA      = 3
    STATE_0         = 5
    STATE_1         = 4
    STATE_2         = 6
    STATE_3         = 7
    STATE_4         = 8
    
    state = STATE_IDLE
    state_c = STATE_0
    while not self.stop.isSet():
      d = self.conn.read(1)
      if len(d) == 0:
        continue

      byte = d[0]
      # if byte == '\r':
        # print '\r\n'
      # else:
        # print '%c'%byte,

      if self.console_command_process:
        if state_c == STATE_0:
          if chr(byte) == 'Z':
            state_c = STATE_1

        elif state_c == STATE_1:
           if chr(byte) == 'c':
            state_c = STATE_2

        elif state_c == STATE_2:
          if chr(byte) =='l':
            state_c = STATE_3
            readStr = 'Zcl'

        elif state_c == STATE_3:
          if chr(byte) != '\n':
            readStr += chr(byte)
          else:
            state_c = STATE_4

        elif state_c == STATE_4:
          if chr(byte) != '\n':
            readStr += chr(byte)
          else:
            self.process_response(readStr)
            state_c = STATE_0 
            self.console_command_process = 0

      else:
        if state == STATE_IDLE:
          if byte == SOF:
              state = STATE_SIZE_LSB
              c_data = []
            
        elif state == STATE_SIZE_LSB:
          c_size = byte #Read LSB of length
          state = STATE_SIZE_MSB   
          
        elif state == STATE_SIZE_MSB:
          c_size |= (byte << 8) # Total length
          #print 'Size %02x' % c_size
          state = STATE_DATA   
          
        elif state == STATE_DATA:
          c_data += [byte]
          c_size -= 1
          if c_size == 0:
            self.process(c_data)
            state = STATE_IDLE  
#------------------------------------------------------------------------------
  def update_ota_progress(self,ota_progress):
    barLength = 50 # Modify this to change the length of the progress bar
    status = ""
    if isinstance(ota_progress, int):
        ota_progress = float(ota_progress)
    if not isinstance(ota_progress, float):
        ota_progress = 0
        status = "error: ota_progress var must be float\r\n"
    if ota_progress < 0:
        ota_progress = 0
        status = "Halt...\r\n"
    if ota_progress >= 1:
        ota_progress = 1
        status = "Done...\r\n"
    block = 1 + int(round(barLength * ota_progress))
    text = "\rDownloading: [{0}] {1:.2f}% {2}".format( "="*block + " "*(barLength-block), ota_progress*100, status)
    sys.stdout.write(text)
    sys.stdout.flush()

#------------------------------------------------------------------------------
  def baudRate_thread_handler(self):
    while True:
      while self.ota_active:
        self.prevOffset = self.currOffset
        time.sleep(1)
        self.otaBaudRate = self.currOffset - self.prevOffset
      time.sleep(1)

#------------------------------------------------------------------------------
def main():
  try:
    conn = COMConnection(GW_COM_PORT, BAUDRATE)
    m = Main(conn)
    m.run()
    conn.close()
  except IOError as e:
    print (e)
    print ("I/O error({0}): {1}".format(e.errno, e.strerror))
  print ('quitting')
  os._exit(1)
    

#-----------------------------------------------------------------------------
main()
