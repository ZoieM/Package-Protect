# Package-Protect

## Understanding the current codebase
[This commit comparison](https://github.com/ZoieM/Package-Protect/compare/2d71048..57ad8ff) demonstrates the key files in this project.

### Files for FreeRTOS Tasks:
+ **`AmazonFreeRTOS/demos/common/mqtt/aws_hello_world.c`** is our main file. In commit 57ad8ff:
  + Lines 1-88 are **includes and global variables**.
  + Lines 89-527 are **tasks for AWS MQTT messages**.
  + Lines 528-781 are **tasks for the mailbox sensors**.
  + Lines 782+ is analagous to our int main() function--use this function to **initialize any tasks and/or semaphores you create**.
+ **`AmazonFreeRTOS/demos/ti/cc3220_launchpad/common/application_code/ti_code/CC3220SF_LAUNCHXL.c`** and **`AmazonFreeRTOS/demos/ti/cc3220_launchpad/common/application_code/ti_code/CC3220SF_LAUNCHXL.h`** contain information about which pins we are using. (Most of us only care about GPIO pins; only screen cares about UART pins).
  + GPIO/UART **pin names** are set in `CC3220SF_LAUNCHXL.h`. GPIO/UART **pin configurations** (e.g. input/output, interrupts...) are set in `CC3220SF_LAUNCHXL.c`. For more info on GPIO, read the comments in `AmazonFreeRTOS\lib\third_party\mcu_vendor\ti\SimpleLink_CC32xx\v2_10_00_04\source\ti\drivers\gpio\GPIOCC32XX.h` and `AmazonFreeRTOS\lib\third_party\mcu_vendor\ti\SimpleLink_CC32xx\v2_10_00_04\source\ti\drivers\GPIO.h`. For more info on UART, read the comments in `AmazonFreeRTOS\lib\third_party\mcu_vendor\ti\SimpleLink_CC32xx\v2_10_00_04\source\ti\drivers\uart\UARTCC32XX.h` and `AmazonFreeRTOS\lib\third_party\mcu_vendor\ti\SimpleLink_CC32xx\v2_10_00_04\source\ti\drivers\UART.h`.
  + NOTE:  "The order of the pin configurations [in CC3220SF_LAUNCHXL.c] must coincide with [the order of] what was defined in CC3220SF_LAUNCHXL.h," and "pins not used for interrupts should be placed at the end of the array"

### Files for AWS Communication: 
+ **`AmazonFreeRTOS/demos/common/include/aws_clientcredential.h`** contains the information required for ***MQTT communication via AWS IoT***
  + `static const char clientcredentialMQTT_BROKER_ENDPOINT[]` Set this equal to your **AWS IoT Endpoint** (e.g. <1234567890123>-ats.iot.<us-east-1>.amazonaws.com). To find the endpoint, go to AWS IoT Console > Settings > Endpoint.
  + `#define clientcredentialIOT_THING_NAME` Set this equal to the name of the **AWS Thing** that represents the TI CC3220SF-LAUNCHXL microcontroller.
  + `#define clientcredentialWIFI_SSID       "SJSU_MyDevice"` Set this to the **name of the WiFi network** that you want to use the board with. (If you are on campus, you must use the SJSU_MyDevice WiFi network. To do this, you must [register](https://one.sjsu.edu/task/all/my-devices-portal) the device's MAC address.)
  + `#define clientcredentialWIFI_PASSWORD   ""` Set this to the **password of the WiFi network** that you want to use the board with. (If you are on campus using SJSU_MyDevice, the password is nothing.)
  + `#define clientcredentialWIFI_SECURITY   eWiFiSecurityOpen`  Set this equal to the **security type of the WiFi network** you are using. (With SJSU_MyDevice, use eWiFiSecurityOpen. At home, I used eWiFiSecurityWPA2)
+ **`AmazonFreeRTOS/demos/common/include/aws_clientcredential_keys.h`** contains the ***credentials for the device*** (a public and private key pair) that allow it to access our AWS IoT services.
  + Don't modify this file directly; instead use the Certificate Configurator program: `<BASE_FOLDER>\tools\certificate_configuration\CertificateConfigurator.html`.
