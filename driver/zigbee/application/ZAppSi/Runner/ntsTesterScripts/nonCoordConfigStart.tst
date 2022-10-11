             TESTCASE  USB_ZC_CH_11()

#1  SystemResetRequest(0); //System-RESET.request(TYPE=true: Hard Reset)

#2  SystemSetRequest(c3, 04, 00000400);//System_SET.request(Attribute = 0xc3:APS_AIB_CHANNEL_MASK, AttributeLength=0x04, 00000400 : (1L << 0x12));

#3  SystemSetRequest(6f, 08, 0000000000000001); //ExtAddr

#4  SystemSetRequest(c4, 08, aaaaaaaaaaaaaaaa); //ExtPANId

#5  SystemStartRequest();

END
