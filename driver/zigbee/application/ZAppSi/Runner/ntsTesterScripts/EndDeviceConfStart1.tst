             TESTCASE  CONFIG_START_ENDDEVICE_1()

#1  SystemResetRequest(0); //System-RESET.request(TYPE=true: Hard Reset)

#2  SystemSetRequest(c3, 04, 00004000);//System_SET.request(Attribute = 0xc3:APS_AIB_CHANNEL_MASK, AttributeLength=0x04, 00000400 : (1L << 0x12));

#3  SystemSetRequest(6f, 08, 0000000000000003); //ExtAddr

#4  SystemSetRequest(c4, 08, 0000000000000000); //ExtPANId aaaaaaaaaaaaaaaa

#5  SystemSetRequest(52, 01, 00); // rxOnWhenIdle

#6  SystemSetRequest(9b, 01, 01); //nwkUseMulticast

#7  SystemStartRequest();

END
