             TESTCASE  COMMISSIONING()

#1  SystemResetRequest(0); //System-RESET.request(TYPE=true: Hard Reset)

#2  SystemSetRequest(c3, 04, 00004000);//System_SET.request(Attribute = 0xc3:APS_AIB_CHANNEL_MASK, AttributeLength=0x04, 00000400 : (1L << 0x12));

#3  SystemSetRequest(6f, 08, 000000000000000a); //ExtAddr

#4  SystemSetRequest(c4, 08, bbbbbbbbbbbbbbbb); //ExtPANId

#5  SystemSetRequest(9b, 01, 01); //nwkUseMulticast

#6  SystemSetRequest(52, 01, 01); // rxOnWhenIdle

#7  SystemSetRequest(fb, 01, ff); // permitDuration = 0xff

#8  SystemSetRequest(9a, 08, bbbbbbbbbbbbbbbb); // nwkExtendedPANID

#9  SystemSetRequest(00, 01, 16); // nwkLogicalChannle = 0x16

#10 SystemSetRequest(01, 02, CCCC); // nwkPANID

#11 SystemSetRequest(96, 02, DDDD); // nwkShortAddr


END