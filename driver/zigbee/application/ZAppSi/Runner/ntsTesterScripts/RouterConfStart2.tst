             TESTCASE  CONFIG_START_ROUTER_2()

#1  SystemResetRequest(0); //System-RESET.request(TYPE=true: Hard Reset)

#2  SystemSetRequest(c3, 04, 00004000);//System_SET.request(Attribute = 0xc3:APS_AIB_CHANNEL_MASK, AttributeLength=0x04, 00000400 : (1L << 0x12)); 00400000

#3  SystemSetRequest(6f, 08, 0000000000000002); //ExtAddr

#4  SystemSetRequest(c4, 08, BBBBBBBBBBBBBBBB); //ExtPANId AAAAAAAAAAAAAAAA

#5  SystemSetRequest(fb, 01, ff); // permitDuration = 0xff

#6  SystemSetRequest(9b, 01, 01); //nwkUseMulticast

#7  SystemSetRequest(52, 01, 01); // rxOnWhenIdle

#8  SystemStartRequest();

END
