# Package-Protect (Incomplete)

[This commit comparison](https://github.com/ZoieM/Package-Protect/compare/2d71048..57ad8ff) demonstrates the key files in this project.

Files for FreeRTOS Tasks:
+ **`AmazonFreeRTOS/demos/common/mqtt/aws_hello_world.c`** is our main file.
+ **`AmazonFreeRTOS/demos/ti/cc3220_launchpad/common/application_code/ti_code/CC3220SF_LAUNCHXL.c`** and **`AmazonFreeRTOS/demos/ti/cc3220_launchpad/common/application_code/ti_code/CC3220SF_LAUNCHXL.h`** contain information about which GPIO pins we are using.

Files for AWS Communication: 
+ **`AmazonFreeRTOS/demos/common/include/aws_clientcredential.h`** contains the information required for ***MQTT communication via AWS IoT***
  + `static const char clientcredentialMQTT_BROKER_ENDPOINT[]` Set this equal to your **AWS IoT Endpoint** (e.g. <1234567890123>-ats.iot.<us-east-1>.amazonaws.com). To find the endpoint, go to AWS IoT Console > Settings > Endpoint.
  + `#define clientcredentialIOT_THING_NAME` Set this equal to the name of the **AWS Thing** that represents the TI CC3220SF-LAUNCHXL microcontroller.
  + `#define clientcredentialWIFI_SSID       "SJSU_MyDevice"` Set this to the **name of the WiFi network** that you want to use the board with. (If you are on campus, you must use the SJSU_MyDevice WiFi network. To do this, you must [register](https://one.sjsu.edu/task/all/my-devices-portal) the device's MAC address.)
  + `#define clientcredentialWIFI_PASSWORD   ""` Set this to the **password of the WiFi network** that you want to use the board with. (If you are on campus using SJSU_MyDevice, the password is nothing.)
  + `#define clientcredentialWIFI_SECURITY   eWiFiSecurityOpen`  Set this equal to the **security type of the WiFi network** you are using. (With SJSU_MyDevice, use eWiFiSecurityOpen. At home, I used eWiFiSecurityWPA2)
+ **`AmazonFreeRTOS/demos/common/include/aws_clientcredential_keys.h`** contains the ***credentials for the device*** (a public and private key pair) that allow it to access our AWS IoT services.
  + Don't modify this file directly; instead use the Certificate Configurator program: `<BASE_FOLDER>\tools\certificate_configuration\CertificateConfigurator.html`.
