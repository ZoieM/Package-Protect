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
"MIIDWjCCAkKgAwIBAgIVAK79c31TlE5qiaLEXWU1TpwpAfXgMA0GCSqGSIb3DQEB\n"\
"CwUAME0xSzBJBgNVBAsMQkFtYXpvbiBXZWIgU2VydmljZXMgTz1BbWF6b24uY29t\n"\
"IEluYy4gTD1TZWF0dGxlIFNUPVdhc2hpbmd0b24gQz1VUzAeFw0xOTA1MTIwMzA1\n"\
"NDdaFw00OTEyMzEyMzU5NTlaMB4xHDAaBgNVBAMME0FXUyBJb1QgQ2VydGlmaWNh\n"\
"dGUwggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQCvafVDR623zZxWUzsd\n"\
"TNX+Z9AJIZis5tC5kCegxrPcLQJ7fq0EEdNEBm3FFXbceLJLBa5pKrWiBQhW4oLP\n"\
"NPGgWX9SWnpR7euuAhUFCg2qX+yNVJYvwhz/+31phnDM5/ebot2tfEDEV772d4bv\n"\
"XQKVzMhvfJ/H/OrtfutC4Hu02e5enEUWcarWTWMsiOtb61X+Q15lkLvWKmINICoa\n"\
"GYWKh2HR/rEUrtMtvfruSDn0InvQcVMwm1SAEYHgOSTxBGrV0COg/iD1HjOWBoHh\n"\
"qf2F5B0Wyk8ZV78//88QoWd4bkhKiF5lv8jnjfGcp8y6hi082uapRIn2vCwrPWyB\n"\
"GJHDAgMBAAGjYDBeMB8GA1UdIwQYMBaAFMYcwibhk7iZQTgTWYytznkRxz/pMB0G\n"\
"A1UdDgQWBBRlRXxo7twbXlax4HbgrbbB9r42cjAMBgNVHRMBAf8EAjAAMA4GA1Ud\n"\
"DwEB/wQEAwIHgDANBgkqhkiG9w0BAQsFAAOCAQEAJcmO7cJbO/dcHdkU/SQRDDdQ\n"\
"OidnvWZ+TmuISl8Pb3Y6jkgI7oWPIU3j3pKP+RuPUr9cHcfqgE4xDe1GFI6g5/lK\n"\
"DtjxXT21Bq9WscuLZzwcgmeuZ3wBrUqBkxDXa3RgnP6QpV6LjGoCrYTO4RkZocjv\n"\
"fFuAAWTUQEbq2oJdYj18jn3uDqhtZFuWGOulmG+F+db25vmW1h1icnawhaVyufkO\n"\
"QfJsDa5WSiH1L09cr63MdmAigpbUWTw7rpXFQvFF0/LpEHRgGgKzMXtyDFB/bTlq\n"\
"kbg8QPLStQxjJi/fGg8wGmkok/zbY6Tvjfil1VNCA51xrJoGObMaPkgVrXCD3g==\n"\
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
"MIIEogIBAAKCAQEAr2n1Q0ett82cVlM7HUzV/mfQCSGYrObQuZAnoMaz3C0Ce36t\n"\
"BBHTRAZtxRV23HiySwWuaSq1ogUIVuKCzzTxoFl/Ulp6Ue3rrgIVBQoNql/sjVSW\n"\
"L8Ic//t9aYZwzOf3m6LdrXxAxFe+9neG710ClczIb3yfx/zq7X7rQuB7tNnuXpxF\n"\
"FnGq1k1jLIjrW+tV/kNeZZC71ipiDSAqGhmFiodh0f6xFK7TLb367kg59CJ70HFT\n"\
"MJtUgBGB4Dkk8QRq1dAjoP4g9R4zlgaB4an9heQdFspPGVe/P//PEKFneG5ISohe\n"\
"Zb/I543xnKfMuoYtPNrmqUSJ9rwsKz1sgRiRwwIDAQABAoIBAE/A6C9X1qb8B/nD\n"\
"y9vNhHov7wlHyifKpdnIrgvObBZOLJPDi5yPEjQajCwQT0N8aOvtQFg2f/CTQzBl\n"\
"uj3Ff5p9NoNV+cloWEB8V9w7ruzowh+b9tDt+8tzJ5kj9ANl8FFF4m4vUS80CfH7\n"\
"dFE+Q5+iRPtTeT4vQw0KKKL2d6hIsOzD3rW9a27yQpp8H8mMyAF6xXsYK7kL3zz2\n"\
"ETH+znDuzsZZEusypdjgBgq4vNRRBMMajnzK8iN9DG9Sd9tLX+YwC01aQxQ/kZbw\n"\
"AfFl8far68eecWJDWVcKMvGJGSHNoI+yEbGW2avtViXiOKH8sGfYyM1Xx4bTCNgW\n"\
"EY/0R8kCgYEA2lgjyQbq043PbjVogFY6q6rjm4AE23ZURfGycC4g58azTr4fP4fI\n"\
"wpMunQ1aWVa22Jneeybe4Ex9e0qdr4GuSdrpA9NTE+zsgz24hwI6VEplE6ySdtQV\n"\
"0US81DdrLiEWTQSJ9eow/mDxPGDvSflxCMVBWEsexX0llas2/y51Os0CgYEAzapy\n"\
"/ZbH9nnESC0IJ0XP2y7hIcpkSd39BtYKkh3wao/h25WAkM/52/WWdsdlsqigAq43\n"\
"Nfcu9itjkgvpoYdC/nRplw7jxtOkorBRrxV+ogTUaAUACNuaGUMQg4PoIWFjoOE6\n"\
"RShPc9tkhxYsQCbAUvfcOGi1xSycyQIgYFUSHs8CgYAUtZdvUcCkICc0hMxMn+Eg\n"\
"tyyvaw0K48ZKfAo4qadlVGtdZJsCI5bfHaamLsYLAzaEhNOdSqqJC7g7IXCjXOFz\n"\
"D9haDIkssqQcLpZ597Qgmo3Lt+qMasFHAAYI+tinn2vGElAjivrqpbc7ytXnZkla\n"\
"U5tHDJj2klAmSf8FZRqpYQKBgAG9ER/HqIUS3m/lwY3jbzBhIxIQDez57WujX4+A\n"\
"pUmhUb1zdBTFTU1otA7o/JkYB9I9+sWAA2udTkgrxZvR8uUHwuS+AXrqyxd8+hPK\n"\
"0Lk55TnD4Q4yHQldocQa11mA40C25rEy+Aj4r87chx87tKB+6+OmLvMtv12LoQ5v\n"\
"aanNAoGAV4KcbOJ0KEhwM3eDAZLzWCg6khlsXGAV9EHMZcS16+GRipCJcjcDfEVQ\n"\
"RqQaagvwtSsp3FvlnHXJ+ZdvndqbuKzR+rt5KLiZrggg521vibMqCU1dp8hGyNBh\n"\
"CqlZVdvXefPpgRMcusf/b92anFYzTBaJnXYXqnQ2jqnyflOwXmw=\n"\
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
