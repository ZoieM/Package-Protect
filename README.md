# Package Protect

## Hardware

### Components List
Package Protect uses the following hardware:
+ [SimpleLink™ Wi-Fi® CC3220SF Wireless Microcontroller LaunchPad™ Development Kit](http://www.ti.com/tool/CC3220SF-LAUNCHXL?jktype=tools_software)
+ [Pnuematic Lock](https://www.amazon.com/dp/B01IB3OIVO/ref=sspa_dk_detail_7?psc=1&pd_rd_i=B01IB3OIVO)
+ [4x5 Keypad Membrane](https://www.amazon.com/gp/product/B07RX9ZBF7/ref=ppx_yo_dt_b_search_asin_title?ie=UTF8&psc=1)
+ [20x4 UART LCD](https://www.amazon.com/gp/product/B0757BFQM2/ref=ppx_yo_dt_b_asin_title_o03_s00?ie=UTF8&psc=1)
+ [Ultrasonic Sensors](https://www.amazon.com/gp/product/B01COSN7O6/ref=ppx_yo_dt_b_asin_title_o00_s00?ie=UTF8&psc=1)
+ [Limit Switches](https://www.amazon.com/dp/B07BL33XXT/ref=sspa_dk_detail_0?psc=1&pd_rd_i=B07BL33XXT&pd_rd_w=9nFwj&pf_rd_p=45a72588-80f7-4414-9851-786f6c16d42b&pd_rd_wg=6FgEB&pf_rd_r=DRRCBGBSMXJPN6FY4KQX&pd_rd_r=31581f58-97d5-4a86-9922-5602ede98874&spLa=ZW5jcnlwdGVkUXVhbGlmaWVyPUEzR0FFWEo2VTRFUEYyJmVuY3J5cHRlZElkPUEwNzg0NjQ3VUFRWUhLNjJDVTk5JmVuY3J5cHRlZEFkSWQ9QTA4OTgwNDZFTVVBNjlTWElDVDEmd2lkZ2V0TmFtZT1zcF9kZXRhaWwmYWN0aW9uPWNsaWNrUmVkaXJlY3QmZG9Ob3RMb2dDbGljaz10cnVl)

### Hardware References
For more information about these components, refer to the following documentation:
+ [Official CC3220SF Technical Documents List](http://www.ti.com/tool/CC3220SF-LAUNCHXL#technicaldocuments)
  + [User's Guide](http://www.ti.com/lit/ug/swru463b/swru463b.pdf)
  + [Technical Reference Manual](http://www.ti.com/lit/ug/swru465/swru465.pdf)

## Software
### Understanding repo organization
This repository is comprised of three distinct versions of the AmazonFreeRTOS project:

+ **HelloWorld**: Clean slate for IDE configuration and understanding (and a backup/reference in a disasterous case production code is irreparably broken)
+ **OldReferenceCode**: Archive of previous project work, primarily relevant for writing task and configuring GPIO pins.
+ **PackageProtect**: Production code folder. This is where we should write our drivers.

The **AWS** folder contains content relevant to configuring AWS services.

### Understanding the project architecture
[This commit comparison](https://github.com/ZoieM/Package-Protect/compare/2d71048..57ad8ff) demonstrates the key files in this project.

#### Key files for FreeRTOS tasks:
+ **`AmazonFreeRTOS/demos/common/mqtt/aws_hello_world.c`** is our ***main file***. In commit 57ad8ff:
  + Lines 1-88 are **includes and global variables**.
  + Lines 89-527 are **tasks for AWS MQTT messages**.
  + Lines 528-781 are **tasks for the mailbox sensors**.
  + Lines 782+ is analagous to our int main() function--use this function to **initialize any tasks and/or semaphores you create**.
+ **`AmazonFreeRTOS/demos/ti/cc3220_launchpad/common/application_code/ti_code/CC3220SF_LAUNCHXL.c`** and **`AmazonFreeRTOS/demos/ti/cc3220_launchpad/common/application_code/ti_code/CC3220SF_LAUNCHXL.h`** contain information about which ***pins*** we are using. (Most of us only care about GPIO pins; only screen cares about UART pins).
  + GPIO/UART **pin names** are set in `CC3220SF_LAUNCHXL.h`. GPIO/UART **pin configurations** (e.g. input/output, interrupts...) are set in `CC3220SF_LAUNCHXL.c`.
    + For more info on GPIO, read the comments in **`AmazonFreeRTOS\lib\third_party\mcu_vendor\ti\SimpleLink_CC32xx\v2_10_00_04\source\ti\drivers\gpio\GPIOCC32XX.h`** and **`AmazonFreeRTOS\lib\third_party\mcu_vendor\ti\SimpleLink_CC32xx\v2_10_00_04\source\ti\drivers\GPIO.h`**. 
    + For more info on UART, read the comments in **`AmazonFreeRTOS\lib\third_party\mcu_vendor\ti\SimpleLink_CC32xx\v2_10_00_04\source\ti\drivers\uart\UARTCC32XX.h`** and **`AmazonFreeRTOS\lib\third_party\mcu_vendor\ti\SimpleLink_CC32xx\v2_10_00_04\source\ti\drivers\UART.h`**.
  + NOTE:  "The order of the pin configurations [in CC3220SF_LAUNCHXL.c] must coincide with [the order of] what was defined in CC3220SF_LAUNCHXL.h," and "pins not used for interrupts should be placed at the end of the array"

#### Key files for AWS communication: 
+ **`AmazonFreeRTOS/demos/common/include/aws_clientcredential.h`** contains the information required for ***MQTT communication via AWS IoT***
  + `static const char clientcredentialMQTT_BROKER_ENDPOINT[]` Set this equal to your **AWS IoT Endpoint** (e.g. <1234567890123>-ats.iot.<us-east-1>.amazonaws.com). To find the endpoint, go to AWS IoT Console > Settings > Endpoint.
  + `#define clientcredentialIOT_THING_NAME` Set this equal to the name of the **AWS Thing** that represents the TI CC3220SF-LAUNCHXL microcontroller.
  + `#define clientcredentialWIFI_SSID       "SJSU_MyDevice"` Set this to the **name of the WiFi network** that you want to use the board with. (If you are on campus, you must use the SJSU_MyDevice WiFi network. To do this, you must [register](https://one.sjsu.edu/task/all/my-devices-portal) the device's MAC address.)
  + `#define clientcredentialWIFI_PASSWORD   ""` Set this to the **password of the WiFi network** that you want to use the board with. (If you are on campus using SJSU_MyDevice, the password is nothing.)
  + `#define clientcredentialWIFI_SECURITY   eWiFiSecurityOpen`  Set this equal to the **security type of the WiFi network** you are using. (With SJSU_MyDevice, use eWiFiSecurityOpen. At home, I used eWiFiSecurityWPA2)
+ **`AmazonFreeRTOS/demos/common/include/aws_clientcredential_keys.h`** contains the ***credentials for the device*** (a public and private key pair) that allow it to access our AWS IoT services.
  + Don't modify this file directly; instead use the Certificate Configurator program: `<BASE_FOLDER>\tools\certificate_configuration\CertificateConfigurator.html`.
