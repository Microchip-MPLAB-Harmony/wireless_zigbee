/* Crypto related Configuration Options */
#undef NO_SHA256
#define HAVE_ECC
#define WOLFSSL_HAVE_MCHP_HW_ECC
#define HAVE_CURVE25519
#define TFM_TIMING_RESISTANT
#define ECC_TIMING_RESISTANT
#define WC_RSA_BLINDING
#define FREERTOS
#undef NO_ASN
#define HAVE_ECC_DHE
#define HAVE_ECC_SIGN
#define HAVE_ECC_VERIFY
#undef WC_NO_RNG
#define CUSTOM_RAND_GENERATE_BLOCK  SYS_GetRandomSequence
extern int SYS_GetRandomSequence(uint8_t *buffer, unsigned long size);
