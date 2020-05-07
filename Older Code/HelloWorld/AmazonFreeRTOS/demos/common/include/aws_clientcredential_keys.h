#ifndef AWS_CLIENT_CREDENTIAL_KEYS_H
#define AWS_CLIENT_CREDENTIAL_KEYS_H

#include <stdint.h>

/*
 * PEM-encoded client certificate.
 *
 * Must include the PEM header and footer:
 * "-----BEGIN CERTIFICATE-----\n"\
 * "...base64 data...\n"\
 * "-----END CERTIFICATE-----"
 */
#define keyCLIENT_CERTIFICATE_PEM \
"-----BEGIN CERTIFICATE-----\n"\
"MIIDWTCCAkGgAwIBAgIUe5+OZx83BedmaBUhbwhr0HZoqVUwDQYJKoZIhvcNAQEL\n"\
"BQAwTTFLMEkGA1UECwxCQW1hem9uIFdlYiBTZXJ2aWNlcyBPPUFtYXpvbi5jb20g\n"\
"SW5jLiBMPVNlYXR0bGUgU1Q9V2FzaGluZ3RvbiBDPVVTMB4XDTIwMDIyNTA2MzQy\n"\
"MloXDTQ5MTIzMTIzNTk1OVowHjEcMBoGA1UEAwwTQVdTIElvVCBDZXJ0aWZpY2F0\n"\
"ZTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBALC74Qi4qSOwlr0SybbQ\n"\
"oJOscy7XXEDLD3yijqCMqHS51lueIA2r6lXApm++UFPeNf4epCoT31V6NfQdKhnc\n"\
"Z9jExPbKCGS66TAZ6clLivdQeRrDcytNjetWvU5mPUBegQYcskSrnYPvDcdw0zI2\n"\
"vwFrAw5tcQ/5qGgAYwS+mpy7bqEzG86CgiEZWXpA0VsG+4WuFEN+BGWCCMXKo0zC\n"\
"tTHGO1w6WVmbGU7nbNec/DfOPT0KFdZe6e+ZsYhVTohsMpq5CQ7pZqV1hRx/jQyW\n"\
"kT0Dizo2e9FkR27eQO9+F2al+G8kkUVRE/4kX1tZqAGUyLXxRucg3oXfdZitZAWV\n"\
"O40CAwEAAaNgMF4wHwYDVR0jBBgwFoAUB/jFii7C8yBCReruOngV40z+qowwHQYD\n"\
"VR0OBBYEFE4K0CDan9Ru2pIYK0+NMbt57S3DMAwGA1UdEwEB/wQCMAAwDgYDVR0P\n"\
"AQH/BAQDAgeAMA0GCSqGSIb3DQEBCwUAA4IBAQAcTidEtD7iw7CASVow624CUDtO\n"\
"u9qQr08+75mOfS5s8t6DaEmzGYqkLizzdb2G87I6/uXw9PkDg/OMMs+RSlqObs4T\n"\
"/rwOrghNVW22WicY7I1eQlrUEuidLiUP+eAkZfCsspAn/HhE19E5CTWgo6mL/6jn\n"\
"fX+9YALiUTdydULVNBC2jreHmT4WmVP3BG7gpESxyiD4ifgCtkhgjwnSvGqSZYkV\n"\
"CTahf6yGa73IP+9Ht7y5GJnLKu+P3HFkPasIo3clUMucaebDAXOwcI6BNj5zhlTy\n"\
"gc2Yd/PhZhy09+7jWfm9IyrkgSaaUyazHDXuzCkKhNI8T6xMwBI7N2s68QFZ\n"\
"-----END CERTIFICATE-----"

/*
 * PEM-encoded client private key.
 *
 * Must include the PEM header and footer:
 * "-----BEGIN RSA PRIVATE KEY-----\n"\
 * "...base64 data...\n"\
 * "-----END RSA PRIVATE KEY-----"
 */
#define keyCLIENT_PRIVATE_KEY_PEM \
"-----BEGIN RSA PRIVATE KEY-----\n"\
"MIIEpQIBAAKCAQEAsLvhCLipI7CWvRLJttCgk6xzLtdcQMsPfKKOoIyodLnWW54g\n"\
"DavqVcCmb75QU941/h6kKhPfVXo19B0qGdxn2MTE9soIZLrpMBnpyUuK91B5GsNz\n"\
"K02N61a9TmY9QF6BBhyyRKudg+8Nx3DTMja/AWsDDm1xD/moaABjBL6anLtuoTMb\n"\
"zoKCIRlZekDRWwb7ha4UQ34EZYIIxcqjTMK1McY7XDpZWZsZTuds15z8N849PQoV\n"\
"1l7p75mxiFVOiGwymrkJDulmpXWFHH+NDJaRPQOLOjZ70WRHbt5A734XZqX4bySR\n"\
"RVET/iRfW1moAZTItfFG5yDehd91mK1kBZU7jQIDAQABAoIBAQCX1dHPnFYzw1K9\n"\
"vZZu6W4LcOzEIWGwiMQVX9MJO869+aqfq4n+NORuJ8TV27tHUnEwkUKYo9oLpaMU\n"\
"xrmU3jaZlPNi0s/DOpF8MccYmT4am5hv1drsKQT0WuDoqg2Vb5uJlL3TIV2CK666\n"\
"2cOYMFCI91b43i10fBiiwTJQsTBD1ZWlOWpvgJlS/wWZfbmfBRTRGTUM5wQnAg4D\n"\
"yP03Ghp26KgwDxuwOV4yVLoNxu/citVbRb9PHEDSS+VQlMHznhDikW+6BqtRhVqh\n"\
"VYidjcXTggzjxzaTnkTJ2CoCnRL2XpbV6GX0Ny+vPAqVrDjrzv+0fbjg0toYbiup\n"\
"MY36eTIBAoGBAN7OpAKElhPIOHxxdObeUt6cKykJYOZKw8WDcfkuOGcsF0fJOOpF\n"\
"SsD2SaDZk9X5znWhyd4rGPJR44/6Xt9ZCqt6j11DWY6aldk3zu7DweDsCwMbD/nr\n"\
"pDPbcuh8+MLqpwd1Wsu6DxHEDDK1m/3+B4YONv5g4mT0cyB1oCYXAZJZAoGBAMsQ\n"\
"G6Y71UHPIOpO+7J8ayEaetDdTiUY5XN26UhrHE2CJBRqq4m1SDRbAPf+Un1zfjT9\n"\
"2LjGSHDkunYaieIEGIqKuls2CSnGH7UHdnKMh7S/gwrAH3n9zs5bDbONL+YJjmm3\n"\
"hK4P0U3tp+EzNGUoZiRy7KMHiVsJDlLZJwjqsERVAoGBAKR7Ti6hrJ0r+S89Hrz0\n"\
"sZ6vEVm5F7TKyt273N7EVVUtAn63OPIRd08eQlqhZPbY9KZ4aqs9i6wP8fuvLGyb\n"\
"sjnHP6DtAGc7DZaPEY/IKg+ekb6YMuIgKFc0EQ86evaB/g6OfxnY4BkQbqTc1yzZ\n"\
"ZLp9MfH2mgtHPtpem3yjDUD5AoGAf4Ko6hTOUBnBoIBiWuz31HytPHSLOo5Mntm/\n"\
"mWLxDda30z48Yye7pGy0ygUgRXh9escgDL8uA/4M/Faj2JIb2vtMFDR1Qo8Pn/yE\n"\
"q1+FY8GShvCnk1IGR9wzWVlCB6BelhHQNgDmvJmMfsRJlW/t29tyrtjvroOcQ/fq\n"\
"JBZDA1UCgYEAowGlw0GoeaRsuyZGxxLCQUXVCBwOi3IEAAqbnrI7bpKty/5CtjG6\n"\
"9rnRQi7XMuho3to8LaKGMUVlS68TRd3pvFa8RBSDpJajVnUNO5HSSFcJMTc/uF83\n"\
"HmCwygXDn5T54tuwnNN7luhiqzxurrWKS8ol4urfarNgNNW0N/DwMpA=\n"\
"-----END RSA PRIVATE KEY-----"

/*
 * PEM-encoded Just-in-Time Registration (JITR) certificate (optional).
 *
 * If used, must include the PEM header and footer:
 * "-----BEGIN CERTIFICATE-----\n"\
 * "...base64 data...\n"\
 * "-----END CERTIFICATE-----"
 */
#define keyJITR_DEVICE_CERTIFICATE_AUTHORITY_PEM  NULL

/* The constants above are set to const char * pointers defined in aws_dev_mode_key_provisioning.c,
 * and externed here for use in C files.  NOTE!  THIS IS DONE FOR CONVENIENCE
 * DURING AN EVALUATION PHASE AND IS NOT GOOD PRACTICE FOR PRODUCTION SYSTEMS
 * WHICH MUST STORE KEYS SECURELY. */
extern const char clientcredentialCLIENT_CERTIFICATE_PEM[];
extern const char* clientcredentialJITR_DEVICE_CERTIFICATE_AUTHORITY_PEM;
extern const char clientcredentialCLIENT_PRIVATE_KEY_PEM[];
extern const uint32_t clientcredentialCLIENT_CERTIFICATE_LENGTH;
extern const uint32_t clientcredentialCLIENT_PRIVATE_KEY_LENGTH;

#endif /* AWS_CLIENT_CREDENTIAL_KEYS_H */
