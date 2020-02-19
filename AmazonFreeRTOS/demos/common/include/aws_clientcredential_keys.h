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
"MIIDWTCCAkGgAwIBAgIUVn0/ji0vBo5VocuU2lZ/DafWiuswDQYJKoZIhvcNAQEL\n"\
"BQAwTTFLMEkGA1UECwxCQW1hem9uIFdlYiBTZXJ2aWNlcyBPPUFtYXpvbi5jb20g\n"\
"SW5jLiBMPVNlYXR0bGUgU1Q9V2FzaGluZ3RvbiBDPVVTMB4XDTE5MDMxMTIwMTI0\n"\
"N1oXDTQ5MTIzMTIzNTk1OVowHjEcMBoGA1UEAwwTQVdTIElvVCBDZXJ0aWZpY2F0\n"\
"ZTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBALSgm1pikaLambhwlBIz\n"\
"ssAL0W5L0/oRg0tF6oKEyeci1SsHKU7r1WcDcE4wc55wDK+LvoxIP+Dj7pq4W2Ev\n"\
"FVSzwsTndwmRy/LLZmJhOUeAbNSSGfWXpispE1FtVgGWvnV7BzUnOP/+j1MrOglM\n"\
"IzahCghMcNe4BlWKhB7tdhQ9IwxqqIpAAZEAJcEUA5S13gD0dVdtF2jdDJgR1E42\n"\
"eiUkNrx5QShRS9LOKCUHpclI4vXpHhtLduoBfVcXM3QGJdng9nKbwwP34RKK7NbO\n"\
"TFGos0bR+Ei+kzTquPCJRkmjSIxxfZSpYzqUkzs220awF8LQWcK7asnrNCrs2bsL\n"\
"lI8CAwEAAaNgMF4wHwYDVR0jBBgwFoAUJRGQz2ybxD5Q19ZYE623mSnPuHMwHQYD\n"\
"VR0OBBYEFL2TsPWpNiHa/I4GW0EB4m7zYl/9MAwGA1UdEwEB/wQCMAAwDgYDVR0P\n"\
"AQH/BAQDAgeAMA0GCSqGSIb3DQEBCwUAA4IBAQA2QmcqFxCQHmRX6G6BanhYYz2w\n"\
"FE6DEyKpsVFWkb9loYvBQ+qY/nFPUaPy5GpTjZSXH2UQRjfEPPwzVa9f5K90xLSB\n"\
"haLjbIjrHnqPLiLUi8EcjuW8f4XB9m7M+/SfJX7lxm37ay3ZEK79gOrVbhoqsiq2\n"\
"1FKeWnZPyRWVtMVt06cU/Y3mwh7kwz+XkpvtC1BLqMWbto9PwQqtA/0Ur1PBakNr\n"\
"yCh7mJN99c14qUe4gHYTzpg9r7S0wmQ2lrpn1+pspNM/4R4bnb1Tqkz5k/eURoT1\n"\
"GQh/KZFqCD0LqUAeVfAJGZi+uD5G4hCU8neNKiRNbZ3EVE4zxZN+z4xeKe8q\n"\
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
"MIIEpAIBAAKCAQEAtKCbWmKRotqZuHCUEjOywAvRbkvT+hGDS0XqgoTJ5yLVKwcp\n"\
"TuvVZwNwTjBznnAMr4u+jEg/4OPumrhbYS8VVLPCxOd3CZHL8stmYmE5R4Bs1JIZ\n"\
"9ZemKykTUW1WAZa+dXsHNSc4//6PUys6CUwjNqEKCExw17gGVYqEHu12FD0jDGqo\n"\
"ikABkQAlwRQDlLXeAPR1V20XaN0MmBHUTjZ6JSQ2vHlBKFFL0s4oJQelyUji9eke\n"\
"G0t26gF9VxczdAYl2eD2cpvDA/fhEors1s5MUaizRtH4SL6TNOq48IlGSaNIjHF9\n"\
"lKljOpSTOzbbRrAXwtBZwrtqyes0KuzZuwuUjwIDAQABAoIBAQCz8OvS9y8uladd\n"\
"3okkOOxx9VQGFPRvwtKRQm2E6NRatpC19MRqIvbNUNeojQwhYm7A0u5YwgEhAPDK\n"\
"oa4m+si9QPdfQVeM6PnMPmUYzNJLMN06RvIlf5XCmYDtNYbgvlOupYlgolpebDJM\n"\
"IFwItxi9a2CbM8uWm3Vz8jH8vYNMVI0F7onro/D2TODRlR9cltmTrMX+YHJfcAfi\n"\
"w/K1NG70zn68vI4FIDp6bFgtZROu1Plq6KJTNwOfKljJEk1cU311RDYW6Ne/IccP\n"\
"hHO9ktzcZxepVjqW14DodTq0ZOSI7BAmi5IFQ9J3YYDJ4UHo8uj0RePkdR3vHlFA\n"\
"+SvMXADBAoGBAOz55W5FapyIqY063U0hNLKW350ww8YYYdysUjUSztJ/dNWRRVyH\n"\
"Pr67rYoVu602x8qzf99eVqwT4HhTsrgriIUlK+7hVGO/euOb9xUVqyPU+kchOYcP\n"\
"5PTVrnrCnJ6nGablv3E4j00vKgwXXHBnaLkUJ9LchhktYkngtPgDwNt9AoGBAMMg\n"\
"r2NCXSPvCD1/klZEnYi5896JstHFCbKnmcUW7SzVeDgwRYLwwX72yngAsJDyNSZw\n"\
"Q50MeHuTKi3vnjzNVXgEiLFCjCtCIS5Un2+6VfdFvT5w434AKJskJNxdizBJGmTR\n"\
"J3WJJ+OvbXHLyxA1PdOIrOL1Cq3pt277eSwx6bX7AoGBAJtDg/IC4z4aQFS7O6G8\n"\
"XuWf+nToLW0OLphCAz6oyv+Z6LfBDZv5NMANAT/Wy3dKzA5gGykDi3AFOe48kH0g\n"\
"cLsjxqwl0H/mRiL43iNfZhj9Ato1x5ZZcJ6FnmLqPWmpfCIgp5UMBMACZd80Mymm\n"\
"ZzPUI9+BAw9d7+cNpiRVeTeVAoGAaUzvOUqsBuNM+BsrNqDqvslTAMoglTGXDTGD\n"\
"OygnMCW3LeNm78XLNiAqnV4J6v66jhbRdiQvtMhzX7zLERbiQ9V2iupVyFZ0n5MN\n"\
"Q3c0QzAAc3zqV6nwP+Def4l/vrwEoVl5yOUOgMG/90Q6PnHs/oXofsYsUDQrSJov\n"\
"BxmcfRcCgYBafAKWRfBcGWJ7/9tVD7qHjseUzcVJkiyT1J6xXrY3onu5rdqlnUBp\n"\
"ZwfLCbybUQSfRUOaJW3P2/pXiGKv0MwIg+Ct4hxT+HigVKUypQYriteliZyM1/yx\n"\
"o4GySSXD62ne1YbdIvc/MJZrGCvIjps3FPBvuIG3vd+pg1YZCOWpqg==\n"\
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
